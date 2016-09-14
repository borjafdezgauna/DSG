#include "../stdafx.h"
#include "../inc/Fantasma.h"
#include "../inc/Escenario.h"
#include "../inc/FrameRate.h"
#include "../inc/ObjModel.h"
#include "../inc/ObjParser.h"

int g_num_malos= 0;
Fantasma g_fantasmas[MAX_NUM_MALOS];

int Fantasma::m_modelDisplayList= 0;

//Constructor 
Fantasma::Fantasma()
{
	m_vivo = true;
	m_movimiento = false;
	m_atrapado = false;
	angulo = 0.0;
}

//Destructor
Fantasma::~Fantasma()
{
	if (m_modelDisplayList)
	{
		glDeleteLists(m_modelDisplayList,1);
	}
}

//Metodos propios de la clase

//Cargar el fantasma
void Fantasma::addFantasma(int x, int y)
{
	g_fantasmas[g_num_malos].SetPos(x,y);
	g_fantasmas[g_num_malos].SetPosReal(x + 0.5,y + 0.5);
	g_fantasmas[g_num_malos].SetPosRealDestino(x + 0.5,y + 0.5);

	g_num_malos++;

	
}



/*
Modifica las banderas dependiendo hacia donde pueda ir
*/
void Fantasma::comprobarAlrededor(int x, int y)
{
	//Obtengo lo que hay en una posicion determinada
	Escenario::getInstance()->getC(x, y);
	
	//Sobreescribo lo que hay en una posición determinada
	//Escenario::getInstance()->setC(x, y, c);
	for (int i= 0; i<4; i++) movs[i]= false;


	//Verifico que no me salgo del rango
	if((x >= 0 && x<=127) && (y >= 0 && y <= 127))
	{
		if(getC(x+1,y) == ' ')
		{
			//Puede ir hacia delante
			movs[DERECHA] = true;
		}
		if(getC(x,y+1) == ' ')
		{
			//Puede ir hacia arriba
			movs[ARRIBA] = true;
		}
		if(getC(x,y-1) == ' ')
		{
			//Solo puedo ir hacia a abajo
			movs[ABAJO] = true;
		}
		if(getC(x-1,y) == ' ')
		{
			//Solo puedo ir hacia detras
			movs[IZQUIERDA] = true;
		}
	}
}

char Fantasma::getC(int x, int y) {
	return Escenario::getInstance()->getC(x,y);
}




//Establecer un recorrido para el fantasma
void Fantasma::moverFantasma()
{
	
	int posiciones[4];
	double probabilidades[4];
	int suma_posiciones = 0;
	double suma_probabilidades = 0.0;
	double valor_aleatorio;
	int opcion;
	//int count = 0;

	//CONTROLAR SI HAY QUE TOMAR DECISIÓN O NO
	//ACTUALIZAR POS_X Y POS_Y
	if(fabs(m_posDestino[0] - m_pos_real_x) >= 0.01 || fabs(m_posDestino[1] - m_pos_real_y) >= 0.01)
	{
		return;
	}

	m_pos_x= (int) (m_posDestino[0]- 0.5);
	m_pos_y= (int) (m_posDestino[1]- 0.5);


	comprobarAlrededor(m_pos_x,m_pos_y);

	//Inicializamos la posicion de Inicio
	m_posInicio[0] = m_pos_x+0.5;
	m_posInicio[1] = m_pos_y+0.5;

	//En el array posiciones estan a uno las posiciones que se puede tomar
	for (int i=0; i<4; i++)
	{
		if(movs[i] == true) posiciones[i] = 1;
		else posiciones[i] = 0;
		
		suma_posiciones = suma_posiciones + posiciones[i];
	}
	
	//En el array probabilidades se rellenan las probabilidades de los posibles caminos
	for (int x=0; x<4; x++)
	{
		probabilidades[x] = posiciones[x]*(1./(float)suma_posiciones);
	}

	//Establecemos un valor aleatorio y al recorrer el array de probabilidades cuando llegue a una probabilidad mayor es la
	//que elige
	valor_aleatorio = ((float)(rand()%100))/100.f;
	for(int x=0; x<4; x++)
	{
		suma_probabilidades = suma_probabilidades + probabilidades[x];
		if(suma_probabilidades > valor_aleatorio)
		{
			opcion = x;
			break;
		}
	}
	
	//Dependiendo de la direccion escogida para el destino, se desplaza en la matriz
	//alante:0,izquierda:1,derecha:2,atras:3
	switch (opcion)
	{
		case ARRIBA:
			m_posDestino[0] = m_pos_x+0.5;
			m_posDestino[1] = m_pos_y+1.5;
			break;
		case IZQUIERDA:	
			m_posDestino[0] = m_pos_x-0.5;
			m_posDestino[1] = m_pos_y+0.5;
			break;
		case DERECHA:	
			m_posDestino[0] = m_pos_x+1.5;
			m_posDestino[1] = m_pos_y+0.5;
			break;
		case ABAJO:	
			m_posDestino[0] = m_pos_x+0.5;
			m_posDestino[1] = m_pos_y-0.5;
			break;
	}

}

//void Fantasma::setRotation(void){
//	glRotatef(angulo, 0.0, 0.0, 1.0);
//}

void Fantasma::loadModel()
{
	if (!m_modelDisplayList)
	{
		ObjParser parser(string("models/Sonic.obj"),true,true);
		parser.load();
		ObjModel *model=  parser.getObjModel();
		model->scale(0.025);

		m_modelDisplayList= glGenLists(1);
		glNewList(m_modelDisplayList,GL_COMPILE);
		model->draw();
		glEndList();
	}
}

//Funcion para dibujar los fantasmas
void Fantasma::draw()
{

	for (int x = 0; x < g_num_malos; x++)
	{
		if(g_fantasmas[x].getVivo())
		{
			//glColor3f (0.5, 1.0, 0.5);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();

			glTranslatef(g_fantasmas[x].getPosRealX(),g_fantasmas[x].getPosRealZ(),0);
			glRotatef(90.f,1.f,0.f,0.f);

			glCallList(m_modelDisplayList);

			glPopMatrix();
		}

	}
}

/*
RECORREMOS EL ARRAY DE FANTASMA PARA PONERLOS EN MOVIMIENTO
*/

void Fantasma::comenzarMovimiento()
{
	for(int x = 0; x < g_num_malos; x++)
	{
		g_fantasmas[x].moverFantasma();
		g_fantasmas[x].moverPosReal();
	}
}

/*
Dentro de esta funcion se puede llamar a una funcion que compruebe si el fantasma va a ser comido y asi poner 
las variables correspondientes con el valor correcto
*/
void Fantasma::moverPosReal()
{
	//Obtengo x,y de la posicion de INICIO
	////float valorXInicio = m_posInicio[0];
	////float valorYInicio = m_posInicio[1];
	float valorXInicio = getPosRealX();
	float valorYInicio = getPosRealZ();

	//Obtengo x,y de la posicion de DESTINO
	float valorXDestino = m_posDestino[0];
	float valorYDestino = m_posDestino[1];
	
	//Valor del incremento que voy añadir para acercarme al destino
	double incrementoX = 1.0 / (double)getFPS();
	double incrementoY = 1.0 / (double)getFPS();

	//if(valorXInicio - valorXDestino == 0)
	{
		//Estoy incrementando/decrementando Y
		if(valorYDestino - valorYInicio > 0.01)
		{
			//Voy incrementando valorYDestino con incrementoY
			////if(valorYInicio != valorYDestino)
			////{
				//Aplico el incremento
				valorYInicio = valorYInicio + incrementoY;
				////m_posInicio[1] = valorYInicio;
				SetPosRealY(valorYInicio);
			////}			
		}
		else if(valorYInicio - valorYDestino > 0.01)
		{
			//Voy decrementando valorYDestino con incrementoY
			////if(valorYInicio != valorYDestino)
			////{
				//Aplico decremento
				valorYInicio = valorYInicio - incrementoY;
				////m_posInicio[1] = valorYInicio;
				SetPosRealY(valorYInicio);
			////}
		}

	}
	//if(valorYInicio - valorYDestino == 0)
	{
		//estoy incrementando/decrementando X
		if(valorXDestino - valorXInicio > 0.01)
		{
			//Voy incrementando valorXDestino con incrementoX
			////if(valorXInicio != valorXInicio)
			////{
				//Aplico incremento
				valorXInicio = valorXInicio + incrementoX;
				////m_posInicio[0] = valorXInicio;
				SetPosRealX(valorXInicio);
			////}
		}
		else if(valorXInicio - valorXDestino > 0.01)
		{
			//Voy decrementando valorXDestino con incrementoX
			////if(valorXInicio != valorXInicio)
			////{
				//Aplico incremento
				valorXInicio = valorXInicio - incrementoX;
				////m_posInicio[0] = valorXInicio;
				SetPosRealX(valorXInicio);
			////}
		}
	}

	//if(inicial = final)
	//{
	//	//NO HAGO NADA DE MOMENTO. ESTOY EN LA MISMA POSICION
	//}
	//if(final > inicial) // Ejemplo: inicial = 5 y final = 10
	//{

	//}
	
	
	
}

void Fantasma::esPillado(int x)
{
	g_fantasmas[x].setVivo(false);
	g_fantasmas[x].setAtrapado(true);
	//g_num_malos = g_num_malos - 1;
}

int Fantasma::getPosX()
{
	return m_pos_x;
}

int Fantasma::getPosZ()
{
	return m_pos_y;
}

float Fantasma::getPosRealX()
{
	return m_pos_real_x;
}

float Fantasma::getPosRealZ()
{
	return m_pos_real_y;
}

void Fantasma::setAtrapado(bool x)
{
	m_atrapado = x;
}

bool Fantasma::getAtrapado()
{
	return m_atrapado;
}

void Fantasma::setVivo(bool vida)
{
	m_vivo = vida;
}
bool Fantasma::getVivo()
{
	return m_vivo;
}

int Fantasma::getNumMalos()
{
	return g_num_malos;
}

/**
Funcion para decidir si va tomando el camino de los huecos que va encontrando
true: cambia direccion
false: sigue su camino
*/
//bool Fantasma::tomarDecision()
//{
//	int valor;
//	valor = rand()%2;
//
//	if(valor == 0) 
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}

#include "../stdafx.h"
#include "../inc/Personaje.h"
#include "../inc/Fantasma.h"
#include "../inc/Escenario.h"
#include "../inc/FrameRate.h"
#include "../inc/ObjModel.h"
#include "../inc/ObjParser.h"

//Inicializamos el puntero a 0
CPersonaje* CPersonaje::pinstance = 0;
int CPersonaje::m_modelDisplayList= 0;

//De esta forma nos aseguramos de crear una única instancia
CPersonaje* CPersonaje::Instance() {
	if (pinstance == 0) { //Comprobamos si es la primera vez que se llama
		pinstance = new CPersonaje(); //Si es así, creamos la instancia
	}
	return pinstance; //Devolvemos la instancia
}

//Constructor de la clase Personaje
CPersonaje::CPersonaje(void)
{
	realX=0.0;
	realY=0.0;
	actualX=0.0;
	actualY=0.0;
	finalX=0.0;
	finalY=0.0;
	angulo=90.0;
	anguloSig=90.0;
	enMovimiento=false;
	avanzandoX=false;
	avanzandoY=false;
	teclaA=false;
	teclaD=false;
	teclaW=false;
	teclaS=false;
	frps=0;
	dir=1; //Comienza mirando hacia la dcha

}

void CPersonaje::loadModel()
{

	ObjParser parser(string("models/Mario.obj"),true,true);
	parser.load();
	ObjModel *model=  parser.getObjModel();
	model->scale(0.005);

	m_modelDisplayList= glGenLists(1);
	glNewList(m_modelDisplayList, GL_COMPILE);
	model->draw();
	glEndList();
}

//Destructorde la clase Personaje
CPersonaje::~CPersonaje(void)
{
	glDeleteLists(m_modelDisplayList,1);
}

//Método para posicionar al personaje en su pos real
void CPersonaje::setPositionRealXY(float x, float y){
	realX=x;
	realY=y;
}

//Método para posicionar al personaje en la mitad de la celda en la que se encuentra 
void CPersonaje::setPositionActualXY(float x, float y){
	actualX=x;
	actualY=y;
}

//Método para definir la posición a la que se dirige el personaje
void CPersonaje::setPositionFinalXY(float x, float y){
	finalX=x;
	finalY=y;
}


//Devuelve la variable x correspondiente de la posición real del personaje
float CPersonaje::getPositionRealX(void){
	return realX;
}

//Devuelve la variable z correspondiente de la posición real del personaje
float CPersonaje::getPositionRealY(void){
	return realY;
}

//Devuelve la coordenada x de la posición actual del personaje respecto a la celda del escenario
float CPersonaje::getPositionActualX(void){
	return actualX;
}

//Devuelve la coordenada z de la posición actual del personaje respecto a la celda del escenario
float CPersonaje::getPositionActualY(void){
	return actualY;
}

//Devuelve la pos x de la celda de destino
float CPersonaje::getPositionFinalX(void){
	return finalX;
}

//Devuelve la pos y de la celda de destino
float CPersonaje::getPositionFinalY(void){
	return finalY;
}
bool CPersonaje::avanceX(void){
	return avanzandoX;
}
bool CPersonaje::avanceY(void){
	return avanzandoY;
}
float CPersonaje::getAngulo(void){
	return angulo;
}
//Mediante este método definimos la colocación del personaje desde el escenario
void CPersonaje::setPosition(float posX, float posY){
	setPositionActualXY(posX+0.5, posY+0.5);
	setPositionFinalXY(posX+0.5, posY+0.5);
	setPositionRealXY(posX+0.5, posY+0.5);
	glTranslatef(posX+0.5, posY+0.5, 0.0);
}

//El personaje rota en el eje z
void CPersonaje::setRotation(void){
	glRotatef(angulo, 0.0, 0.0, 1.0);
}

//Comprueba si hay pared delante del personaje
bool CPersonaje::hayParedDelante(float posX, float posY){
	if(dir==0 && Escenario::getInstance()->getC(posX, posY-1)=='#'){
		return true;
	}
	else if(dir==1 && Escenario::getInstance()->getC(posX+1, posY)=='#'){
		return true;
	}
	else if(dir==2 && Escenario::getInstance()->getC(posX, posY+1)=='#'){
		return true;
	}
	else if(dir==3 && Escenario::getInstance()->getC(posX-1, posY)=='#'){
		return true;
	}
	else{
		return false;
	}
}

//Comprueba si hay pared detrás del personaje
bool CPersonaje::hayParedDetras(float posX, float posY){
	if(dir==0 && Escenario::getInstance()->getC(posX, posY+1)=='#'){
		return true;
	}
	else if(dir==1 && Escenario::getInstance()->getC(posX-1, posY)=='#'){
		return true;
	}
	else if(dir==2 && Escenario::getInstance()->getC(posX, posY-1)=='#'){
		return true;
	}
	else if(dir==3 && Escenario::getInstance()->getC(posX+1, posY)=='#'){
		return true;
	}
	else{
		return false;
	}
}

//Mediante éste método el personaje se puede mover a la derecha (girará 90 grados hacia la dcha.)
void CPersonaje::moverDerecha(void){

	if(!avanzandoX && !avanzandoY){ //Sólo podrá girar si no está avanzando en x e y...
		if(!enMovimiento){			//...y si no está girando sobre sí mismo
			anguloSig=angulo-90;	//Le restamos 90 grados
			enMovimiento=true;		//Ponemos la variable enMovimiento a true para que pueda moverse
			teclaD=true;			//Cambiamos el valor de teclaD a true
			if(dir!=0){				//Comprobamos que no nos salimos del rango de valores
				dir=dir-1;
			}
			else{
				dir=3;
			}
		}
		angulo-=0.5*frps;			//Disminuimos el angulo actual
	}
}

//Con este método podrá moverse hacia la izquierda (girará 90 grados a la izq.)
void CPersonaje::moverIzquierda(void){

	if(!avanzandoX && !avanzandoY){	//Sólo podrá girar si no está avanzando en x e y...
		if(!enMovimiento){			//...y si no está girando sobre sí mismo
			anguloSig=angulo+90;	//Le sumamos 90 grados
			enMovimiento=true;		//Ponemos la variable enMovimiento a true pra que pueda moverse
			teclaA=true;			//Cambiamos el valor de teclaA a true
			if(dir!=3){				//Comprobamos que no nos salimos del rango de valores
				dir=dir+1;
			}
			else{
				dir=0;
			}
		}
		angulo+=0.5*frps;			//Aumentamos el angulo actual
	}
}

//Si se pulsa la tecla "w" el personaje se moverá hacia delante
void CPersonaje::moverRecto(void){

	//Para poder avanzar en cualquier dirección comprueba que no se está moviendo. Después comprueba que no hay pared.
	//Cambia las variables necesarias para que avance hacia delante
	if(!avanzandoX && !avanzandoY){	
		if(angulo==0 && !hayParedDelante(realX, realY)){
				finalY=actualY-1;
				avanzandoY=true;
				avanzandoX=false;
				teclaW=true;
				dir=0;
			
		}

		else if((angulo==90 || angulo== -270) && !hayParedDelante(realX, realY)){
				finalX=realX+1;
				avanzandoX=true;
				avanzandoY=false;
				teclaW=true;
				dir=1;
		}

		else if((angulo==180 || angulo== -180) && !hayParedDelante(realX, realY)){
				finalY=actualY+1;
				avanzandoY=true;
				avanzandoX=false;
				teclaW=true;
				dir=2;
		}

		else if((angulo==270 || angulo== -90) && !hayParedDelante(realX, realY)){
				finalX=actualX-1;
				avanzandoX=true;
				avanzandoY=false;
				teclaW=true;
				dir=3;
		}
	}

}

//Si pulsamos la tecla "s" el personaje se moverá hacia atrás
void CPersonaje::moverAtras(void){
	
	//Antes de  avanzar en cualquier dirección comprueba que no se está moviendo. Después comprueba que no hay pared.
	//Cambia las variables necesarias para moverse hacia atrás
		if(!avanzandoX && !avanzandoY){
			if(angulo==0 && !hayParedDetras(realX, realY)){
				finalY=actualY+1;
				avanzandoY=true;
				avanzandoX=false;
				teclaS=true;
				dir=0;
			}

			else if((angulo==90 || angulo== -270) && !hayParedDetras(realX, realY)){
				finalX=actualX-1;
				avanzandoX=true;
				avanzandoY=false;
				teclaS=true;
				dir=1;
			}
			else if((angulo==180 || angulo== -180) && !hayParedDetras(realX, realY)){
				finalY=actualY-1;
				avanzandoY=true;
				avanzandoX=false;
				teclaS=true;
				dir=2;
			}
			else if((angulo==270 || angulo== -90) && !hayParedDetras(realX, realY)){
				finalX=actualX+1;
				avanzandoX=true;
				avanzandoY=false;
				teclaS=true;
				dir=3;
			}
		}
}


//Método para atrapar los fantasmas
void CPersonaje::encontrarFantasma(void){
	for(int i=0; i<g_num_malos; i++){ //Recorremos el array de "malos"
		//Si la posición de los dos coincide entonces entra en el if...
		if(fabs(g_fantasmas[i].getPosRealX()-getPositionRealX())<0.5
			&& fabs(g_fantasmas[i].getPosRealZ()-getPositionRealY())<0.5)
		{ 																							
		g_fantasmas[i].setAtrapado(true); //...y marcamos el fantasma como "atrapado"
		}
	}
}



//El método actualizar() se actualiza constantemente, para que el personaje se pueda mover correctamente.
//Aquí también se comprueba si ha atrapado algún fantasma.
void CPersonaje::actualizar(void){

	//calculamos los frames
	frps=getFPS();

	//Nos aseguramos de que el angulo no se sale del rango
	if(angulo==360 || angulo==-360){
		angulo=0;
	}

	//Evitamos que se mueva y avance a la vez; cuando una esté a true las otras a false y viceversa
	if(enMovimiento){ 
		avanzandoX=false;
		avanzandoY=false;
	}

	if(avanzandoX || avanzandoY){
		enMovimiento=false;
	}

	//Si están la variable enMovimiento y teclaD a true, gira a la dcha
	if(enMovimiento && teclaD){
		moverDerecha();
	}

	//Si están la variable enMovimiento y teclaA a true, gira a la izq
	if(enMovimiento && teclaA){
		moverIzquierda();
	}

	//El personaje deja de girar cuando el angulo actual se aproxima al de destino
	if(fabs(anguloSig-angulo)<0.5){
		enMovimiento=false;
		teclaA=false;
		teclaD=false;
	}

	//Si alguna de las variables avanzando y teclaW están a true se podrá mover hacia delante
	if((avanzandoX || avanzandoY) && teclaW){
		moverRecto();

		//el switch se ocupa de cambiar las variables realX y realY dependiendo de la direccion
		switch (dir)
		{
		case 0:
			realY-=0.005*frps;
			break;
		case 1:
			realX+=0.005*frps;
			break;
		case 2:
			realY+=0.005*frps;
			break;
		case 3:
			realX-=0.005*frps;
			break;
		}

		
	}
	
	//Si alguna de las variables avanzando y teclaS están a true se podrá mover hacia atras
	if((avanzandoX || avanzandoY) && teclaS){
		moverAtras();
		
		//el switch se ocupa de cambiar las variables realX y realY dependiendo de la direccion
		switch (dir)
		{
		case 0:
			realY+=0.005*frps;
			break;
		case 1:
			realX-=0.005*frps;
			break;
		case 2:
			realY-=0.005*frps;
			break;
		case 3:
			realX+=0.005*frps;
			break;
		}	

		
	}
	
	//Si está avanzando en el eje x y la posición real se aproxima a la de destino, entonces se para
	if(fabs(finalX-realX)<0.1 && avanzandoX){
		actualX=finalX;
		realX=actualX;
		avanzandoX=false;
		teclaW=false;
		teclaS=false;
	}

	//Si está avanzando en el eje y y la posición real se aproxima a la de destino, entonces se para
	if(fabs(finalY-realY)<0.1 && avanzandoY){
		actualY=finalY;
		realY=actualY;
		avanzandoY=false;
		teclaW=false;
		teclaS=false;
	}

	encontrarFantasma();
	
}

void CPersonaje::draw(void){

	glColor3f (0.5, 1.0, 0.5);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	
	glTranslatef(realX, realY, 0.0);
	setRotation();

	glRotatef(90.f,1.f,0.f,0.f);

	if (m_modelDisplayList)
		glCallList(m_modelDisplayList);

	glPopMatrix();
}
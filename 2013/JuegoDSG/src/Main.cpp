//main.cpp
//Autores: todos

#include "../stdafx.h"
#include "../inc/FrameRate.h"
#include "../inc/Camara.h"
#include "../inc/Personaje.h"
#include "../inc/Fantasma.h"
#include "../inc/Escenario.h"
#include "../inc/Iluminacion.h"


#define MOVE_STEP .4
#define ANGLE_STEP 0.2
#define PI 3.1416f

float g_xp=0.0f;
float g_yp=0.0f;
float g_zp=0.0f;
//float g_x=0.0f;
//float g_y=0.0f;
//float g_z=10.0f;
float g_roll= 0.0f;
float g_pitch= 0.0f;
float g_yaw= 0.0f;
int g_w;
int g_h;
float g_cubeAngle= 0.f;
float g_cubeAngleIn= 0.f;
float giro=1.0;
int angulo = 0;
float posx;
float posy;
float posz;
CCamara camMapa; 
CCamara camPpal; 

CPersonaje* cpersonaje = CPersonaje::Instance();//new CPersonaje();
Escenario* pEscenario= Escenario::getInstance();



void DrawScene(void)
{
	//limpiar el backbuffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//Primera cámara
	
	//posicionar la cámara
	float posx = cpersonaje->getPositionRealX(); 
	float posy = cpersonaje->getPositionRealY();
	float posxfinal = cpersonaje->getPositionFinalX();
	float posyfinal = cpersonaje->getPositionFinalY();

	camPpal.setAngulo(cpersonaje->getAngulo());
	camPpal.setPositionFinal(posxfinal, posyfinal);
	camPpal.setPosition(posx,posy,10);
	camPpal.setRotation(30.0,0.0,0.0);	//p
	camPpal.camara(false);
	
	//iluminar la escena
	iluminar(true);

	//dibujar todos los objetos
	cpersonaje->draw();
	pEscenario->draw();
	Fantasma::draw();
	

	//Segunda cámara
	glClear(GL_DEPTH_BUFFER_BIT);	
	//Posicion de la camara vista desde arriba	
//	camMapa.setPosition(posx,posy,10);	
//	camMapa.setRotation(0,0,0);
	//indicar con el valor booleano si es la camara general o no
	camMapa.camara(true);
		
	//iluminar la escena
	iluminar(false);

	//dibujar todos los objetos
	cpersonaje->draw();
	pEscenario->draw(false);
	Fantasma::draw();

}

void DrawSceneCam2(void)
{
	camPpal.camPPers(posx,posy,angulo);

	
	//iluminar la escena
	iluminar(true);

	//dibujar todos los objetos
	cpersonaje->draw();
	pEscenario->draw();
	Fantasma::draw();

	
	//Descomentar una vez terminado
	
/*
	//Segunda cámara
	glClear(GL_DEPTH_BUFFER_BIT);	
	//Posicion de la camara vista desde arriba	

	//indicar con el valor booleano si es la camara general o no
	camMapa.camara(true);
		
	//iluminar la escena
	iluminar(false);

	//dibujar todos los objetos
	cpersonaje->draw();
	pEscenario->draw(false);
	Fantasma::draw();*/

}

void DrawSceneIZQ(void)
{
	//limpiar el backbuffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	
	//posicionar la cámara
	float posx = cpersonaje->getPositionRealX(); 
	float posy = cpersonaje->getPositionRealY();
	float posxfinal = cpersonaje->getPositionFinalX();
	float posyfinal = cpersonaje->getPositionFinalY();
	camPpal.setPositionFinal(posxfinal, posyfinal);

	camPpal.setPosition(posx-1.5,posy,10);

	camPpal.setRotation(30.0,0.0,0.0);	

	camPpal.camara(false);
	
	//iluminar la escena
	iluminar(true);

	//dibujar todos los objetos
	cpersonaje->draw();
	pEscenario->draw();
	Fantasma::draw();
	

	//Segunda cámara
	glClear(GL_DEPTH_BUFFER_BIT);	
	//Posicion de la camara vista desde arriba	

	//indicar con el valor booleano si es la camara general o no
	camMapa.camara(true);
		
	//iluminar la escena
	iluminar(false);

	//dibujar todos los objetos
	cpersonaje->draw();
	pEscenario->draw(false);
	Fantasma::draw();

}

void DrawSceneDCH(void)
{
	//limpiar el backbuffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	//Primera cámara
	
	//posicionar la cámara
	float posx = cpersonaje->getPositionRealX(); 
	float posy = cpersonaje->getPositionRealY();
	float posxfinal = cpersonaje->getPositionFinalX();
	float posyfinal = cpersonaje->getPositionFinalY();
	camPpal.setPositionFinal(posxfinal, posyfinal);
	
	camPpal.setPosition(posx+1.5,posy,10);	
	camPpal.setRotation(30.0,0.0,0.0);	

	camPpal.camara(false);
	
	//iluminar la escena
	iluminar(true);

	//dibujar todos los objetos
	cpersonaje->draw();
	pEscenario->draw();
	Fantasma::draw();
	

	//Posicion de la camara vista desde arriba	
	glClear(GL_DEPTH_BUFFER_BIT);	
	

	//indicar con el valor booleano si es la camara general o no
	camMapa.camara(true);
		
	//iluminar la escena
	iluminar(false);

	//dibujar todos los objetos
	cpersonaje->draw();
	pEscenario->draw(false);
	Fantasma::draw();

}

void Reshape (int w, int h)
{
	//Reshape callback function
	camPpal.setDimension(h,w);
	camMapa.setDimension(h,w);
	g_h= h;
	g_w= w;

}

void Keyboard(unsigned char key,int x, int y)
{
	//keyboard callback function
	switch (key)
	{
	case 'w':	if(!getEfectoMalo()) cpersonaje->moverRecto(); break;
	case 's':	if(!getEfectoMalo()) cpersonaje->moverAtras(); break;
	case 'd':	if(!getEfectoMalo()) cpersonaje->moverDerecha(); break;
	case 'a':	if(!getEfectoMalo()) cpersonaje->moverIzquierda(); break;
	//case 'n':	glutDisplayFunc(DrawSceneCam2);break; //Vista en primera persona
	case 'v':	glutDisplayFunc(DrawScene);break;//volver a la vista principal
	case 'c':	glutDisplayFunc(DrawSceneIZQ);break; //vista a la izquierda del personaje
	case 'b':	glutDisplayFunc(DrawSceneDCH);break; //vista a la derecha del personaje
	case 27: exit(0);
	}
}

int main(int argc, char** argv)
{
	//INIT GLUT/////////////////////
	////////////////////////////////
	//init window and OpenGL context
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (1024, 768); 
	glutCreateWindow (argv[0]);
//	glutFullScreen();
	glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF); //desactivar la repetición de teclas de Windows
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	//callback functions
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);

	pEscenario->cargarEscenario("mapas/ejemplo.txt");
	Fantasma::loadModel();
	cpersonaje->loadModel();

	initFrameRate(); //principalmente determina el inicio del primer frame
	while (1)
	{
		//UPDATE////////////////////
		////////////////////////////
		//queued events?
		glutMainLoopEvent();
		if(!getEfectoMalo()) {
			cpersonaje->actualizar();
			Fantasma::comenzarMovimiento();
		}
		//RENDER////////////////////
		////////////////////////////
		glutPostRedisplay();
		glutSwapBuffers();

		endFrame();
	}

	pEscenario->releaseInstance();

	return 0;
}
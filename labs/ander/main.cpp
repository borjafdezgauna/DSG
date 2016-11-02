// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Cube.h"
#include "ColladaModel.h"


float g_x=0.0f;
float g_y=0.0f;
float g_z=10.0f;
float g_roll= 0.0f;
float g_pitch= 0.0f;
float g_yaw= 0.0f;
int g_w;
int g_h;
float g_cubeAngle= 0.f;

//declaramos instancias de cubo
Cube g_cubo1, g_cubo2;
ColladaModel venom("Venom.dae");


void Set3DView()
{
	//set projection matrix
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

	//set modelview matrix
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();

	glRotatef(-g_roll, 0.0, 0.0, 1.0);	
	glRotatef(-g_yaw, 0.0, 1.0, 0.0);
	glRotatef(-g_pitch, 1.0, 0.0, 0.0);	
	glTranslatef(-g_x, -g_y, -g_z);
		
}



//void DrawCube()
//{
//	glColor3f (0.5, 1.0, 0.5);
//	glMatrixMode(GL_MODELVIEW);
//	
//	glRotatef(g_cubeAngle,1.0,0.0,0.0);
//	glutWireCube (1.0);
//}

void DrawScene(void)
{
	//clean the backbuffer
	glClear (GL_COLOR_BUFFER_BIT);

			//NOTA: si quisieramos vaciar el front bufer tambien
			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//viewing transformation
	Set3DView();

	//draw the cube
	g_cubo1.draw();
	g_cubo2.draw();
	venom.draw();

}

void Reshape (int w, int h)
{
	//Reshape callback function
	g_h= h;
	g_w= w;
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
}

int main(int argc, char** argv)
{
	

	g_cubo1.setPosition(0.0, 0.5, -1.0);
	g_cubo1.setScale(0.5, 0.5, 0.5);
	
	g_cubo2.setPosition(2.0, 0.0, -3.0);
	g_cubo2.setScale(2.0, 2.0, 2.0);

	g_cubo1.setColor(1.0, 0.0, 0.0);
	g_cubo2.setColor(0.0, 0.0, 1.0);

	//INIT GLUT/////////////////////
	////////////////////////////////
	//init window and OpenGL context
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (1024, 768); 
	glutCreateWindow (argv[0]);
//	glutFullScreen();
//PONEMOS AQUI EL VECTOR DIRECCION DE LA LUZ, DESPUES DE GLLOADIDENTITY()
	GLfloat light_position[] = { -1, -1, -1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	//añadimos para el culling despues de definir bien la normal de los vertices y caras en Cube.cpp
	glCullFace(GL_BACK);
	//mode = [GL_FRONT, GL_BACK, GL_FRONT_AND_BACK];
	// CON FRONT quitamos la cara delantera, con back las traseras y con front and back no vemos nada xd
	glEnable(GL_CULL_FACE);


	//ILUMINACION
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat light_specular[]= { 1.0, 1.0, 1.0, 1.0 };
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);


	//callback functions
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);
	glutMouseFunc(Mouse);
	glutMotionFunc(MouseMotion);


	while (1)
	{
		TratarTeclado();
		//UPDATE////////////////////
		////////////////////////////
		//"move" the cube
		g_cubeAngle+= 0.1;
		//queued events?
		glutMainLoopEvent();
		Raton();

		//RENDER////////////////////
		////////////////////////////
		glutPostRedisplay();
		glutSwapBuffers();
	}
   return 0;
}
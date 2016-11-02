// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "keyboard.h"
#include "mouse.h"
#include "TimeCounter.h"
#include "Cube.h"

#include "../../Simple OpenGL Image Library/src/SOIL.h"
#pragma comment (lib,"../../Debug/SOIL.lib")

float g_x=0.0f;
float g_y=0.0f;
float g_z=10.0f;
float g_roll= 0.0f;
float g_pitch= 0.0f;
float g_yaw= 0.0f;
int g_w;
int g_h;

Cube cubo1, cubo2;


void Set3DView()
{
	//set projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);

	//set modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(-g_roll, 0.0, 0.0, 1.0);
	glRotatef(-g_yaw, 0.0, 1.0, 0.0);
	glRotatef(-g_pitch, 1.0, 0.0, 0.0);
	glTranslatef(-g_x, -g_y, -g_z);
}


void DrawScene(void)
{
	//clean the backbuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//viewing transformation
	Set3DView();

	//draw the cube
	cubo1.draw();
	cubo2.draw();

}

void Reshape(int w, int h)
{
	//Reshape callback function
	g_h = h;
	g_w = w;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
}

int main(int argc, char** argv)
{

	//INIT GLUT/////////////////////
	////////////////////////////////
	//init window and OpenGL context
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1024, 768);
	glutCreateWindow(argv[0]);
	//glutFullScreen();

	//Evitar que windows use funci�n de repetici�n
	glutSetKeyRepeat(false);


	//callback functions
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(upKeyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);

	//culling
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);


	

	//Luces
	GLfloat light_ambient[] = { 0.0,1.0,0.0,1.0 };
	GLfloat light_diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light_specular[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light_position[] = { -1.0, -1.0, -1.0, 0.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);



	//Propiedades del cubo
	cubo2.setPosition(3, 3, 3);
	cubo1.setColor(1, 0, 0);
	cubo2.setColor(0, 1, 1);
	cubo2.setScale(2, 2, 2);

	//Texuras 2D
	glEnable(GL_TEXTURE_2D);
	cubo1.setTexture("C:/Users/asier/Source/Repos/DSG/labs/asierlopez/textura2.png");





	double g_cubeAngle = 0;

	SetVecesPerSecond(500);

	while (1)
	{
		StartCounter();

		ejecutarTeclado();
		ejecutarRaton();

		//UPDATE////////////////////
		////////////////////////////
		//"move" the cube
		g_cubeAngle += 0.1;
		cubo1.setRotation(g_cubeAngle, 0, 0);
		//queued events?
		glutMainLoopEvent();


		//RENDER////////////////////
		////////////////////////////
		glutPostRedisplay();
		glutSwapBuffers();


		Regular();
		
	}
   return 0;
}
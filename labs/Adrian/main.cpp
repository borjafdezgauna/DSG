// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Cube.h"
#include "ColladaModel.h"

#define MOVE_STEP .4
#define ANGLE_STEP 0.2
#define PI 3.1416f

float g_x=0.0f;
float g_y=0.0f;
float g_z=10.0f;
float g_roll= 0.0f;
float g_pitch= 0.0f;
float g_yaw= 0.0f;
int g_w;
int g_h;
float g_cubeAngle= 0.f;
Cube g_cubo1, g_cubo2;
ColladaModel cm("EM208_heavy.dae");



/*void Keyboard(unsigned char key,int x, int y)
{
	//keyboard callback function
	switch (key)
	{
	case '8':	g_x-= MOVE_STEP*sin(g_yaw*PI/180);
				g_z-= MOVE_STEP*cos(g_yaw*PI/180);break;
	case '2':	g_x+= MOVE_STEP*sin(g_yaw*PI/180);
				g_z+= MOVE_STEP*cos(g_yaw*PI/180);break;
	case '6': g_yaw-= ANGLE_STEP; break;
	case '4': g_yaw+= ANGLE_STEP; break;
	case 27: exit(0);
	}
}*/

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
	GLfloat light_position[] = { -1.0,-1.0,-1.0,0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
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
	//g_cubo1.setPosition(0.0, 0.0, 0.0);
	//g_cubo1.setColor(1.0, 0.0, 0.0);
	//g_cubo1.setTexture("C:/Users/Adrián/Source/Repos/DSG/labs/Adrian/text_1.jpg");
	//g_cubo2.setPosition(5.0, 0.0, 0.0);
	//g_cubo2.setColor(0.0, 0.0, 1.0);
	//g_cubo2.setTexture("C:/Users/Adrián/Source/Repos/DSG/labs/Adrian/text_2.jpg");
	//clean the backbuffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//viewing transformation
	Set3DView();

	//draw the cube
	//DrawCube();
	
	
	//g_cubo1.draw();
	//g_cubo2.draw();
	cm.draw();

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

	//INIT GLUT/////////////////////
	////////////////////////////////
	//init window and OpenGL context
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (1024, 768);
	glutCreateWindow (argv[0]);
	//glutFullScreen();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV, GL_BLEND);
	glTexParameterf(GL_TEXTURE_ENV, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//callback functions
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(Keyboard_up);
	glutMouseFunc(MouseW);
	glutMotionFunc(MouseMotionW);

	cm.setIdTexture();
	

	while (1)
	{
		//QueryPerformanceCounter
		//QueryPerformanceFrecuency
		//declarar dos enteros int64
		//sleep(1/60-(t2-t1))

		Keyboard_pulsar();
		//UPDATE////////////////////
		////////////////////////////
		//"move" the cube
		g_cubeAngle+= 0.1;
		//queued events?
		glutMainLoopEvent();
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		GLfloat light_ambient[] = { 0.0,0.0,0.0,1.0 };
		GLfloat light_diffuse[] = { 1.0,1.0,1.0,1.0 };
		GLfloat light_specular[] = { 1.0,1.0,1.0,1.0 };
		
		//GLfloat light_spot_direction[] = { 0.0,0.0,-1.0 };
		glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
		
		//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light_spot_direction);
		//glutSetKeyRepeat(false);

		//RENDER////////////////////
		////////////////////////////
		glutPostRedisplay();
		glutSwapBuffers();
	}
   return 0;
}
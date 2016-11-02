// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../Simple OpenGL Image Library/src/SOIL.h"
#include "Cube.h"
#include "ColladaModel.h"
#include "keyboard.h"
#include "mouse.h"
#pragma comment(lib,"../../Debug/SOIL.lib")

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
ColladaModel colla("Venom.dae");
//ColladaModel colla("EM208_heavy.dae");

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
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}



void DrawCube()
{
	glColor3f (0.5, 1.0, 0.5);
	glMatrixMode(GL_MODELVIEW);
	
	//glRotatef(g_cubeAngle,1.0,0.0,0.0);
	glutWireCube (1.0);
}

void DrawScene(void)
{
	//clean the backbuffer
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//viewing transformation
	Set3DView();

	//draw the cube
	//DrawCube();


	/*g_cubo1.draw();
	g_cubo2.draw();*/

	colla.draw();


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
	g_cubo1.setPosition(0.5, 1.5, 0.0);
	g_cubo2.setPosition(0.0, 0.0, -3.0);

	g_cubo1.setScale(0.5, 1.5, 2.5);
	g_cubo2.setScale(1.5, 2.5, 4.5);

	g_cubo1.setColor(0.1, 0.5, 1.0);
	g_cubo2.setColor(0.5, 0.1, 0.5);

	

	//INIT GLUT/////////////////////
	////////////////////////////////

	//init window and OpenGL context
	glutInit(&argc, argv);
	
	
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (1024, 768); 
	glutCreateWindow (argv[0]);
	//glutFullScreen();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	g_cubo1.generateTexture("C:/Users/asier/Source/Reposs/DSG/labs/asierrodriguez/km.png");
	
	//g_cubo2.generateTexture("C:/Users/asier/Source/Reposs/DSG/labs/asierrodriguez/km2.png");
	// iluminacion
	GLfloat light_specularn[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 4.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specularn);


	//AQUI
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	//evitar repetición windows
	glutSetKeyRepeat(false);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	colla.setTexture();

	//callback functions
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(PressedKeyboard);
	glutMouseFunc(updateMouseUp);
	glutMotionFunc(updateMouseAlways);

	while (1)
	{
		int ang = 0;
		updateMovement();
		// con este va solo hacia un lado cuando pulsas hasta que sueltas
		OnMouseMovement();


		//con este gira cuando cambias el raton
		mouseAlwaysMoving();


		//UPDATE////////////////////
		////////////////////////////
		//"move" the cube
		g_cubeAngle+= 0.1;
		//queued events?
		glutMainLoopEvent();

		/*g_cubo1.setRotation(45 + ang, 45 + ang, 45 + ang);
		g_cubo2.setRotation(45 + ang, 45 + ang, 45 + ang);*/

		//RENDER////////////////////
		////////////////////////////
		glutPostRedisplay();
		glutSwapBuffers();

		ang = ang + 1;
	}
   return 0;
}
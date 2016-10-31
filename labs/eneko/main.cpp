// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "keyboard.h"
#include "Mouse.h"
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
float g_cubeAngle= 0.f;
Cube g_cubo1, g_cubo2;
unsigned int identi;
unsigned int identi2;



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

	//clean the backbuffer
	glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	//viewing transformation
	Set3DView();

	
	
	//draw the cube
	g_cubo1.setPosition(-0.8, 0.8, 0.8);
	g_cubo1.setColor(1,1,1);
	g_cubo1.setScale(0.5, 0.5, 0.5);
	g_cubo1.setIdenti(identi);
	g_cubo1.draw();
	g_cubo2.setPosition(0.0, 0.0, 0.0);
	g_cubo2.setColor(1,1 ,1);
	g_cubo2.setScale(0.3, 0.3, 0.3);
	g_cubo2.setIdenti(identi2);
	g_cubo2.draw();


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
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
	glutInitWindowSize (1024, 768); 
	glutCreateWindow (argv[0]);
	//glutFullScreen();
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_ambient[] = { 0.0,0.0,0.0,1.0 };
	GLfloat light_diffuse[] = { 1.0,1.0,1.0,1.0 };
	GLfloat light_specular[] = { 0.0,0.0,0.0,0.0 };
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glEnable(GL_TEXTURE_2D);
	identi = SOIL_load_OGL_texture("C:/Users/Eneko/Source/Repos/DSG/labs/eneko/texturas_papel10.jpg", 0, 0, 0);
	identi2 = SOIL_load_OGL_texture("C:/Users/Eneko/Source/Repos/DSG/labs/eneko/text.png", 0, 0, 0);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	
	//callback functions
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(pressKeyboard);
	glutMouseFunc(pulsMouse);
	glutMotionFunc(estMouse);
	glutSetKeyRepeat(true);
	
	while (1){
		moverTeclado();
		//moveMouse();
	
		//glutKeyboardFunc(moverTeclado);
		//UPDATE////////////////////
		////////////////////////////
		//"move" the cube
		g_cubeAngle+= 0.1;
		//queued events?
		glutMainLoopEvent();
		if (control % 2 != 0)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (control1 % 2 != 0) {
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glDisable(GL_DEPTH_TEST);
		}
		else {
			glEnable(GL_DEPTH_TEST);
			glCullFace(GL_BACK);
			glDisable(GL_CULL_FACE);
		
		}
		//RENDER////////////////////
		////////////////////////////
		glutPostRedisplay();
		glutSwapBuffers();
	}
   return 0;
   
}
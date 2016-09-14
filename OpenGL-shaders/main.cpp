// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GLExtensions.h"

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



void Keyboard(unsigned char key,int x, int y)
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
}

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

GLenum my_program;
GLenum my_vertex_shader;
GLenum my_fragment_shader;

void DrawCube()
{
	glMatrixMode(GL_MODELVIEW);
	glRotatef(g_cubeAngle,1.0,0.0,0.0);


	glBegin(GL_QUADS);
		glNormal3f(0.0,0.0,1.0);
		glVertex3f(0.5,-0.5,0.5);
		glVertex3f(0.5,0.5,0.5);
		glVertex3f(-0.5,0.5,0.5);
		glVertex3f(-0.5,-0.5,0.5);
	glEnd();
}



void DrawScene(void)
{
	//clean the backbuffer
	glClear (GL_COLOR_BUFFER_BIT);

	//viewing transformation
	Set3DView();

	//draw the cube
	DrawCube();

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

#define NUM_MAX_LINES 1024
#define MAX_LINE_LENGTH 1024

void loadShaderFromFile(char* filename, char **pBuffer)
{
	int i= 0;
	char line[MAX_LINE_LENGTH];
	FILE *pFile;
	fopen_s(&pFile,filename,"r");
	if (pFile)
	{
		while(!feof(pFile))
		{
			fgets(line,MAX_LINE_LENGTH,pFile);

			pBuffer[i]= new char [strlen(line)+1];
			strcpy_s(pBuffer[i],strlen(line)+1,line);
			i++;
		}
		pBuffer[i]= 0;
		fclose(pFile);
	}

}



void initShaders()
{
	char *vertexProgram[NUM_MAX_LINES];
	char *fragmentProgram[NUM_MAX_LINES];


	QueryGLExtFunctionPointers();

	loadShaderFromFile("shaders/vp0.vert",vertexProgram);
	loadShaderFromFile("shaders/fp0.frag",fragmentProgram);
	 
	// Create Shader And Program Objects
	my_program = glCreateProgramObjectARB();
	my_vertex_shader = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	my_fragment_shader = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	 
	GLcharARB log[512];
	int logSize;

	// Load Shader Sources
	glShaderSourceARB(my_vertex_shader, 1, (const GLcharARB**)vertexProgram,NULL);
	glShaderSourceARB(my_fragment_shader, 1, (const GLcharARB**)fragmentProgram, NULL);

	 
	// Compile The Shaders


	glCompileShaderARB(my_fragment_shader);
		glGetInfoLogARB(my_fragment_shader,512,&logSize,log);
		glCompileShaderARB(my_vertex_shader);




	glGetInfoLogARB(my_fragment_shader,512,&logSize,log);


	// Attach The Shader Objects To The Program Object
	glAttachObjectARB(my_program, my_vertex_shader);
	glAttachObjectARB(my_program, my_fragment_shader);	 

	// Link The Program Object
	glLinkProgramARB(my_program);

	// Use The Program Object Instead Of Fixed Function OpenGL
	glUseProgramObjectARB(my_program);
}

int main(int argc, char** argv)
{

	//INIT GLUT/////////////////////
	////////////////////////////////
	//init window and OpenGL context
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize (1024, 768); 
	glutCreateWindow (argv[0]);
	//glutFullScreen();

	initShaders();

	//callback functions
	glutDisplayFunc(DrawScene);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);


	while (1)
	{
		//UPDATE////////////////////
		////////////////////////////
		//"move" the cube
		g_cubeAngle+= 0.1;
		//queued events?
		glutMainLoopEvent();


		//RENDER////////////////////
		////////////////////////////
		glutPostRedisplay();
		glutSwapBuffers();
	}
   return 0;
}
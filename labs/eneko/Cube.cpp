#include "stdafx.h"
#include "Cube.h"


Cube::Cube()
{
}


Cube::~Cube()
{
}

void Cube::draw() 
{
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(-mx, -my ,-mz);
	/*glRotatef(-mroll, 0.0, 0.0, 1.0);
	glRotatef(-myaw, 0.0, 1.0, 0.0);
	glRotatef(-mpitch, 1.0, 0.0, 0.0);*/
	glScaled(esX, esY, esZ);

	//Dibujar el cubo
	glBegin(GL_QUADS);
	//Primer lado
	//glColor3d(c1,c2, c3);
	GLfloat mat_ambient[] = { c1,c2,c3,1.0 };
	GLfloat mat_diffuse[] = { c1,c2,c3,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	//Segundo lado
	
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	//Tercer lado
	
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	//Cuarto lado

	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	//QuintoLado

	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	//SextoLado
	
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glEnd();
	glPopMatrix();
}

void Cube::setPosition(double x, double y, double z)
{
	mx = x;
	my = y;
	mz = z;
}

void Cube::setRotation(double pitch, double yaw, double row)
{
	myaw = yaw;
	mpitch = pitch;
	mroll = row;

}

void Cube::setScale(double x, double y, double z)
{
	esX = x;
	esY = y;
	esZ = z;
}

void Cube::setColor(double color1, double color2, double color3)
{
	c1 = color1;
	c2 = color2;
	c3 = color3;
}

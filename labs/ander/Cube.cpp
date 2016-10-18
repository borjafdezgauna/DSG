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
	
	

	glPushMatrix();
	ApplyObjectTransformation();
	//dibujar el cubo

	glBegin(GL_QUADS);

	//1ºcara
	//glColor3f(0, 0, 1);
	
	glColor3f(m_colorr, m_colorg, m_colorb);

	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);

	//2ºcara
	//glColor3f(0, 1, 0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);

	//3ºcara
	//glColor3f(0, 1, 1);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);

	//4ºcara
	//glColor3f(1, 0, 0);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5,  -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	//5ºcara
	//glColor3f(1, 0, 1);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);

	//6ºcara
	//glColor3f(1, 1, 0);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);

	glEnd();

	glPopMatrix();
}

void Cube::setPosition(double x, double y, double z) {
	m_x = x;
	m_y = y;
	m_z = z;
}

void Cube::setRotation(double pitch, double yaw, double roll) {
	m_pitch = pitch;
	m_yaw = yaw;
	m_roll = roll;
}

void Cube::setScale(double x, double y, double z) {
	m_scalex = x;
	m_scaley = y;
	m_scalez = z;
}

void Cube::setColor(float r, float g, float b) {
	m_colorr = r;
	m_colorg = g;
	m_colorb = b;
	
}


void Cube::ApplyObjectTransformation() {
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(m_x, m_y, m_z);
	glRotatef(m_pitch, 1.0, 0.0, 0.0);
	glRotatef(m_yaw, 0.0, 1.0, 0.0);
	glRotatef(m_roll, 0.0, 0.0, 0.1);
	
}
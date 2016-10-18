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
	glTranslated(m_x, m_y, m_z);
	glColor3i(m_r, m_g, m_b);
	//glScaled(m_sx, m_sy, m_sz);	
	//glRotated(m_pitch, m_yaw, m_roll);

	glBegin(GL_QUADS);

	//cara delantera
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);	
	//cara superior
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);	
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	//cara derecha	
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	//cara inferior	
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	//cara izquierda
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	//cara trasera
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	
	glEnd();

	glPopMatrix();
}

void Cube::setPosition(double x, double y, double z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

void Cube::setRotation(double pitch, double yaw, double roll)
{
	m_yaw = yaw;
	m_pitch = pitch;
	m_roll = roll;
}

void Cube::setScale(double x, double y, double z)
{
	m_sx = x;
	m_sy = y;
	m_sz = z;
}

void Cube::setColor(int r, int g, int b)
{
	m_r = r;
	m_g = g;
	m_b = b;
}




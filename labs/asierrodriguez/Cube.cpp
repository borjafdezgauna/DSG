#include "stdafx.h"
#include "Cube.h"


Cube::Cube()
{
}


Cube::~Cube()
{
}

void Cube::draw() {
	//Dibujar el cubo

	glPushMatrix();
	glTranslated(m_x, m_y, m_z);
	//glRotated(m_roll, m_yaw, m_pitch);
	glScaled(m_scale_x, m_scale_y, m_scale_z);
	glColor3d(m_color_r, m_color_g, m_color_b);
	glRotated(m_yaw, 0, 1, 0);
	glRotated(m_pitch, 1, 0, 0);
	glRotated(m_roll, 0, 0, 1);

	glBegin(GL_QUADS);

	//Cara frontal
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);

	//Cara dcha
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);

	//Cara izq
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);

	//Cara trasera
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
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
	m_pitch = pitch;
	m_yaw = yaw;
	m_roll = roll;
}

void Cube::setScale(double x, double y, double z)
{
	m_scale_x = x;
	m_scale_y = y;
	m_scale_z = z;
}

void Cube::setColor(double r, double g, double b)
{
	m_color_r = r;
	m_color_g = g;
	m_color_b = b;
}

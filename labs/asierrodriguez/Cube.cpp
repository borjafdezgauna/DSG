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
	GLfloat mat_ambient[] = { c1,c2,c3,1.0 };
	GLfloat mat_diffuse[] = { c1,c2,c3,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat low_shininess[] = { 5.0 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);

	glPushMatrix();
	glTranslated(m_x, m_y, m_z);
	//glRotated(m_roll, m_yaw, m_pitch);
	glScaled(m_scale_x, m_scale_y, m_scale_z);
	glRotated(m_yaw, 0, 1, 0);
	glRotated(m_pitch, 1, 0, 0);
	glRotated(m_roll, 0, 0, 1);

	glBegin(GL_QUADS);

	//cara delantera
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	//cara superior
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	//cara derecha	
	glNormal3f(1.0, 0.0, 0.0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	//cara inferior	
	glNormal3f(0.0, -1.0, 0.0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);
	//cara izquierda
	glNormal3f(-1.0, 0.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	//cara trasera
	glNormal3f(0.0, 0.0, -1.0);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);


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

void Cube::setColor(double color1, double color2, double color3)
{
	c1 = color1;
	c2 = color2;
	c3 = color3;
}

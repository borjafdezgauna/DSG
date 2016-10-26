#include "stdafx.h"
#include "Cube.h"
#include "../../Simple OpenGL Image Library/src/SOIL.h"
#pragma comment(lib,"../../Debug/SOIL.lib")

Cube::Cube()
{
	m_sx = 1;
	m_sy = 1;
	m_sz = 1;
}


Cube::~Cube()
{
}



void Cube::draw()
{
	glPushMatrix();
	glTranslated(m_x, m_y, m_z);
	//glColor3d(m_r, m_g, m_b);
	glScaled(m_sx, m_sy, m_sz);	
	//glRotated(m_yaw, 0, 1, 0);
	//glRotated(m_pitch, 1, 0, 0);
	//glRotated(m_roll, 0, 0, 1);

	id = id_textura();

	glBindTexture(GL_TEXTURE_2D, id);

	glBegin(GL_QUADS);

	GLfloat mat_ambient[] = { m_r,m_g,m_b,1.0 };
	GLfloat mat_diffuse[] = { m_r,m_g,m_b,1.0 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);

	//cara delantera
	glNormal3f(0.0, 0.0, 1.0);
	glTexCoord2f(0.0,1.0);
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(0.0,0.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1.0,0.0);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1.0,1.0);
	glVertex3f(0.5, 0.5, 0.5);	
	//cara superior
	glNormal3f(0.0, 1.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5, 0.5, -0.5);
	//cara derecha	
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5, 0.5, -0.5);
	//cara inferior	
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.5, -0.5, 0.5);
	//cara izquierda
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, -0.5, -0.5);
	//cara trasera
	glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2f(1.0, 1.0);
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

void Cube::setColor(double r, double g, double b)
{
	m_r = r;
	m_g = g;
	m_b = b;
}

void Cube::setTexture(const char *text)
{
	textura = text;
}

int Cube::id_textura()
{
	unsigned int x = SOIL_load_OGL_texture(textura, 0, 0, 0);
	return x;
}


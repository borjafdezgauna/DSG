#include "stdafx.h"
#include "Cube.h"


Cube::Cube()
{
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
}


Cube::~Cube()
{
}

void Cube::draw()
{
	glPushMatrix();

	//transformaciones
	glTranslated(x, y, z);
	glRotated(yaw, 0, 1, 0);
	glRotated(pitch, 1, 0, 0);
	glRotated(roll, 0, 0, 1);
	glColor3d(red, green, blue);
	glScaled(scaleX, scaleY, scaleZ);

	//dibujar el cubo
	glBegin(GL_QUADS);

	//cara alante
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);

	//cara arriba
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);

	//cara atras
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);

	//cara abajo
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);

	//cara derecha
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);

	//cara izquierda
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, 0.5);

	glEnd();

	//rescatar matriz
	glPopMatrix();
}

void Cube::setPosition(double x, double y, double z)
{
	Cube::x = x;
	Cube::y = y;
	Cube::z = z;
}

void Cube::setRotation(double yaw, double pitch, double roll)
{
	Cube::yaw = yaw;
	Cube::pitch = pitch;
	Cube::roll = roll;
}

void Cube::setScale(double scaleX, double scaleY, double scaleZ)
{
	Cube::scaleX = scaleX;
	Cube::scaleY = scaleY;
	Cube::scaleZ = scaleZ;
}

void Cube::setColor(double red, double green, double blue)
{
	Cube::red = red;
	Cube::green = green;
	Cube::blue = blue;
}



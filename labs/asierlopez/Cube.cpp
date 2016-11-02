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
	//glColor3d(red, green, blue);
	glScaled(scaleX, scaleY, scaleZ);

	//iluminacion del material
	//GLfloat mat_ambient[] = { red,green,blue,1.0 };
	//GLfloat mat_diffuse[] = { red,green,blue,1.0 };
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	
	//textura seleccionador
	glBindTexture(GL_TEXTURE_2D, textura);

	//dibujar el cubo
	glBegin(GL_QUADS);

	//cara alante
	//glTexCoord3f
	glNormal3f(0, 0, 1);  //normal de la luz
	glTexCoord2f(1.0, 0.0);  // punto para la textura
	glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(0.5, 0.5, 0.5);
	

	//cara arriba
	glNormal3f(0, 1, 0);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);

	//cara atras
	glNormal3f(0, 0, -1);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);

	//cara abajo
	glNormal3f(0, -1, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);

	//cara derecha
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	
	

	//cara izquierda
	glNormal3f(-1, 0, 0);
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

void Cube::setTexture(char * file)
{
	Cube::textura = SOIL_load_OGL_texture(file, 0, 0, 0);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND); //para interpretar coordenadas fuera de 0 y 1 // afecta para el venom
}



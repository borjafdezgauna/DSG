/*
 * Escenario.cpp
 *
 *  Created on: 27/11/2013
 *      Author: dowdyph0
 */
#include "../stdafx.h"


#include "../inc/Escenario.h"

#include "../inc/Fantasma.h"
#include "../inc/Personaje.h"

using namespace std;

#define NUM_QUADS_X_S 240
#define NUM_QUADS_Y_S 240
#define NUM_QUADS_X_B 20
#define NUM_QUADS_Y_B 20


Escenario* Escenario::pInstance = 0;

int Escenario::m_alto= 0;
int Escenario::m_ancho= 0;
int Escenario::m_displayListHQ= 0;
int Escenario::m_displayListLQ= 0;

int texturaSuelo = 0;
int texturaBloque = 0;

CPersonaje* pers;


/*
 * Genera los objetos 3D del escenario en funcion del contenido
 * de la variable matrizMapa
 */

float Escenario::getLadoX() {
	return (float)m_ancho;
}

float Escenario::getLadoZ() {
	return (float)m_alto;
}

float Escenario::getAlto() {
	return ALTO_BLOQUE;
}

void Escenario::draw(bool highQ)
{
	if (highQ)
		glCallList(m_displayListHQ);
	else
		glCallList(m_displayListLQ);
}

void Escenario::drawFloor(bool highQ) {

	float xbase, ybase;
	float xquadsize, yquadsize;
	int numQuadsX,numQuadsY;
	if (highQ)
	{
		numQuadsX= NUM_QUADS_X_S;
		numQuadsY= NUM_QUADS_Y_S;
	}
	else
	{
		numQuadsX= NUM_QUADS_X_S / 2;
		numQuadsY= NUM_QUADS_Y_S / 2;
	}

	xquadsize= (float) m_ancho/ (float)numQuadsX;
	yquadsize= (float) m_alto/ (float)numQuadsY;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texturaSuelo);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBegin(GL_QUADS);



	for (int i= 0; i<numQuadsX; i++)
		for (int j= 0; j<numQuadsY; j++)
		{
			xbase= (float)i*xquadsize;
			ybase= (float)j*yquadsize;
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(xbase, ybase);glVertex3f(xbase, ybase,0.0f);
			glTexCoord2f(xbase+xquadsize, ybase);glVertex3f(xbase+xquadsize, ybase,0.0f);
			glTexCoord2f(xbase+xquadsize, ybase+yquadsize);glVertex3f(xbase+xquadsize, ybase+yquadsize,0.0f);
			glTexCoord2f(xbase, ybase+yquadsize);glVertex3f(xbase, ybase+yquadsize,0.0f);
			
		}
	glEnd();
}

void Escenario::drawBlock(int x, int z,bool highQ) {
	float xbase, ybase;
	float xquadsize, yquadsize;
	xquadsize= 1.f;
	yquadsize= 1.f;
	xbase= (float)x*xquadsize;
	ybase= (float)z*yquadsize;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslatef(xbase, ybase, 0.0);

	glBindTexture(GL_TEXTURE_2D, texturaBloque);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glBegin(GL_QUADS);

	//Cara de atrás
	/*glNormal3f(0.0, 0.0, -1.0);
	glTexCoord2f(0.0,0.0);glVertex3f( 1.0, 1.0, 0.0);
	glTexCoord2f(1.0,0.0);glVertex3f(1.0, 0.0, 0.0);
	glTexCoord2f(1.0,1.0);glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(0.0,1.0);glVertex3f(0.0, 1.0, 0.0);*/

	//Cara de arriba
	glNormal3f(0.0, 0.5, 0.0);
	glTexCoord2f(0.0,0.0);glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(1.0,0.0);glVertex3f(0.0, 1.0, 0.0);
	glTexCoord2f(1.0,1.0);glVertex3f(0.0, 1.0, 1.0);
	glTexCoord2f(0.0,1.0);glVertex3f(1.0, 1.0, 1.0);

	int numQuadsX,numQuadsY;
	if (highQ)
	{
		numQuadsX= NUM_QUADS_X_B;
		numQuadsY= NUM_QUADS_Y_B;
	}
	else
	{
		numQuadsX= NUM_QUADS_X_B / 2;
		numQuadsY= NUM_QUADS_Y_B / 2;
	}

	//Cara de enfrente: debe tener más vértices
	float xbase2, ybase2;
	float xquadsize2, yquadsize2;
	xquadsize2 = (float) xquadsize / (float)numQuadsX;
	yquadsize2 = (float) yquadsize / (float)numQuadsY;
	for (int i= 0; i<numQuadsX; i++)
		for (int j= 0; j<numQuadsY; j++)
		{
			xbase2= (float)i*xquadsize2;
			ybase2= (float)j*yquadsize2;
			glNormal3f(0.0, 0.0, 1.0);
			glTexCoord2f(xbase2, ybase2);glVertex3f(xbase2, ybase2,1.0f);
			glTexCoord2f(xbase2+xquadsize2, ybase2);glVertex3f(xbase2+xquadsize2, ybase2,1.0f);
			glTexCoord2f(xbase2+xquadsize2, ybase2+yquadsize2);glVertex3f(xbase2+xquadsize2, ybase2+yquadsize2,1.0f);
			glTexCoord2f(xbase2, ybase2+yquadsize2);glVertex3f(xbase2, ybase2+yquadsize2,1.0f);
		}

	//Cara de abajo
	glNormal3f(0.0, -1.0, 0.0);
	glTexCoord2f(0.0,0.0);glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1.0,0.0);glVertex3f(1.0, 0.0, 0.0);
	glTexCoord2f(1.0,1.0);glVertex3f(1.0, 0.0, 1.0);
	glTexCoord2f(0.0,1.0);glVertex3f(0.0, 0.0, 1.0); 

	//Cara izquierda
	glNormal3f(-1.0, 0.0, 0.0);
	glTexCoord2f(0.0,0.0);glVertex3f(0.0, 0.0, 0.0);
	glTexCoord2f(1.0,0.0);glVertex3f(0.0, 0.0, 1.0);
	glTexCoord2f(1.0,1.0);glVertex3f(0.0, 1.0, 1.0);
	glTexCoord2f(0.0,1.0);glVertex3f(0.0, 1.0, 0.0);

	//Cara derecha
	glNormal3f(1.0, 0.0, 0.0);
	glTexCoord2f(0.0,0.0);glVertex3f(1.0, 0.0, 1.0);
	glTexCoord2f(1.0,0.0);glVertex3f(1.0, 0.0, 0.0);
	glTexCoord2f(1.0,1.0);glVertex3f(1.0, 1.0, 0.0);
	glTexCoord2f(0.0,1.0);glVertex3f(1.0, 1.0, 1.0);

	glEnd();

	glPopMatrix();
}


void Escenario::setElements() {
	int f = 0;
	int c = 0;
	for (f = 0; f < m_ancho - 1; f++) {
		for (c = 0; c < m_alto - 1; c++) {
			switch (matrizMapa[f][c]) {
				case 'A': {	// fantasma
					Fantasma::addFantasma(f, c);
					break;
				}
				case '@': {	// jugador
					pers = CPersonaje::Instance();
					pers->setPosition(f, c);
					break;
				}
				case ' ': {	// espacio vacio
					break;
				}
				case '#': {	// pared
					break;
				}
				default: {
					break;
				}
			}
		}
	}
}

/*
 * Muestra por pantalla matrizMapa
 */
void Escenario::mostrarEscenario() {
	int f = 0;
	int c = 0;
	for (f = 0; f < m_ancho; f++) {
		for (c = 0; c < m_alto; c++) {
			cout << matrizMapa[f][c];
		}
		cout << endl;
	}
}

/*
 * Carga el fichero de escenario en la variable matrizMapa
 */
bool Escenario::cargarEscenario(string pFichero) {

	if (texturaSuelo==0)
		texturaSuelo = SOIL_load_OGL_texture("texturas/suelo.jpg", SOIL_LOAD_AUTO,
												0, 0);
	if (texturaBloque==0)
		texturaBloque = SOIL_load_OGL_texture("texturas/suelo2.jpg", SOIL_LOAD_AUTO,
												0, 0);
	ifstream fichero;
	string linea;
	unsigned int f = 0;
	fichero.open(pFichero.c_str());
	if (fichero.is_open()) {
		while (getline(fichero, linea)) {
			Escenario::m_alto++;
		}
		fichero.clear();
		fichero.seekg(0, fichero.beg);
		while (getline(fichero, linea)) {
			if (!linea.empty() && linea[linea.length() - 1] == '\n') {
				linea.erase(linea.length() - 1);
			}
			string::iterator it;
			unsigned int c = 0;
			Escenario::m_ancho= max(Escenario::m_ancho,linea.length());
			for (c = 0, it = linea.begin(); it < linea.end(); it++, c++) {
				matrizMapa[c][m_alto-1-f] = *it;
			}
			f++;
		}

	fichero.close();
	
	setElements(); //una vez cargado, les asignamos las posiciones a los fantasmas y el personaje

	//creamos un display list y dibujamos todo el escenario para luego dibujar más rápido
	m_displayListHQ= glGenLists(1);
	glNewList(m_displayListHQ,GL_COMPILE);
		for (int i= 0; i<m_ancho; i++)
			for (int j= 0; j<m_alto; j++)
				if (matrizMapa[i][j]=='#')
					drawBlock(i,j,true);
		drawFloor(true); 

	glEndList();
	m_displayListLQ= glGenLists(1);
	glNewList(m_displayListLQ,GL_COMPILE);
		for (int i= 0; i<m_ancho; i++)
			for (int j= 0; j<m_alto; j++)
				if (matrizMapa[i][j]=='#')
					drawBlock(i,j,false);
		drawFloor(false); 

	glEndList();
	return true;
	}
	return false;
}

char Escenario::getC(unsigned int posX, unsigned int posZ) {
	return Escenario::getInstance()->matrizMapa[posX][posZ];
}

void Escenario::setC(unsigned int posX, unsigned int posZ, char pC) {
	Escenario::getInstance()->matrizMapa[posX][posZ] = pC;
}

/*
 *  Metodo que devuelve una instancia unica del escenario
 */
Escenario* Escenario::getInstance() {
	if (pInstance == 0) {
		pInstance = new Escenario();
	}
	return pInstance;
}

void Escenario::releaseInstance() {
	if (pInstance != 0) {
		delete pInstance;
		pInstance= 0;
	}
}
/*
 * Constructor del escenario
 */
Escenario::Escenario() {
	texturaSuelo= 0;
	texturaBloque= 0;
	
}

/*
 * Destructor
 */
Escenario::~Escenario() 
{
	if (m_displayListHQ) glDeleteLists(m_displayListHQ,1);
	if (m_displayListLQ) glDeleteLists(m_displayListLQ,1);
}


/*
 * Escenario.h
 *
 *  Created on: 27/11/2013
 *      Author: dowdyph0
 */

#include <string>
#include <fstream>
#include <iostream>

 
using namespace std;

#ifndef ESCENARIO_H_
#define ESCENARIO_H_

#define ANCHO 128
#define ALTO 128
#define ALTO_BLOQUE 1

class Escenario {

public:
	float getLadoX();
	float getLadoZ();
	float getAlto();
	char matrizMapa[ANCHO][ALTO]; // matriz logica del escenario
	static Escenario* getInstance();
	static void releaseInstance();
	bool cargarEscenario(string pFichero);
	void mostrarEscenario();
	void drawBlock(int x, int y,bool highQ= true);
	void setElements();
	void drawFloor(bool highQ= true);
	void draw(bool highQ= true);
	char getC(unsigned int x, unsigned int z);
	void setC(unsigned int x, unsigned int z, char c);
protected:
	Escenario();
	~Escenario();
	Escenario(const Escenario &);
	Escenario &operator =(const Escenario &);
private:
	static Escenario* pInstance;
	static int m_ancho;
	static int m_alto;
	static int m_displayListHQ;
	static int m_displayListLQ;
};

#endif /* ESCENARIO_H_ */

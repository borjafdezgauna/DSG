#include "stdafx.h"
#include "mouse.h"

bool ratonIzq;

void RatonLateral () {

	if (ratonIzq) {
		//MOVER ANGULO
	}
}

void CapturarClick(int event, int state, int x, int y) {
	if (event == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		ratonIzq = true;
	}
}
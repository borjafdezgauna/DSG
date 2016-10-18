#include "stdafx.h"
#include "Mouse.h"
#define ANGLE_STEP 0.2
bool mPulsado;
float esAncho;
int esAlto;
void estMouse(int x, int y) {
	esAncho = (float)x;
	esAlto = (float)y;
}
void pulsMouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON: mPulsado = true;
		

		if(state == GLUT_UP)
			mPulsado = false;
		break;
	
	}
	
}
	void moveMouse() {
	
		if (mPulsado) {
			float w = (float)g_w;
			float pant = (w/2.0);
			float cal = esAncho-pant;
			float x = cal/pant;
			g_yaw += x*ANGLE_STEP;
			
		}
	
	}


#include "stdafx.h"
#include "Mouse.h"

float xmouse;
float ymouse;
#define ANGLE_STEP 0.05
#define MOVE_STEP .025
#define PI 3.1416f
bool btnIz;
bool adentro;
bool afuera;


void Raton() {

	if (btnIz) {
		//x2 = g_x / g_w;
			
		g_yaw += ANGLE_STEP*((xmouse-g_w / 2) / (g_w / 2));
		g_pitch += MOVE_STEP*((ymouse - g_h / 2) / (g_h / 2));

	}
	if (adentro) {
		g_x -= MOVE_STEP*sin(g_yaw*PI / 180);
		g_z -= MOVE_STEP*cos(g_yaw*PI / 180);
	}
	if (afuera) {
		g_x += MOVE_STEP*sin(g_yaw*PI / 180);
		g_z += MOVE_STEP*cos(g_yaw*PI / 180);
	}
	
}

void Mouse(int button, int state, int x, int y)
{
	//Mouse callback function
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		btnIz = true;
		xmouse = (float) x;
		ymouse = (float) y;
	}
		if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
			btnIz = false;
	}
		if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
			adentro = true;
		}
		if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
			adentro = false;
		}
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
			afuera = true;
		}
		if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
			afuera = false;
		}
}

void MouseMotion(int x, int y) {
	xmouse = x;
	ymouse = y;
}

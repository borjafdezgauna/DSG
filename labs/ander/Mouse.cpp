#include "stdafx.h"
#include "Mouse.h"

float xmouse;
float ymouse;
#define ANGLE_STEP 0.05
#define MOVE_STEP .05
#define PI 3.1416f
bool btnIz;

void RatonLateral() {

	if (btnIz) {
		//x2 = g_x / g_w;
			
		g_yaw += ANGLE_STEP*((xmouse-g_w/2)/(g_w/2));
		g_pitch += MOVE_STEP*((ymouse - g_h / 2) / (g_h / 2));
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
}

void MouseMotion(int x, int y) {
	xmouse = x;
	ymouse = y;
}

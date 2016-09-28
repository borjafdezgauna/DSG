#include "stdafx.h"
#include "mouse.h"

#define MOVE_STEP 0.1
#define ANGLE_STEP 0.05
#define PI 3.1416f

bool key;
double x_act;
double y_act;
int boton;

void mouse(int button, int state, int x, int y) {
	key = !state;
	x_act = x;
	y_act = y;
	boton = button;
}

void mouseMotion(int x, int y){
	x_act = x;
	y_act = y;
}

void ejecutarRaton() {
	if (key) {
		if (boton == GLUT_LEFT_BUTTON) {
			g_x -= MOVE_STEP*sin(g_yaw*PI / 180);
			g_z -= MOVE_STEP*cos(g_yaw*PI / 180);
		}
		else if (boton == GLUT_MIDDLE_BUTTON) {
			double mitadAncho = (double)g_w / 2.0;
			g_yaw += (((double)x_act - mitadAncho) / mitadAncho)*ANGLE_STEP;
			double mitadAlto = (double)g_h / 2.0;
			g_pitch += (((double)y_act - mitadAlto) / mitadAlto)*ANGLE_STEP;
		}
		else if (boton == GLUT_RIGHT_BUTTON) {
			g_x += MOVE_STEP*sin(g_yaw*PI / 180);
			g_z += MOVE_STEP*cos(g_yaw*PI / 180);
		}
	}
}

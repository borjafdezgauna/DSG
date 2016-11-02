#include "stdafx.h"
#include "Keyboard.h"

#define MOVE_STEP 0.01
#define ANGLE_STEP 0.05
#define PI 3.1416f

BOOL tecla_1 = false;
BOOL tecla_2 = false;
BOOL tecla_3 = false;
BOOL tecla_4 = false;
BOOL solid = true;
BOOL culling = true;

void Keyboard(unsigned char key, int x, int y)
{
	//keyboard callback function
	switch (key)
	{
	case '8':	tecla_1 = true; break;
	case '2':	tecla_2 = true; break;
	case '6':	tecla_3 = true; break;
	case '4':	tecla_4 = true; break;
	case '5': if (solid) {solid = false;}
			  else { solid = true; }break;
	case '7': if (culling) { culling = false; }
			  else { culling = true; }break;
	case 27: exit(0);
	}
}

void Keyboard_pulsar() 
{
		if (tecla_1) {
			g_x -= MOVE_STEP*sin(g_yaw*PI / 180);
			g_z -= MOVE_STEP*cos(g_yaw*PI / 180);
		}
		if (tecla_2) {
			g_x += MOVE_STEP*sin(g_yaw*PI / 180);
			g_z += MOVE_STEP*cos(g_yaw*PI / 180);
		}
		if (tecla_3) {
			g_yaw -= ANGLE_STEP;
		}
		if (tecla_4) {
			g_yaw += ANGLE_STEP;
		}
		if (solid) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		if (solid == false) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if (culling) {
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glEnable(GL_DEPTH_TEST);
		}
		if (culling == false) {
			glDisable(GL_CULL_FACE);
			glCullFace(GL_BACK);
			glDisable(GL_DEPTH_TEST);
		}
}
void Keyboard_up(unsigned char key, int x, int y) {
	switch (key) {
	case '8':	tecla_1 = false;
		break;
	case '2':	tecla_2 = false;
		break;
	case '6':	tecla_3 = false;
		break;
	case '4':	tecla_4 = false;
		break;
	}
}
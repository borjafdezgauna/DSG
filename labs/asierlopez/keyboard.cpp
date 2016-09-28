#include "stdafx.h"
#include "keyboard.h"

#define MOVE_STEP 0.1
#define ANGLE_STEP 0.05
#define PI 3.1416f

bool key8;
bool key2;
bool key6;
bool key4;

void Keyboard(unsigned char key, int x, int y){
	switch (key) {
	case '8':	key8 = true;
				break;
	case '2':	key2 = true;
				break;
	case '6':	key6 = true;
				break;
	case '4':	key4 = true;
				break;
	case 27:	exit(0);
	}
}

void ejecutarTeclado() {
	//keyboard callback function
	if(key8){
		g_x -= MOVE_STEP*sin(g_yaw*PI / 180);
		g_z -= MOVE_STEP*cos(g_yaw*PI / 180);
	}else if (key2) {
		g_x += MOVE_STEP*sin(g_yaw*PI / 180);
		g_z += MOVE_STEP*cos(g_yaw*PI / 180);
	}else if (key6) {
		g_yaw -= ANGLE_STEP;
	}else if (key4) {
		g_yaw += ANGLE_STEP;
	}
}

void upKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '8':	key8 = false;
		break;
	case '2':	key2 = false;
		break;
	case '6':	key6 = false;
		break;
	case '4':	key4 = false;
		break;
	}
}
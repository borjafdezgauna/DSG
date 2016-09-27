#include "stdafx.h"
#include "keyboard.h"

#define MOVE_STEP 0.04
#define ANGLE_STEP 0.02
#define PI 3.1416f

bool key1Up = false;
bool key2Down = false;
bool key3Left = false;
bool key4Right = false;

void Keyboard(unsigned char key, int x, int y)
{
	//keyboard callback function
	switch (key)
	{
	case '8':
		key1Up = true;
		break;
	case '2':	
		key2Down = true;
		break;
	case '6': key3Left = true; break;
	case '4': key4Right = true; break;
	case 27: exit(0);
	}
}

void PressedKeyboard(unsigned char key, int x, int y)
{
	//keyboard callback function
	switch (key)
	{
	case '8':
		key1Up = false;
		break;
	case '2':
		key2Down = false;
		break;
	case '6': key3Left = false; break;
	case '4': key4Right = false; break;
	case 27: exit(0);
	}
}

void updateMovement() {
	if (key1Up) {
		g_x -= MOVE_STEP*sin(g_yaw*PI / 180);
		g_z -= MOVE_STEP*cos(g_yaw*PI / 180);
	}
	else if (key2Down) {
		g_x += MOVE_STEP*sin(g_yaw*PI / 180);
		g_z += MOVE_STEP*cos(g_yaw*PI / 180);
	}
	else if (key3Left) {
		g_yaw += ANGLE_STEP;
	}
	else if (key4Right) {
		g_yaw -= ANGLE_STEP;
	}
}


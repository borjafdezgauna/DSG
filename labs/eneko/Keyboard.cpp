#include "stdafx.h"
#include "keyboard.h"
#define MOVE_STEP .4
#define ANGLE_STEP 0.2
#define PI 3.1416f
bool pulsado;
void Keyboard(unsigned char key, int x, int y)
{
	//keyboard callback function
	switch (key)
	{
	case '8':	g_x -= MOVE_STEP*sin(g_yaw*PI / 180);
		g_z -= MOVE_STEP*cos(g_yaw*PI / 180);break;
	case '2':	g_x += MOVE_STEP*sin(g_yaw*PI / 180);
		g_z += MOVE_STEP*cos(g_yaw*PI / 180);break;
	case '6': g_yaw -= ANGLE_STEP; break;
	case '4': g_yaw += ANGLE_STEP; break;
	case 27: exit(0); break;
	}
	

}
void pressKeyboard(unsigned char key, int x, int y) {
	
	switch (key)
	{
	case '8': pulsado = false;break;
	case '2': pulsado = false;break;

	}

}
void moverTeclado(unsigned char key, int x, int y) {
	if (pulsado) {
		g_x -= MOVE_STEP*sin(g_yaw*PI / 180);
		g_z -= MOVE_STEP*cos(g_yaw*PI / 180);
	
	}
		/*/switch (key)
		{
			
		case '8':	g_x -= MOVE_STEP*sin(g_yaw*PI / 180);
			g_z -= MOVE_STEP*cos(g_yaw*PI / 180);break;
		case '2':	g_x += MOVE_STEP*sin(g_yaw*PI / 180);
			g_z += MOVE_STEP*cos(g_yaw*PI / 180);break;
		case '6': g_yaw -= ANGLE_STEP; break;
		case '4': g_yaw += ANGLE_STEP; break;
		case 27: exit(0); break;
			/*/
		
	}


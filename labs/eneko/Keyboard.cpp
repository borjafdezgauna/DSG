#include "stdafx.h"
#include "keyboard.h"
#define MOVE_STEP .8
#define ANGLE_STEP 1.5
#define PI 3.1416f
bool pulsado1;
bool pulsado2;
bool pulsado3;
bool pulsado4;
int control = 1;
int control1 = 1;
void Keyboard(unsigned char key, int x, int y)
{
	//keyboard callback function
	switch (key)
	{
	case '8': pulsado1 = true;break;
	case '2': pulsado2= true;break;
	case '4':pulsado3 = true;break;
	case '6':pulsado4 = true;break;
	case'5': control++;break;
	case'0':control1++;break;
	case 27: exit(0); break;

	}
	

}
void pressKeyboard(unsigned char key, int x, int y) {
	
	switch (key)
	{
	case '8': pulsado1 = false;break;
	case '2': pulsado2= false;break;
	case '4':pulsado3 = false;break;
	case '6':pulsado4 = false;break;
	}

}
void moverTeclado() {
	if (pulsado1) {
		g_x -= MOVE_STEP*sin(g_yaw*PI / 180);
		g_z -= MOVE_STEP*cos(g_yaw*PI / 180);
	}
	if (pulsado2){
		g_x += MOVE_STEP*sin(g_yaw*PI / 180);
		g_z += MOVE_STEP*cos(g_yaw*PI / 180);
	}
	if (pulsado4) {
		g_yaw -= ANGLE_STEP;
	}
	if (pulsado3) {
		g_yaw += ANGLE_STEP;
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
//int64 t1,t2
//QueryPerfotmance(&t1)
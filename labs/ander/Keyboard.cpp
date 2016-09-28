#include "stdafx.h"
#include "Keyboard.h"
#define MOVE_STEP .005
#define ANGLE_STEP 0.05
#define PI 3.1416f

bool pulsa8;
bool pulsa6;
bool pulsa4;
bool pulsa2;

void Keyboard(unsigned char key, int x, int y)
{
	//keyboard callback function
	switch (key)
	{
	case '8':	pulsa8 = true; break;
	case '2':	pulsa2 = true; break;
	case '6': pulsa6 = true; break;
	case '4':  pulsa4 = true; break;
		
	case 27: exit(0);
	}
}
		void TratarTeclado() 
		{
			if(pulsa8){
					g_x -= MOVE_STEP*sin(g_yaw*PI / 180);
					g_z -= MOVE_STEP*cos(g_yaw*PI / 180);
				}
			if (pulsa2) {
				g_x += MOVE_STEP*sin(g_yaw*PI / 180);
				g_z += MOVE_STEP*cos(g_yaw*PI / 180); 
			}
			if (pulsa6) {
				g_yaw -= ANGLE_STEP; 
			}
			if (pulsa4) {
				g_yaw += ANGLE_STEP;
			}

		}

void KeyboardUp(unsigned char key, int x, int y) {
	switch (key)
	{
	case '8':	pulsa8 = false; break;

	case '2':	pulsa2 = false; break;

	case '6':   pulsa6 = false; break;


	case '4':  pulsa4 = false; break;
	case 27: exit(0);
		}
		
	}
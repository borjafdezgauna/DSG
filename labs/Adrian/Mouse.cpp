#include "stdafx.h"
#include "Mouse.h"

#define ANGLE_STEP 0.2

// GLUT_LEFT_BUTTON 0x0000
// GLUT_MIDDLE_BUTTON 0x0001
// GLUT_RIGHT_BUTTON 0x0002

void MouseW(int button, int state, int x, int y){

	float f_x = (float)x;
	if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
		if (f_x>=g_w/2.0) {
			g_yaw -= ANGLE_STEP * ((f_x - g_w) / (g_w / 2.0));
		}
		else {
			g_yaw += ANGLE_STEP * ((f_x - g_w) / (g_w / 2.0));
		}
	}
}

void MouseMotionW(int x, int y) {
	float f_x = (float)x;
		if (f_x >= g_w / 2.0) {
			g_yaw -= ANGLE_STEP * ((f_x - g_w) / (g_w / 2.0));
		}
		else {
			g_yaw += ANGLE_STEP * ((f_x - g_w) / (g_w / 2.0));
		}
}
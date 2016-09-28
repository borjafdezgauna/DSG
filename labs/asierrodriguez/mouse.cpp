#include "stdafx.h"
#include "mouse.h"

#define ANGLE_STEP 0.02
#define PI 3.1416f

int actualY;
bool clickUp = false;
double semiScreen;
double semiScreenUp;
double mouseInScreen;
double mouseInScreenUp;


// de izq a dcha
void OnMouseMovement() {
	if (clickUp) {
		g_yaw += mouseInScreen * ANGLE_STEP;
		g_pitch += mouseInScreenUp * ANGLE_STEP;
	}
}

void updateMouseUp(int button, int state, int x, int y) {
		clickUp = !clickUp;
		semiScreen = (double)g_w / 2.0;
		mouseInScreen = ((double)x - semiScreen) / semiScreen;
		semiScreenUp = (double)g_h / 2.0;
		mouseInScreenUp = ((double)y - semiScreenUp) / semiScreenUp;
}

void mouseAlwaysMoving() {
	if (clickUp) {
		g_yaw += mouseInScreen * ANGLE_STEP;
		g_pitch += mouseInScreenUp * ANGLE_STEP;
	}
}

void updateMouseAlways(int x, int y) {
		semiScreen = (double)g_w / 2.0;
		mouseInScreen = ((double)x - semiScreen) / semiScreen;
		semiScreenUp = (double)g_h / 2.0;
		mouseInScreenUp = ((double)y - semiScreenUp) / semiScreenUp;
}
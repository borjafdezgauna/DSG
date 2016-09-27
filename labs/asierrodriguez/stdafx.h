// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

extern int g_w;
extern float g_z;
extern float g_yaw;
extern float g_x;

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <math.h>

//OPENGL includes
#include <GL/gl.h>
#include <GL/glu.h>

//FreeGLUT includes
#define FREEGLUT_LIB_PRAGMAS 0
#include "../../packages/nupengl.core.0.1.0.1/build/native/include/GL/glut.h"
#include "../../packages/nupengl.core.0.1.0.1/build/native/include/GL/freeglut.h"
#pragma comment(lib,"../../packages/nupengl.core.0.1.0.1/build/native/lib/Win32/freeglut.lib")
#pragma comment(lib,"opengl32.lib")
//SOIL
#include "../../Simple OpenGL Image Library/src/SOIL.h"
#pragma comment(lib,"../../Debug/SOIL.lib")
#pragma comment(lib,"../../packages/nupengl.core.0.1.0.1/build/native/lib/Win32/freeglut.lib")
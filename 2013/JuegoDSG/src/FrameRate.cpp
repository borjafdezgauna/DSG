//FrameRate.cpp
//Autor: Borja Pérez Sánchez

#include "../stdafx.h"
#include "../inc/FrameRate.h"

const int frameRate = 20; //Frames por segundo a los que correrá el juego
const double frameLength = 1.0 / (double) frameRate; //Duración deseada en segundos de cada frame

__int64 freq; //Frecuencia con la que se actualiza el contador (ciclos por segundo)
__int64 t0; //Instante en el que acabó el frame anterior (ciclos)
__int64 t1; //Instante en el que acaba el frame actual (ciclos)
double tiempoSleep; //Tiempo que deberá esperar desde que acaba la generación del frame actual hasta la duración deseada de un frame
//Variables para mostrar el frame rate real aproximado
int FPS_old = 0;
int FPS_new;
int cont = 1;
double suma = 0.0;

//Devuelve el número de frames por segundo
int getFPS() {
	return frameRate;
}

//Inicializa el frame rate (justo antes de entrar al game loop)
void initFrameRate() {
	QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
	QueryPerformanceCounter((LARGE_INTEGER*)&t0);
}

//Duerme la ejecución desde que se completa el frame hasta su duración deseada (al final de cada iteración del game loop)
void endFrame() {
	
	QueryPerformanceCounter((LARGE_INTEGER*)&t1); //Registramos el valor de t1 (fin del frame)

	//Para saber aproximadamente los frames reales a los que corre el juego en cada momento
	suma += ((double)t1-(double)t0) / (double)freq; //Vamos sumando las duraciones de los frames para hacer la media en un segundo
	if(cont==frameRate) {
		FPS_new = (int)floor(1.0/(suma/frameRate));
		if(FPS_new != FPS_old) {
			printf("FPS: %d\n",FPS_new);
			FPS_old = FPS_new;
		}
		suma = 0.0;
		cont = 1;
	} else {
		cont++;
	}
	
	//El hardware da lo que da, y siempre habrá un tiempo mínimo que le cueste crear un frame. Por eso, si exigimos
	//mucho frame rate no llegaría, y como el tiempo que tardaría en generar el frame sería mayor que la duración
	//deseada del frame, tiempoSleep sería negativo y no esperaríamos
	tiempoSleep = frameLength - ((double)t1-(double)t0) / (double)freq; //En segundos
	if(tiempoSleep >= 0) {
		Sleep((DWORD)(tiempoSleep*1000.0)); //Convertimos de segundos a milisegundos
	}

	QueryPerformanceCounter((LARGE_INTEGER*)&t0); //Registramos el instante en que acaba el frame actual para que
	//lo sepa el siguiente
}
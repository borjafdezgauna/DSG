#include "stdafx.h"
#include "timeCounter.h"

double PCFreq = 0.0;
__int64 CounterStart = 0;
double frecuencyMili = 0.0;

void StartCounter(){
	LARGE_INTEGER li;
	QueryPerformanceFrequency(&li);
	PCFreq = double(li.QuadPart) / 1000.0;
	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

void SetVecesPerSecond(double vecesPerSecond) {
	frecuencyMili = (1.0 / vecesPerSecond) * 1000;
}

double GetCounter(){
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

void Regular() {
	double timeMili = GetCounter();
	if (timeMili < frecuencyMili) {
		Sleep(frecuencyMili - timeMili);
	}
}

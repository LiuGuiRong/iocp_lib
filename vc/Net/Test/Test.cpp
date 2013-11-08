#include "stdafx.h"
#include <math.h>
#include <Windows.h>
#pragma comment (lib, "Winmm.lib") 

float InvSqrt (float x) 
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i>>1);
    x = *(float*)&i;
    x = x*(1.5f - xhalf*x*x);
    return x;
}

int _tmain(int argc, _TCHAR* argv[])
{
	float arg = 101000003.0f;
	DWORD sys_time = timeGetTime();
	int looper = 0;
	for (;looper < 10000000; looper++) {
		InvSqrt(arg);
	}
	printf("InvSqrt() used time: %d \n", timeGetTime() - sys_time);

	sys_time = timeGetTime();
	looper = 0;
	for (;looper < 10000000; looper++) {
		sqrt(arg);
	}
	printf("sqrt() used time: %d", timeGetTime() - sys_time);

	return 0;
}


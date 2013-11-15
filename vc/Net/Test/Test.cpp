#include "stdafx.h"
#include <math.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

DWORD ThreadProc (LPVOID lpdwThreadParam );

//Global variable Shared by all threads
int nGlobalCount = 0;
struct param {
	int index;
	long time;
	param() { index  = 1; time = 2;};
};
//Main function which starts out each thread
int __cdecl main( int argc, char **argv)
{ 
	param* thread_param = new param;

	int i, nThreads = 5;
	DWORD dwThreadId;
	//Determine the number of threads to start
	if (argc > 1) {
		nThreads = atoi( argv[1]);
	}

	//Set the global count to number of threads
	nGlobalCount = nThreads;
	//Start the threads
	for (i=1; i<= nThreads; i++) {
		thread_param->index = i;
		//printf("i - %d\n",i);
		if (CreateThread(NULL, //Choose default security
			0, //Default stack size
			(LPTHREAD_START_ROUTINE)&ThreadProc,
			//Routine to execute
			(LPVOID) thread_param, //Thread parameter
			0, //Immediately run the thread
			&dwThreadId //Thread Id
			) == NULL)
		{
			printf("Error Creating Thread#: %d\n",i);
			return(1);
		}
		else
		{
			printf("Global Thread Count: %d %d %d\n", nGlobalCount, nThreads, i);
			Sleep(1000);
		}
	}

	return 0;
}

//Thread Routine
DWORD ThreadProc (LPVOID lpdwThreadParam ) 
{
	//Print Thread Number
	printf ("Thread #: %d\n", ((param*)lpdwThreadParam)->index);
	//Reduce the count
	nGlobalCount--;
	//ENd of thread
	return 0;
}
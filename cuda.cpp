#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include<iostream>
#define  MAX_NUMBER 99999 
#define  NumbeOfTasks 4

using namespace std;

int k;

int dst[NumbeOfTasks] [NumbeOfTasks ] = { { 0,   5,  MAX_NUMBER, 10, 3 },

		{ MAX_NUMBER, 0,   3, MAX_NUMBER, 5 },

		{ MAX_NUMBER, MAX_NUMBER, 0,   1, MAX_NUMBER },

		{ MAX_NUMBER, MAX_NUMBER, MAX_NUMBER, 0, 2 },

		{ 9, MAX_NUMBER, MAX_NUMBER, 0, 2 }

		};

__global__ void Min_RF(int a, int b)
{
	if(a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

__global__ void MatAdd(int dst[NumbeOfTasks][NumbeOfTasks])
{
	int i = threadIdx.x;
	int j = threadIdx.y;

	dst[i][j] = Min_RF(dst[i][j], dst[i][k] + ds[k][j]);
}

int main()
{
	int numOfBlocks = 1;

	dim3 threadsPerBlock(4, 4);

	for (int k = 0; k < NumbeOfTasks k++)
		MatAdd << numOfBlocks threadsPerBlock >> >(dst);

}

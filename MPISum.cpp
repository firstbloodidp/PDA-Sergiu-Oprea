#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <mpi.h>
#include <time.h>
#define  MASTER 0
#define NRTASKS 5
#define SIZE 60

using namespace std;

int getSum(int lower, int upper,int rank);

int numbers[SIZE];

void main(int argc, char *argv[])
{
	int partPerThread = SIZE / NRTASKS;
	int size, myrank, mysum = 0, mpiSum = 0, tag = 1;
	int source; 

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int lower = myrank* partPerThread;
	int upper = lower + partPerThread;

	if (myrank == MASTER) 
	{
		srand(time(NULL));
		printf("Start the master process!\n");
		for (int index = 0; index < SIZE; ++index)
		{
			numbers[index] = rand()%100+1;
		}
		
		int offset = lower;

		for (int processIndex = 1; processIndex < NRTASKS; ++processIndex) 
		{
			lower += partPerThread;
			MPI_Send(&numbers[lower], partPerThread, MPI_INT, processIndex, tag, MPI_COMM_WORLD);
			printf("Master pass the numbers to slave nr %d\n", processIndex);
		}

		mysum = getSum(offset, upper,myrank);

		for (int processIndex = 1; processIndex < NRTASKS; ++processIndex) 
		{
			source = processIndex;
			MPI_Recv(&numbers[lower], partPerThread, MPI_INT, source,tag, MPI_COMM_WORLD, &status);
		}

		MPI_Reduce(&mysum, &mpiSum, 1, MPI_INT, MPI_SUM, MASTER, MPI_COMM_WORLD);

		printf("The final sum is %d \n", mpiSum);
	}
	else {
		source = MASTER;
		MPI_Recv(&numbers[lower],partPerThread,MPI_INT,source, tag,MPI_COMM_WORLD,&status);

		mysum = getSum(lower, upper, myrank);

		MPI_Reduce(&mysum, &mpiSum, 1, MPI_INT, MPI_SUM, MASTER, MPI_COMM_WORLD);

		MPI_Send(&numbers[lower], partPerThread, MPI_INT, MASTER, tag, MPI_COMM_WORLD);
	}

	MPI_Finalize();
}

int getSum(int lower, int upper,int rank) 
{
	int mysum = 0;

	for (int index = lower; index < upper; ++index)
	{
		numbers[index] = numbers[index];
		mysum += numbers[index];
	}
	return mysum;
}

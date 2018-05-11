#include <iostream>
#include <stdio.h> 
#include <mpi.h>
#include <time.h>
#include <stdlib.h> 
#define  MASTER 0
#define  NRTASKS 5
#define  SIZE 50

using namespace std;

void main(int argc, char *argv[])
{
	int size, myrank,randomNr, leaderProcess;
	int tag = 1;

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	srand(time(NULL) + myrank);
	randomNr = rand() % 100 + 1;

	if (myrank == MASTER)
	{
		int randomNrFromProcess, max = randomNr, NumbersVector[SIZE];
		NumbersVector[0] = randomNr;
		
		for (int i = 1; i < NRTASKS; ++i)
		{
			MPI_Recv(&randomNrFromProcess, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &status);
			NumbersVector[i] = randomNrFromProcess;
		}
		
		for (int i = 1; i < NRTASKS; ++i) {
			if (NumbersVector[i] >= max) {
				max = NumbersVector[i];
				leaderProcess = i;
			}
		}

		for (int i = 1; i < NRTASKS; ++i) {
			MPI_Send(&leaderProcess, 1, MPI_INT, i, tag, MPI_COMM_WORLD);

		}

		printf("The lead process is process %d\n", leaderProcess);
	}
	else if (myrank != MASTER){

		MPI_Send(&randomNr,1, MPI_INT, MASTER, tag, MPI_COMM_WORLD);

		MPI_Recv(&leaderProcess, 1, MPI_INT, MASTER, tag, MPI_COMM_WORLD, &status);
	}
	
	MPI_Finalize();
}
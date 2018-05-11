#include <iostream>
#include <stdio.h> 
#include <stdlib.h> 
#include <mpi.h>
#include <time.h>
#define  MASTER 0
#define  NRTASKS 4
#define  INF 99999 

using namespace std;

void royFloyd(int (&dst)[NRTASKS][NRTASKS],int rank) {

	for (int col = 0; col < NRTASKS; ++col) {
		if (dst[line][rank] + dst[rank][col] < dst[line][col]) {
			dst[line][col] = dst[line][rank] + dst[rank][col];
		}
	}
}

void main(int argc, char *argv[])
{
	int size, myrank;
	int source; 

	int tag = 1;

	int dst[NRTASKS][NRTASKS];

	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


	if (myrank == MASTER)
	{
		for (int line = 0; line < NRTASKS; ++line) {
			for (int col = 0; col < NRTASKS; ++col) {
				scanf("%d",dst[line][col]);
			}
		}
		
		rf(dst,myrank);
		for (int i = 1; i < NRTASKS; ++ i)
			for (int line= 1; line< NRTASKS; ++ line){
				source = processIndex;

				MPI_Send(&dst, NRTASKS, MPI_INT, processIndex, tag, MPI_COMM_WORLD);

				MPI_Recv(&dst, NRTASKS, MPI_INT, source, tag, MPI_COMM_WORLD, &status);
			}

	}
	else if (myrank != MASTER){
		source = MASTER;

		MPI_Recv(&dst, NRTASKS, MPI_INT, source, tag, MPI_COMM_WORLD, &status);

		royFloyd(dst, myrank);
		
		MPI_Send(&dst, NRTASKS, MPI_INT, MASTER, tag, MPI_COMM_WORLD);

	}
	

	MPI_Finalize();
}
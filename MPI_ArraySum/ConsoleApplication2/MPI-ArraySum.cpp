// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#define NUMBEROFPROCESSES 5

int array[] = { 1, 2, 3,1,1,2, 3, 4, 5, 1, 2, 3};
int sum = 0;

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	int rank;
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	printf("Rank = %d\n", rank);
	if (rank == 0) {
		int received = 0;
		while (rank != 0) {
			MPI_Recv(&received, 1, MPI_INT, rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			sum += received;
		}
		printf("received = %d\n", received);

	}
	else {
		int mySum = 0;
		int numberOfElements = sizeof(array) / sizeof(int);
		int i;
		for (i = (rank - 1) * numberOfElements / NUMBEROFPROCESSES; i < (rank) * numberOfElements / NUMBEROFPROCESSES; i++) {
			mySum += array[i];
		}
		MPI_Send(&mySum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}


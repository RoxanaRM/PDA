// MPI-Leader.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mpi.h"
#include <stdlib.h>
#include <time.h>
#define NUMBEROFPROCESSES 5

int main(int argc, char *argv[])
{
	srand(time(NULL));
	int number = rand() % 20 + 1;

	MPI_Init(&argc, &argv);

	int rank;
	int next, previous;
	int received = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank < NUMBEROFPROCESSES - 1)
	{
		next = rank + 1;
	}
	else 
	{
		next = 0;
	}

	if (rank < NUMBEROFPROCESSES)
	{
		if (rank > 0)
		{
			previous = rank - 1;
		}
		else 
		{
			previous = NUMBEROFPROCESSES;
		}
	}
	
	while (received == number) 
	{
		
		MPI_Recv((void*)received, 1, MPI_INT, previous, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		printf("Received %d", received);
		if (received > number)
		{
			MPI_Send((void*)received, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
			printf("Send %d ", received);
		}
		else 
		{
			MPI_Send((void*)number, 1, MPI_INT, next, 0, MPI_COMM_WORLD);
			printf("Send %d ", number);
		}
	}

	MPI_Finalize();
	return 0;
}


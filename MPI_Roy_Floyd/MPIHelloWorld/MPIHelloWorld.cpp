// MPIHelloWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//int array[N];
//int local_array[N];



/*
int main(int argc, char* argv[]) {
	int proc_id, no_of_procs;
	MPI_Status status;
	int total_sum, partial_sum;
	int i, no_of_elements, id, no_of_elem_for_child, step, start, end;
	
	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
	MPI_Comm_size(MPI_COMM_WORLD, &no_of_procs);

	//printf("No of elements: ");
	//scanf_s("%d", &no_of_elements);
	no_of_elements = 25;

	if (proc_id == MASTER)
	{
		step = no_of_elements / (no_of_procs);

		for (i = 0; i < no_of_elements; i++)
			array[i] = i;

		for (id = 1; id < no_of_procs; id++) {
			start = (id - 1)* step;
			end = id * step - 1;

			if (id == no_of_procs - 1)
			{
				end = no_of_elements - 1;
			}

			no_of_elem_for_child = end - start + 1;

			MPI_Send(&no_of_elem_for_child, 1, MPI_INT, id, 1, MPI_COMM_WORLD);
			MPI_Send(&array[start], no_of_elem_for_child, MPI_INT, id, 1, MPI_COMM_WORLD);
		}

		total_sum = 0;

		for (id = 1; id < no_of_procs; id++) {
			MPI_Recv(&partial_sum, 1, MPI_INT, id, 1, MPI_COMM_WORLD, &status);
			total_sum += partial_sum;
		}

		printf("Total: %d\n", total_sum);
	}
	else
	{
		MPI_Recv(&no_of_elem_for_child, 1, MPI_INT, MASTER, 1, MPI_COMM_WORLD, &status);
		MPI_Recv(&local_array, no_of_elem_for_child, MPI_INT, MASTER, 1, MPI_COMM_WORLD, &status);

		partial_sum = 0;

		for (i = 0; i < no_of_elem_for_child; i++)
			partial_sum += local_array[i];
		printf("Partial sum calculated by process %d : %d\n", proc_id, partial_sum);
		MPI_Send(&partial_sum, 1, MPI_INT, MASTER, 1, MPI_COMM_WORLD);
	}
	MPI_Finalize();
}
*/


//int main(int argc, char* argv[]) {
//	int proc_id, no_of_procs, myValue, myValue1;
//	MPI_Status status;
//	int number;
//
//	MPI_Init(&argc, &argv);
//
//	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);
//	MPI_Comm_size(MPI_COMM_WORLD, &no_of_procs);
//
//	srand((unsigned)proc_id);
//
//	MPI_Request req;
//	
//	myValue = rand() % 30 + 1;
//	MPI_Isend(&myValue, 1, MPI_INT, (proc_id + 1) % no_of_procs, 1, MPI_COMM_WORLD, &req);
//	MPI_Recv(&myValue1, 1, MPI_INT, (no_of_procs +proc_id - 1) % no_of_procs, 1, MPI_COMM_WORLD, &status);
//	if (myValue > myValue1)
//	{
//		myValue = myValue1;
//	}
//	printf("The prices %d will send the value: %d", proc_id, myValue);
//
//	printf("Process received number %d ", myValue);
//
//	MPI_Finalize();
//}





//------------------- MPI ROY FLOYD----------------------


#define N		4
#define INF		99999
#define MASTER	0
int G[N][N] = {
	0,5,99999, 10,
	99999, 0,3, 99999,
	99999, 99999, 0,1,
	99999, 99999, 99999,0
};

int main(int argc, char **argv)
{
	int  num_procs, proc_id;
	int i, j, k;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &proc_id);

	for (k = 0; k < N; k++)
	{
		for (j = 0; j < N; j++)
		{
			if (G[proc_id][j] > G[proc_id][k] + G[k][j])
			{
				G[proc_id][j] = G[proc_id][k] + G[k][j];
			}
		}
		MPI_Allgather(G[proc_id], N, MPI_INT, G, N, MPI_INT, MPI_COMM_WORLD);

	}
	if (MASTER == proc_id)
	{
		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				if (INF == G[i][j])
				{
					printf("INF ");
				}
				else
				{
					printf("%d ", G[i][j]);
				}
			}
			printf("\n");
		}
	}
	MPI_Finalize();
	return 0;
}

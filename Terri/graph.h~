#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <stack> 

#define INFINITY 999999

void printMatrix(int** matrix, int n, int m) // PRINTING ARRAY [][] *****
{
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < m; k++)
		{
			if (matrix[i][k] != INFINITY)
			{
				printf("%-4d", matrix[i][k]);
			}
			else
			{
				printf("-   ");
			}
		}
		printf("\n");
	}	
}

int** makeDinMatrix(int n, int m) // CREATING DINAMIC ARR *****
{
	//making dinamic Matrix
	int **matrix = (int**) malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++)
	{
		matrix[i] = (int*) malloc(sizeof(int)*m);
	}
	
	//checking for errors
	if (matrix == NULL)
	{
		printf("\nERROR WHEN TRIED TO ALLOCATE MEMORY FOR MATRIX\n");
		return NULL;
	}
	
	//filling matrix with zeros
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < m; k++)
		{
			matrix[i][k] = 0;
		}
	}
	return matrix;
}

void initSMatrix(int** sMatrix, FILE* fp, int typeOfGraph) // FILLING sMATRIX *****
{
	//filing the sMatrix using file data
	int out, in;
	while(!feof(fp))
	{
		//-1 beceause starting counting from 0
		fscanf(fp, "%i %i", &out, &in);
		if (typeOfGraph == 1)
		{
			sMatrix[out-1][in-1] = 1;
		}
		else
		{
			sMatrix[out-1][in-1] = 1;
			sMatrix[in-1][out-1] = 1;
		}
	}
}

void initLMatrix(int** lMatrix, int** sMatrix, int vNumber, int rNumber) // LENGTHS MATR *****
{
	for (int i = 0; i < vNumber; i++) 
	{ 
		for (int j = 0; j < vNumber; j++) 
		{ 
			if (sMatrix[i][j] == 1 ) 
			{ 
				lMatrix[i][j] = sMatrix[i][j]; 
			} 
			else 
			{ 
				lMatrix[i][j] = INFINITY; 
			} 
			if (i == j && lMatrix[i][j]!=1) 
			{ 
				lMatrix[i][j] = 0; 
			} 
		}	  
	} 
	for (int k = 0; k < vNumber; k++) 
	{ 
		for (int i = 0; i < vNumber; i++) 
		{ 
			for (int j = 0; j < vNumber; j++) 
			{ 
				if (lMatrix[k][j] + lMatrix[i][k] < lMatrix[i][j]) 
				{ 
					lMatrix[i][j] = lMatrix[k][j] + lMatrix[i][k]; 
				}
			}
		}
	}
}

void initDMatrix(int** dMatrix, int** lMatrix, int** sMatrix, int vNumber) // DOSIAZNIST MATR *****
{
	for (int i = 0; i < vNumber; i++)
	{
		for (int k = 0; k < vNumber; k++)
		{
			if (lMatrix[i][k] != INFINITY)
				dMatrix[i][k] = 1;
		}
	}
}

void DFS_R(int** sMatrix, int vNumber, int start, int* visited, int* current_label, int* topological_result) // RECURSION DFS *****
{
	visited[start] = 1;

	for (int i = 0; i < vNumber; i++)
	{
		if (sMatrix[start][i] == 1 && visited[i] == 0)
		{
			DFS_R(sMatrix, vNumber, i, visited, current_label, topological_result);
		}
	}
	topological_result[start] = *current_label;
	(*current_label)--;
}

void topological_sort(int** sMatrix, int vNumber) // TOPOLOGICAL SORT *****
{
	int topological_result[vNumber];
	int* visited = (int*) malloc(sizeof(int)*vNumber);
	for (int i = 0; i < vNumber; i++)
	{
		visited[i] = 0;
	}
	int current_label = vNumber;
	for (int i = 0; i < vNumber; i++)
	{
		if (visited[i] == 0)
		{
			DFS_R(sMatrix, vNumber, i, visited, &current_label, topological_result);
		}
	}
	for (int i = 0; i < vNumber; i++)
	{
		printf("VER: %d TOPOLOGICAL RES: %d\n", i+1, topological_result[i]);
	}
}

void transponating_graf(int** sMatrix, int vNumber) // TRANSPONATING MATRIX *****
{
	int t;
    for(int i = 0; i < vNumber; ++i)
    {
        for(int j = i; j < vNumber; ++j)
        {
            t = sMatrix[i][j];
            sMatrix[i][j] = sMatrix[j][i];
            sMatrix[j][i] = t;
        }
    }
    printf("SUM_Matrix(t):\n");
    printMatrix(sMatrix, vNumber, vNumber);
}

void DFRS(int** sMatrix, int vNumber, int start, int* visited, int* t, int* finish_time) // DFRS WITHOUT PRINTF *****
{
	visited[start] = 1;
	for (int i = 0; i < vNumber; i++)
	{
		if (sMatrix[start][i] == 1 && visited[i] == 0)
		{
			DFRS(sMatrix, vNumber, i, visited, t, finish_time);
		}
	}
	++(*t);
	finish_time[start] = *t;
}

void DFRS2(int** sMatrix, int vNumber, int start, int* visited, int* t, int* finish_time) // DFRS WITH PRINTF *****
{
	visited[start] = 1;
	for (int i = 0; i < vNumber; i++)
	{
		if (sMatrix[start][i] == 1 && visited[i] == 0)
		{
			DFRS2(sMatrix, vNumber, i, visited, t, finish_time);
		}
	}
	printf("%d ", start + 1);
	++(*t);
	finish_time[start] = *t;
}
void DFS_loop(int** sMatrix, int vNumber, int* finish_time) // DFS LOOP FOR ORIGINAL GRAF *****
{
	int t = 0;
	int visited[vNumber];
	for (int i = 0; i < vNumber; i++)
	{
		visited[i] = 0;
	}
	for (int i = 0; i < vNumber; i++)
	{
		if (visited[i] == 0)
		{
			DFRS(sMatrix, vNumber, i, visited, &t, finish_time);
		}
	}
}

void DFS_loop2(int** sMatrix, int vNumber, int* finish_time) // DFS_LOOP FOR TRANSPONATED GRAF *****
{
	int finish_time_copy[vNumber];
	for (int i = 0; i < vNumber; i++)
	{
		finish_time_copy[i] = finish_time[i];
	}
	int t = 0;
	int visited[vNumber];
	for (int i = 0; i < vNumber; i++)
	{
		visited[i] = 0;
	}
	int max[2];
	max[0] = -1;
	max[1] = -1;
	for (int k = 0; k < vNumber; k++){
		for (int i = 0; i < vNumber; i++)
		{
			if (finish_time_copy[i] > max[1] && visited[i] == 0)
			{
				max[0] = i;
				max[1] = finish_time_copy[i];
			}
		}
		if (visited[max[0]] == 0)
		{
			printf("Strong connection is found( ");
			DFRS2(sMatrix, vNumber, max[0], visited, &t, finish_time);
			printf(")\n");
		}
		max[0] = -1;
		max[1] = -1;
	}
}

void strong_components(int** sMatrix, int vNumber) // FINDING STRONG COMPONENTS *****
{
	int finish_time[vNumber];
	DFS_loop(sMatrix, vNumber, finish_time);
	for (int i = 0; i < vNumber; i++)
	{
		printf("%d ", finish_time[i]);
	}
	printf("\n");
	transponating_graf(sMatrix, vNumber);
	DFS_loop2(sMatrix, vNumber, finish_time);
	for (int i = 0; i < vNumber; i++)
	{
		printf("%d ", finish_time[i]);
	}
	printf("\n");
}

void terri_algorythm()
{
	
}

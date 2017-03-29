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
	int **matrix = malloc(sizeof(int*)*n);
	for (int i = 0; i < n; i++)
	{
		matrix[i] = malloc(sizeof(int)*m);
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
	int* visited = malloc(sizeof(int)*vNumber);
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

void terri_algor(int** sMatrix, int vNumber) // TERRI ALGORYTHM *****
{
	int start = 0;
	int finish = 0;
	printf("Enter source Ver: ");
	scanf("%d", &start);
	printf("Enter finish Ver: ");
	scanf("%d", &finish);
	start--;
	finish--;
	
	stack <int> 
}

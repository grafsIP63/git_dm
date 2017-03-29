#include "graph.h"

#define SOURCE "source.txt"
#define INFINITY 999999
#define typeOfGraph 1

int main(void)
{
	// OPENING FILE
	FILE* fp = fopen(SOURCE, "r");
	if (fp == NULL)
	{
		printf("ERROR WHED TRIED TO OPEN [%s]", SOURCE);
		return -1;
	}
	
	// EXTRACTING FIRST LINE(vNumber = "Kilkist'vershin"; rNumber="Kilkist' reber")
    int vNumber, rNumber;
    fscanf(fp, "%i %i", &vNumber, &rNumber);
    
    // MAKE SUM_MATR
    int** sMatrix = makeDinMatrix(vNumber, vNumber);
    initSMatrix(sMatrix, fp, typeOfGraph);
    printf("\nSUM_Matrix:\n");
    printMatrix(sMatrix, vNumber, vNumber);	
    
    // TERRI
    terri_algor(sMatrix, vNumber);
    
	return 0;
}

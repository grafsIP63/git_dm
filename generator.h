#pragma once
#include "libraries.h"
//#define SIZE 1000

using namespace std;

void generate(int *&array, int SIZE)
{
	srand(time(0));
	int *array = new int[SIZE];

	for (int i = 0; i<SIZE; i++)
	{
		array[i] = 0;
	}

	int curr = 0;

	for (int i = 0; i<SIZE; i++)
	{
		curr = rand() % 15000;
		while (linear(array, curr, SIZE) != -1)
		{
			curr = rand() % 15000;
		}
		array[i] = curr;
	}
}
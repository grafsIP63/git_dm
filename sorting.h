#pragma once
#include <iostream>

using namespace std;

void buble(int *&array, int size)
{
	int curr = 0;
	int c = 0;
	for (int i = 0; i < size; i++)
	{
		curr = array[i];
		for (int j = i; j < size; j++)
		{
			if (curr > array[j])
			{
				curr = array[j];
				c = array[i];
				array[i] = curr;
				array[j] = c;
			}
		}
	}
}
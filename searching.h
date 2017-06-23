#pragma once

#include "libraries.h"

int binary(int *array, int element, int size, int start, int finish)
{
	int pointer = size;
	//start = 0;
	//finish = size - 1;

	pointer = pointer / 2;//left element
	pointer += start;
	if (pointer - 1 < 0 || pointer > finish)
	{
		return -1;
	}
	if (array[pointer - 1] >= element)
	{
		if (array[pointer - 1] == element)
		{
			return pointer - 1;
		}
		else
		{
			binary(array, element, size / 2, start, pointer);
		}
	}
	else
	{
		if (array[pointer] == element)
		{
			return pointer;
		}
		else
		{
			binary(array, element, finish - pointer + 1, pointer, finish);
		}
	}

}

int linear(int *array, int element, int size)
{
	int result = 0;

	while (array[result] != element)
	{
		result++;
		if (result > size)
		{
			return -1;
		}
	}

	return result;
}

int ubinary(int array[], int K, int i, int m)
{

	if (K == array[i])
	{
		return i;
	}
	else
	{
		if (K<array[i])
		{
			i--;
			if (m == 0)
			{
				return -1;
			}
			else
			{
				i = i - m / 2;
				m = m / 2;
				ubinary(array, K, i, m);
			}
		}
		else
		{

			if (m == 0)
			{
				return -1;
			}
			else
			{
				i = i + m / 2;
				m = m / 2;
				ubinary(array, K, i, m);
			}
		}
	}
}

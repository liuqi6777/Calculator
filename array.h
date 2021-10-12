#ifndef ARRAY_
#define ARRAY_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

typedef struct Array {
	int size;
	int used;
	Number *array;
} Array;

void alloc(Array *array)
{
	array->array = (Number *)malloc(array->size * sizeof(int));
}

int insert(Array *array, Number elem, int idx)
{
	if (array->used >= array->size)
		return -1;

    if (idx >= array->used)
        return -1;

	if (idx < array->used)
		memmove(&array->array[idx+1], &array->array[idx], (array->used - idx) * sizeof(int));

	array->array[idx] = elem;
	array->used++;

	return idx;
}

int remove(Array *array, int idx)
{
	if (idx < 0 || idx >= array->used)
		return -1;

	memmove(&array->array[idx], &array->array[idx+1],
		(array->used - idx - 1) * sizeof(int));
	array->used--;
	return 0;
}

#endif // ARRAY_

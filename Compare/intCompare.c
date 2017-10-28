#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../sorter.h"
#include "../mergesort.h"
#include "intCompare.h"

extern int sort_col_num;
extern int sort_col_type;

// Assigns a value in 1 array to an index in another array
void movieAssign(void* arr1, void* arr2, int index1, int index2){
	((Movie*)arr1)[index1] = ((Movie*)arr2)[index2];
}

// compares two ints
// if return == 1, arr[i1] <= arr[i2]
// if return == 0, arr[i1] > arr[i2]
int intCompare(void* arr1, void* arr2, int index1, int index2){
	Movie* pointer1 = (Movie*)arr1;
	Movie* pointer2 = (Movie*)arr2;
	int p1Data = atoi(pointer1[index1].fields[sort_col_num]);
	int p2Data = atoi(pointer2[index2].fields[sort_col_num]);
	/*
	int* intOutlier = (int*)malloc(sizeof(int)*28);

	if (p1Data < 100 || p1Data > 1000000){
		  intOutlier[index1] = p1Data;
	}
	if (p2Data < 100 || p2Data > 1000000){
		 intOutlier[index2] = p2Data;
	}
	*/
	// return values
	if(p1Data <= p2Data){
		return 1;
	}else if(p1Data > p2Data){
		return 0;
	}else {
		printf("Something went wrong :(\n");
		exit(EXIT_FAILURE);
	}
}

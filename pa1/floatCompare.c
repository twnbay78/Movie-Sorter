#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sorter.h"
#include "mergesort.h"
#include "floatCompare.h"

extern int sort_col_num;
extern int sort_col_type;
// compares two floats
// if return == 1, arr[i1] <= arr[i2]
// if return == 0, arr[i1] > arr[i2]
int floatCompare(void* arr1, void* arr2, int index1, int index2){
	Movie* pointer1 = (Movie*)arr1;
	Movie* pointer2 = (Movie*)arr2;
	float p1Data = atoi(pointer1[index1].fields[sort_col_num]);
	float p2Data = atoi(pointer2[index2].fields[sort_col_num]);

	float* floatOutlier = (float*)malloc(sizeof(float)*28);

	if (p1Data < 5 || p1Data > 1){
		  floatOutlier[index1] = p1Data;
	}
	if (p2Data < 5 || p2Data > 1){
		 floatOutlier[index2] = p2Data;
	}
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

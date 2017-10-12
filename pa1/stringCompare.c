#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sorter.h"
#include "mergesort.h"
#include "stringCompare.h"

extern int sort_col_num;
extern int sort_col_type;
// compares two strings
// if return == 1, arr[i1] <= arr[i2]
// if return == 0, arr[i1] > arr[i2]
int stringCompare(void* arr1, void* arr2, int index1, int index2){
	Movie* pointer1 = (Movie*)arr1;
	Movie* pointer2 = (Movie*)arr2;
        char* p1Data = strdup(pointer1[index1].fields[sort_col_num]);
        char* p2Data = strdup(pointer2[index2].fields[sort_col_num]);

	// return values
	if(strcasecmp(p1Data, p2Data) < 0 || strcasecmp(p1Data, p2Data) == 0){
		return 1;
	}else if(strcmp(p1Data, p2Data) > 0){
		return 0;
	}else {
		printf("Something went wrong :(\n");
		exit(EXIT_FAILURE);
	}
}

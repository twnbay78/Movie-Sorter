#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sorter.h"
#include "mergesort.h"
#include "intCompare.h"
#include "floatCompare.h"
#include "stringCompare.h"
extern int sort_col_num;
extern int sort_col_type;


// merge function joins array Left and array Right into array Arr in sorted order
void merge(void *Arr, void *leftArr, void* rightArr, int leftArrSize, int rightArrSize,
		int Compare(void*, void*, int, int),
		void Assign(void*, void*, int, int)){

	// control variables for each array
	// i = left, j = right, k = output array
	int i = 0;
	int j = 0;
	int k = 0;



	// inserts the left and right elements into the sorted Arr
	while (i < leftArrSize && j < rightArrSize){
		// if the left is less than or equal to the righ
		if(Compare(leftArr, rightArr, i, j) == 1){
			Assign(Arr, leftArr, k, i);
			++k;
			++i;
		}else if (Compare(rightArr, leftArr, j, i) == 1){
			Assign(Arr, rightArr, k, j);
			++k;
			++j;
		}else {
			printf("ERROR, the compare functions didn't work :(\n");
			exit(EXIT_FAILURE);
		}
	}

	// when one of the arrays are empty, the other still needs to be copied over
	while (i < leftArrSize){
		Assign(Arr, leftArr, k, i);
		++k;
		++i;
	}

	while(j < rightArrSize){
		Assign(Arr, rightArr, k, j);
		++k;
		++j;
	}


}


// function that recursively splits the arrays and sorts them with merge()
void mergeSort(void* Arr, int arrSize, int structSize,
		int Compare(void*, void*, int, int),
		void Assign(void*, void*, int, int)){

	// Declaring left + right arrays, and required array indicies
	void *leftArr, *rightArr;
	int middle, i;

	// BASE CASE: if array size is 1, the array is already split
	if(arrSize < 2){
		return;
	}

	middle = arrSize/2;

	// left and right subarrays - recursively being split
	leftArr = malloc(structSize * middle);
	rightArr = malloc(structSize * (arrSize - middle));

	// checking if malloc worked (dam you malloc!)
	if(!leftArr || !rightArr){
		printf("Malloc didn't work while allocating sub array space :(\n");
		exit(EXIT_FAILURE);
	}

	Copy(leftArr, Arr, middle, 0, Assign);
	Copy(rightArr, Arr,  arrSize - middle, middle, Assign);

	// recursive calls
	// splitting the left array
	mergeSort(leftArr, middle, structSize, Compare, Assign);
	// splitting the right array
	mergeSort(rightArr, arrSize - middle, structSize, Compare, Assign);
	// merge sub arrays into a sorted array
	merge(Arr, leftArr, rightArr,  middle, arrSize - middle, Compare, Assign);

	// free sub array memory
	free(leftArr);
	free(rightArr);

}

void Copy(void* arr1, void* arr2, int length, int index, void Assign(void*, void*, int, int)){

	int i;
	for(i = 0; i < length; i++){
		Assign(arr1, arr2, i, index+i);
	}
}

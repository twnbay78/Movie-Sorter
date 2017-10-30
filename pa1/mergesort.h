#ifndef MERGESORT_H
#define MERGESORT_H


void merge(void *Arr, void *leftArr, void* rightArr, int leftArrSize, int rightArrSize, 
		int Compare(void*, void*, int, int),
		void Assign(void*, void*, int, int));


void mergeSort(void* Arr, int arrSize, int structSize, 
		int Compare(void*, void*, int, int),
		void Assign(void*, void*, int, int));
#endif


Movie Sorter

Summary
It is very useful in many cases to sort large sets of data. One good example of this is sorting a large set of movie data. Movies have several attributes involved, allowing for lots of data be analyzed, mined, sorted and distributed throughout wide arrays of applications. This program, in short, will take in movie data from a .csv file (most typically associated with Microsoft Office Excel) and sort the file based on a certain type of data. 
Usage
Compiling and linking necessary files is made simple using the "make" command in terminal: 

$make

 Running the project is accomplished by outputting the data into standard input: 

$cat file.csv | ./sorter -c col_to_sort


Implementation
The following list contains each file and what it is used for in the project: 

Preprocessor - Header Files
•sorter.h
- Declares methods required for sorter.c •mergesort.h
- Declares methods required for mergesort.c •intCompare.h
- Declares methods required for intCompare.c •stringCompare.h
- Declares methods requried for stringCompare.c •floatCompare.h
- Declares methods required for floatCompare.c 
C files
•sorter.c
- This is the "driver" of the program. This file opens the .csv file using a file pointer. The file finds the column specified by the user and the appropriate data type specified by the user using the following methods: get_sort_col_info()
get_col_type()
Each individual movie entry is represented using a struct, and the structs are added to an array, holding every movie entry in the file: Movie* mov
The data of each entry is then loaded into each struct using the function as string: fgets()
Once the sorting is complete, the array of structs will now be in sorted order according to the column specified by the user, and is then outputed to a new .csv file using the function: fprintf()
•mergesort.c
- This is where the sorting magic is done. Sorting is done using a merge-sort implementation, where the worst case runtime efficiency is n*log(n) where n = # of elements to be sorted 
 - Merge sort recursively splits the inputted array until the elements are single elements (cost = log(n)). The function then calls merge() to combine the sub arrays into a final, sorted array (cost = n). •intCompare.c
- This file contains methods used by mergeSort() in the case of column data that is represented by integers. •stringCompare.c
- This file contains methods used by mergeSort() in the case of column data that is represented by strings. •floatCompare.c
- This file contains methods used by mergeSort() in the case of column data that is represented by float values. 
Abstraction
What is most beneficial about Movie Sorter is the capacity at which data can be sorted. The method signature for the merge-sort implementation is as follows: void mergeSort(void* Arr, int arrSize, int structSize,
int Compare(void*, void*, int, int),
void Assign(void*, void*, int, int));
Since the arrays are passed into the merge-sort function are void pointers, it allows for a list of any type to be sorted. Since dereferencing void pointers in C is not allowed, the data must be down-casted to a type that can be referenced in order to perform the comparisons needed. This is done with the intCompare.c, stringCompare.c, and floatCompare.c files, which contain methods that cast the void pointers appropriately so they can be properly referenced. With this implementation, one can hypothetically create compare functions for any type of structure, thus adding a layer of "abstraction." Parameterized types are more commonly known as generics in languages such as Java, C# and others. 

 Imlementing merge-sort for various types of data is loosely expressed as: mergeSort(mov, size-1, typetSize,  typeCompare, typeAssign);

Data is Beautiful
It is also very useful to analyze data we are processing (in this case, sorting). We have implemented simple checks throughout the document to determine if any of the data is "outlier" data. For an example, if any of the data being sorted is close to a small number, or exceeds an arbitrarily large number, it is saved in array for further analysis. If a user wanted to adjust the values of the outlier data, they can simply change the values of the checks in the compare functions. 

Credits
Credit for writing the entirety of this project goes to Jarisha Olanday and myslef 




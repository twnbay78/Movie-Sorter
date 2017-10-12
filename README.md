<!-- BOOTSTRAP FILES FOR FORMATTING -->
<!-- Latest compiled and minified CSS -->
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">

<!-- jQuery library -->
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>

<!-- Latest compiled JavaScript -->
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
<div style="margin: 75px">
<h1>Movie Sorter</h1>

<h3>Summary</h3>

It is very useful in many cases to sort large sets of data. One good example of 
this is sorting a large set of movie data. Movies have several attributes involved, 
allowing for lots of data be analyzed, mined, sorted and distributed throughout wide 
arrays of applications.  This program, in short, will take in movie data from a .csv
file (most typically associated with Microsoft Office Excel) and sort the file based 
on a certain type of data.

<h3>Usage</h3>

Compiling and linking necessary files is made simple using the "make" command in 
terminal:
<br>
<br>
<pre>$make</pre>
<br>

Running the project is accomplished by outputting the data into standard input:
<br>
<br>
<pre>$cat <em>file.csv</em> | ./sorter -c <em>col_to_sort</em></pre>
<br>

<h3>Implementation</h3>

The following list contains each file and what it is used for in the project:

<br>
<h5>Preprocessor - Header Files</h5>
<ul>
	<li>sorter.h</li> 
		- Declares methods required for sorter.c
	<li>mergesort.h</li>
		- Declares methods required for mergesort.c
	<li>intCompare.h</li>
		- Declares methods required for intCompare.c
	<li>stringCompare.h</li>
		- Declares methods requried for stringCompare.c
	<li>floatCompare.h</li>
		- Declares methods required for floatCompare.c
</ul>
<h5>C files</h5>
<ul>
	<li>sorter.c</li>
		- This is the "driver" of the program. This file opens the .csv file using a
		file pointer. The file finds the column specified by the user and the appropriate 
		data type specified by the user using the following methods:
		<pre>get_sort_col_info()<br>get_col_type()</pre> 
		Each individual movie entry is represented using a struct, and the structs are added
		to an array, holding every movie entry in the file:
		<pre>Movie* mov</pre>
		The data of each entry is then loaded into each struct using the function as string: 
		<pre>fgets()</pre>
		Once the sorting is complete, the array of structs will now be in sorted order 
		according to the column specified by the user, and is then outputed to a new .csv
		file using the function:
		<pre>fprintf()</pre>
	<li>mergesort.c</li>
		- This is where the sorting magic is done. Sorting is done using a merge-sort 
		implementation, where the worst case runtime efficiency is <em>n*log(n)</em> where 
		<em>n = # of elements to be sorted</em> 
		<br>
		- Merge sort recursively splits the inputted array until the elements are single elements
		(cost = <em>log(n)</em>). The function then calls <em>merge()</em> to combine the 
		sub arrays into a final, sorted array (cost = <em>n</em>).
	<li>intCompare.c</li>
		- This file contains methods used by <em>mergeSort()</em> in the case of column 
		data that is represented by integers.
	<li>stringCompare.c</li>
		- This file contains methods used by <em>mergeSort()</em> in the case of column 
		data that is represented by strings.
	<li>floatCompare.c</li>
		- This file contains methods used by <em>mergeSort()</em> in the case of column 
		data that is represented by float values.
</ul>	

<h3>Abstraction</h3>
What is most beneficial about <em>Movie Sorter</em> is the capacity at which data can be
sorted. The method signature for the merge-sort implementation is as follows:

<pre>void mergeSort(void* Arr, int arrSize, int structSize,
int Compare(void*, void*, int, int),
void Assign(void*, void*, int, int));</pre>
Since the arrays are passed into the merge-sort function are void pointers, 
it allows for a list of any type to be sorted. Since dereferencing void pointers
in C is not allowed, the data must be down-casted to a type that can be referenced
in order to perform the comparisons needed. This is done with the <em>intCompare.c</em>, 
<em>stringCompare.c</em>, and <em>floatCompare.c</em> files, which contain methods 
that cast the void pointers appropriately so they can be properly referenced. With 
this implementation, one can hypothetically create compare functions for <em>any</em> 
type of structure, thus adding a layer of "abstraction." Parameterized types are more 
commonly known as <em>generics</em> in languages such as <em>Java</em>, <em>C#</em> 
and others.
<br>
<br>
Imlementing merge-sort for various types of data is loosely expressed as:
<pre>mergeSort(mov, size-1, <em>type</em>tSize,  <em>type</em>Compare, <em>type</em>Assign);</pre>

<h3>Data is Beautiful</h3>

It is also very useful to analyze data we are processing (in this case, sorting). We have implemented
simple checks throughout the document to determine if any of the data is "outlier" data. For an example,
if any of the data being sorted is close to a small number, or exceeds an arbitrarily large number,
it is saved in array for further analysis. If a user wanted to adjust the values of the outlier data,
they can simply change the values of the checks in the compare functions. 
<br>

<h3>Credits</h3>

<strong>Credit for writing the entirety of this project goes to Jarisha Olanday 
and myslef</strong>

</div>
<br>
<br>
<br>
<br>
<br>

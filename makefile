C	=       gcc
FLAGS   =       -Wall -g 
COMPILE =       $(CC) $(FLAGS)

all     :       sorter

sorter	:	sorter.c
		$(COMPILE) -o sorter sorter.c mergesort.c Compare/floatCompare.c Compare/intCompare.c Compare/stringCompare.c
clean   :
		rm -rf *.o sorter

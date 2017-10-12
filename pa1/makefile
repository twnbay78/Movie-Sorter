C	=       gcc
FLAGS   = -Wall -g
COMPILE =       $(CC) $(FLAGS)

all     :       sorter

sorter	:	sorter.c
		$(COMPILE) -o sorter sorter.c mergesort.c floatCompare.c intCompare.c stringCompare.c
clean   :
		rm -rf *.o sorter

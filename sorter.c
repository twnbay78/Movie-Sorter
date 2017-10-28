#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "sorter.h"
#include "mergesort.h"
#include "Compare/intCompare.h"
#include "Compare/floatCompare.h"
#include "Compare/stringCompare.h"

int sort_col_num = -1; /*Saves the number of the column to sort by for mergesort*/
int sort_col_type = -1; /*Saves the type of data of the column to sort by for mergesort*/

void get_col_type(){
        switch(sort_col_num){
                case(COLOR):
                case(DIR_NAME):
                case(ACTOR_2):
                case(GENRES):
                case(ACTOR_1):
                case(PLOT_KEYWORDS):
                case(IMDB_LINK):
                case(LANG):
                case(COUNTRY):
                case(CONTENT_RATING):
                case(TITLE):
                case(ACTOR_3):
                        sort_col_type = _STRING;
                        break;
                case(NUM_CRITICS):
                case(DURATION):
                case(DIR_FB_LIKES):
                case(ACT3_FB_LIKES):
                case(ACT1_FB_LIKES):
                case(NUM_VOTED_USERS):
                case(CAST_FB_LIKES):
                case(FACENUMBER):
                case(NUM_USERS):
                case(YEAR):
                case(ACT2_FB_LIKES):
                case(MOVIE_FB_LIKES):
                        sort_col_type = _UINT;
                        break;
                case(IMDB_SCORE):
                case(GROSS):
                case(BUDGET):
                case(ASPECT_RATIO):
                        sort_col_type = _FLOAT;
                        break;
                default:
                        fprintf(stderr, "ERROR: Invalid column argument.\n"); /*Returns this error if the argument does not exactly match any of the column headers*/
                        exit(EXIT_FAILURE);

        }
}

/*Creates substrings from a string*/

int  get_sort_col_info(char * arg2, char * header){
        char* temp = strdup(header);
        char* field;
        int col_num = 0;

        while((field=strsep(&temp, ",")) !=NULL){
                int cmp = strcmp(arg2,field);
                if(cmp == 0){
                        sort_col_num = col_num;
                }
                col_num++;
        }
        free((char *)temp);
        get_col_type();
        return col_num;
}

void create_csv(int array_size, Movie * movies, char * header, char * sort_col){
        char * filename = (char *)(malloc((strlen("sortedmovies_")+strlen(sort_col)+strlen(".csv"))*sizeof(char)));
        filename = strcpy(filename,"sortedmovies_");
        filename = strcat(filename,sort_col);
        filename = strcat(filename,".csv");
        FILE *output = fopen(filename,"w+");
        fprintf(output, header);
        int i;
        for(i = 0; i < array_size-1; ++i){
                fprintf(output, movies[i].line);
        }
        fclose(output);
        printf("File Created: %s\n",filename);
        free(filename);
}

int main(int argc, const char * argv[])
{
        /*Check for correct argument usage */
        if(argv[1]==NULL){
                fprintf(stderr, "ERROR: Expected Usage '-c' <Column name>.\n");
                exit(EXIT_FAILURE);
        }else if(strcmp(argv[1],"-c")==0){
                if(argv[2]==NULL){
                        fprintf(stderr, "ERROR: Expected Usage '-c' <Column name>.\n");
                        exit(EXIT_FAILURE);
                }
        }else{
                fprintf(stderr, "ERROR: Expected Usage '-c' <Column name>.\n");
                exit(EXIT_FAILURE);
        }


        FILE * fp = stdin;      /*Get file from stdin*/
        char line[1024];        /*Buffer line*/
        int row_num = 1;



        fgets(line, 1024, fp); /*Get header line*/
        char * header = strdup(line);
        int col_num = get_sort_col_info(argv[2],line);/*Finds the sorting column number and type according to argument*/

        size_t size = 1;
        Movie * mov = (Movie *)malloc(size * sizeof(Movie)); /*Array to hold structs of movies*/

        /*Fill in array of Movie structs; will represent each line of the csv minus the header line*/
        while (fgets(line, 1024, fp)) /*iterates through each row*/
        {
                char* tmp = strdup(line);
                char* field;
                int index = 0;

                if(row_num == (int)size){ /*Also a dynamically growing array*/
                        size++;
                        Movie * resize = (Movie *)realloc(mov,size * sizeof(Movie));
                        mov = resize;
                }

                mov[row_num-1].line = strdup(line); /*Save whole line in struct for easy print out*/
                mov[row_num-1].line_num = row_num;

                mov[row_num-1].fields = (char **)malloc(col_num * sizeof(char *));

                /*Goes through each line and inserts each field into the field array of each struct*/
                while((field=strsep(&tmp, ",")) !=NULL){ /*Iterates through each column*/
                        mov[row_num-1].fields[index] = (char *)malloc(strlen(field)*sizeof(char));
                        if(index == 10){ /*Checks to see if the next column is movie_title, where commas can possibly be in the field*/
                                mov[row_num-1].fields[index] = field;
                                if(strstr(line,"\"")!=NULL){ /*First checks if the movie_title is quoted as in there is a comma in the field*/
                                        field=strsep(&tmp, "\"");
                                        field=strsep(&tmp, "\"");
                                        index++;
                                        mov[row_num-1].fields[index] = field;
                                        field=strsep(&tmp, ",");
                                }

                        }else{
                                mov[row_num-1].fields[index] = field;

                        }
                        index++;
                }
                free((char *)tmp);
                row_num++;
        }


	int structSize = sizeof(Movie);
	// failing mergesort function in action
	if (sort_col_type == 0){
		mergeSort(mov, size-1, structSize,  stringCompare, movieAssign);
	}
	else if (sort_col_type == 1){
		mergeSort(mov, size-1, structSize,  intCompare, movieAssign);
	}else if (sort_col_type == 2){
		mergeSort(mov, size-1, structSize,  floatCompare, movieAssign);
	}else {
		printf("mergeSort() failed to execute :(\n");
		exit(EXIT_FAILURE);
	}

        create_csv(size,mov, header, argv[2]);
        free((char *)header);
        return 0;
}

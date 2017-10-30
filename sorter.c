#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include "sorter.h"
#include "mergesort.h"
#include "Compare/intCompare.h"
#include "Compare/floatCompare.h"
#include "Compare/stringCompare.h"


int sort_col_num = -1; /*Saves the number of the column to sort by for mergesort*/
int sort_col_type = -1; /*Saves the type of data of the column to sort by for mergesort*/
size_t size; /* Size of the entries in each array of struct */

// Function for type checking what column data we need to sort
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



int  get_sort_col_info(const char * arg2, char * header){
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

// function for creating the sorted csv file
void create_csv(int array_size, Movie * movies, char * header, const char * sort_col){
        char * filename = (char *)(malloc((strlen("sortedmovies_")+strlen(sort_col)+strlen(".csv"))*sizeof(char)));
        filename = strcpy(filename,"sortedmovies_");
        filename = strcat(filename,sort_col);
        filename = strcat(filename,".csv");
        FILE *output = fopen(filename,"w+");
        fprintf(output,"%s", header);
        int i;
        for(i = 0; i < array_size-1; ++i){
                fprintf(output,"%s", movies[i].line);
        }
        fclose(output);
        printf("File Created: %s\n",filename);
        free(filename);
}

// Function that reads the outputed data from a .csv file from STDIN, loads it into an array of structs, sorts the array of structs, and creates a sorted .csv file
Movie* sort(const char** col_args, int count ){
        FILE * fp = stdin;      /*Get file from stdin*/
	char* col_headers  = (char*)malloc(sizeof(char) * 1024);
        char* line = (char*)malloc(sizeof(char)*1024);        /*Buffer line*/
        int row_num = 1;
	int i = 0;

	/*Get header line*/
        fgets(col_headers, 1024, fp); 
        char * header = strdup(line);
	/*Finds the sorting column number and type according to argument*/
        int col_num = get_sort_col_info(col_args[i],col_headers);
	++i;

	// how many entries there are in the array of structs
        size = 1;
        Movie * mov = (Movie *)malloc(size * sizeof(Movie)); /*Array to hold structs of movies*/

        /*Fill in array of Movie structs; will represent each line of the csv minus the header line*/
	/*iterates through each row*/
        while (fgets(line, 1024, fp)) 
        {
                char* tmp = strdup(line);
                char* field;
                int index = 0;

		/*Also a dynamically growing array*/
                if(row_num == (int)size){ 
                        size++;
                        Movie * resize = (Movie *)realloc(mov,size * sizeof(Movie));
                        mov = resize;
                }

	       	/*Save whole line in struct for easy print out*/
                mov[row_num-1].line = strdup(line);
                mov[row_num-1].line_num = row_num;
                mov[row_num-1].fields = (char **)malloc(col_num * sizeof(char *));

                /*Goes through each line and inserts each field into the field array of each struct*/
		/*Iterates through each column*/
		while((field=strsep(&tmp, ",")) !=NULL){
                        mov[row_num-1].fields[index] = (char *)malloc(strlen(field)*sizeof(char));
			/*Checks to see if the next column is movie_title, where commas can possibly be in the field*/
                        if(index == 10){ 
                                mov[row_num-1].fields[index] = field;
				/*First checks if the movie_title is quoted as in there is a comma in the field*/
                                if(strstr(line,"\"")!=NULL){ 
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
	// performs mergesort on the array of structs
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

	create_csv(size,mov, header, col_args[i-1]);
	// If multiply column arguments are inputted, mergesort is performed again on the specified parameters
	if(count > 0){
		do{
			col_num = get_sort_col_info(col_args[i],col_headers);
			//printf("i: %d, count: %d\n", i, count);
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

			create_csv(size,mov, header, col_args[i]);
			++i;
		}while(i < count);
	}
        free((char *)header);
	return mov;
}

int main(int argc, const char * argv[])
{

	/* Variables needed to process program arguments
	token = holding each individual column name 
	col_args[] = holds all column names specified in the program arguments
	col_headers[] = line of the column headers
	count = how many different column headers are specified
	program_args[] = array of all program arguments
	col_check = value used to check whether a column name was specified*/
	char* argv2 = argv[2];
	char* token;
	const char* col_args[28];
	int count = 0;
	int i = 0;
	int j = 0;
	const char* program_args[10];
	const char* input_dirname = (char*)malloc(sizeof(char) * 256);
	const char* output_dirname = (char*)malloc(sizeof(char) * 256);
	int col_check = 0;

        /*Check for correct argument usage */
	// Saves arguments and column data
	// loads program arguments into an array
	
	if(argv[0] == NULL){
		fprintf(stderr, "ERROR: Expected Usage: ./sorter -c <column1,column2..> | -d <input_directory> -o <output_directory>|\n");
		exit(EXIT_FAILURE);
	} 
	if(argv[1] == NULL){
		fprintf(stderr, "ERROR: Expected Usage: ./sorter -c <column1,column2..> | -d <input_directory> -o <output_directory>|\n");
		exit(EXIT_FAILURE);
	}
	if(argv[2] == NULL){
		fprintf(stderr, "ERROR: Expected Usage: ./sorter -c <column1,column2..> | -d <input_directory> -o <output_directory>|\n");
		exit(EXIT_FAILURE);
	}
	
	// while there are still arguments left...
	while ((i+1) < argc){
		program_args[i] = argv[i];
		// case for the input directory "-d" argument
		if(strcmp(program_args[i], "-d") == 0){
			// if there is no parameter
			if((i+1) >= argc){
				fprintf(stderr, "ERROR: Expected Usage: ./sorter -c <column1,column2..> | -d <input_directory> -o <output_directory>|\n");
				exit(EXIT_FAILURE);
			}
			input_dirname = argv[i+1];
			printf("inputdir: %s\n", input_dirname);
			i += 1;
			continue;
		// case for the output directory "-o" argument
		}else if(strcmp(program_args[i], "-o") == 0){
			// if there is no parameter
			if((i+1) >= argc){
				fprintf(stderr, "ERROR: Expected Usage: ./sorter -c <column1,column2..> | -d <input_directory> -o <output_directory>|\n");
				exit(EXIT_FAILURE);
			}
			output_dirname = argv[i+1];
			printf("outputdir: %s\n", output_dirname);
			i += 1;
			continue;
		}
		// case for the column name argument
		else if(strcmp(program_args[i], "-c") == 0){
			// if there is no parameter
			if((i+1) >= argc){
				fprintf(stderr, "ERROR: Expected Usage: ./sorter -c <column1,column2..> | -d <input_directory> -o <output_directory>|\n");
				exit(EXIT_FAILURE);
			}
			// if muliple parameters are specified for the column name
			if(strstr(argv[i+1], ",") != NULL){
				// separates each column name and adds them to col_args list
				while((token = strsep(&argv2, ",")) != NULL){
					col_args[j] = token;
					//printf("col_arg[%d]: %s\n", i, col_args[j]);
					++j;
				}
			// resetting variables
			count = i;
			j = 0;
			i += 1;
			col_check = 1;
			continue;
		}
		}
	++i;
	}

	// if no column name is specified, gracefully fails
	if(col_check == 0){
		fprintf(stderr, "ERROR: you must specify a column name to sort\n");
		exit(EXIT_FAILURE);
	}

	// dir pointer
	DIR *dir;
	// struct that holds folder metadata
	struct dirent *ent;
	dir = opendir(input_dirname);
	if(dir != NULL){
		// recurse through directory
		while((ent = readdir(dir)) != NULL){
			printf("ent_name: %s\n", ent->d_name);
		}
	}else {
		fprintf(stderr, "ERROR: could not read the input directory\n");
		exit(EXIT_FAILURE);
	}

	// calling function to read csv data and sort 
	sort(col_args, count);

        return 0;
}

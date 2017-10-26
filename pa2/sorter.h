#ifndef SORTER_H
#define SORTER_H

enum data_types{
        _STRING = 0,
        _UINT = 1,
        _FLOAT = 2,
};
enum fields
{
	 COLOR = 0,
	 DIR_NAME = 1,
	 NUM_CRITICS = 2,
	 DURATION = 3,
	 DIR_FB_LIKES = 4,
	 ACT3_FB_LIKES = 5,
	 ACTOR_2 = 6,
	 ACT1_FB_LIKES = 7,
	 GROSS = 8,
	 GENRES = 9,
	 ACTOR_1 = 10,
	 TITLE = 11,
	 NUM_VOTED_USERS = 12,
	 CAST_FB_LIKES = 13,
	 ACTOR_3 = 14,
	 FACENUMBER = 15,
	 PLOT_KEYWORDS = 16,
	 IMDB_LINK = 17,
	 NUM_USERS = 18,
	 LANG = 19,
	 COUNTRY = 20,
	 CONTENT_RATING = 21,
	 BUDGET = 22,
	 YEAR = 23,
	 ACT2_FB_LIKES = 24,
	 IMDB_SCORE = 25,
	 ASPECT_RATIO = 26,
	 MOVIE_FB_LIKES = 27,
};

typedef struct movie_data
{
        char ** fields; /*Holds the values of each column in the row*/
        int line_num; /*Holds the row number*/
        char * line; /*Holds the entire row as a string*/

} Movie;

#endif

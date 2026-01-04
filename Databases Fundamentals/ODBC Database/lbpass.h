/*
 Created by roberto on 3/5/21.
*/

#ifndef NCOURSES_BPASS_H
#define NCOURSES_BPASS_H

#include "windows.h"
#include <string.h>
#include <stdio.h>
/*#include <unistd.h>*/

#define MAX_FIELD 512
#define MAX_NAME 21
#define MAX_SPACE 2
#define MAX_SEAT_NO 5
#define MAX_SQLCHAR 8192

void results_bpass(char * bookID, int * n_choices,
                   char *** choices, int max_length, int max_rows);

#endif /*NCOURSES_BPASS_H */

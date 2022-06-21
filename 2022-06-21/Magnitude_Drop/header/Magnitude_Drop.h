#ifndef _MAGNITUDE_DROP_H
#define _MAGNITUDE_DROP_H

#define FNAME1_1 "./input/1_1.txt"
#define FNAME1_2 "./input/1_2.txt"

#define FNAME2_1 "./input/2_1.txt"
#define FNAME2_2 "./input/2_2.txt"

#define FNAME3_1 "./input/3_1.txt"
#define FNAME3_2 "./input/3_2.txt"

#define FNAME4_1 "./input/4_1.txt"
#define FNAME4_2 "./input/4_2.txt"

#define FNAME5_1 "./input/5_1.txt"
#define FNAME5_2 "./input/5_2.txt"

#define FNAME6_1 "./input/6_1.txt"
#define FNAME6_2 "./input/6_2.txt"

#define LOWER 179200
#define UPPER 204800

#define FS 25600
#define F1 10
#define F2 8000
#define P0 1E-6

typedef struct
{
    char topLayer_DFile[50];
    char bottomLayer_DFile[50];
}Magnitude_FileSet;

#endif
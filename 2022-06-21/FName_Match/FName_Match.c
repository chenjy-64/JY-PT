#include <stdio.h>
#include <stdlib.h>

#include "Data_Processing.h"
#include "FName_Match.h"

void fileCopy(char *path_from, char *path_to);

int main(void)
{
    char pre_prefix[20] = "./prefile/", new_prefix[20] = "./input/", suffix[10] = ".txt";
    char xyz[testDir] = {'x', 'y', 'z'};
    char fileName[testNum * testDir * 2][fNameSize], preName[testNum * 2][fNameSize];

    for (int i = 0; i < testNum; i++)
    {
        for (int j = 0; j < testDir; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                sprintf(fileName[i*testDir*2 + j*2 + k], "%s%d_%c_%d%s", new_prefix, i+1, xyz[j], k+1, suffix);
                // printf("%d\t%s\n", i*testDir*2 + j*2 + k, fileName[i*testDir*2 + j*2 + k]);
                sprintf(preName[i*2 + k], "%s%d_%d%s", pre_prefix, i+1, k+1, suffix);
                // printf("%d\t%s\t<=\t%s\n", i*testDir*2 + j*2 + k, fileName[i*testDir*2 + j*2 + k], preName[i*2 + k]);
                // fileCopy(preName[i*2 + k], fileName[i*testDir*2 + j*2 + k]);
            }
            
        }
        
    }

    double tMagnitude[testNum * testDir][2];

    for (int i = 0; i < testNum; i++)
    {
        for (int j = 0; j < testDir; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                tMagnitude[i * testDir + j][k] = Total_Magnitude_Calculate_File(fileName[i*testDir*2 + j*2 + k], UPPER, LOWER, F1, F2, P0, FS);
            }
        
        }
        
    }

    FILE *sfp = fopen(sFName, "w");

    for (int i = 0; i < testNum; i++)
    {
        for (int j = 0; j < testDir; j++)
        {
            printf("%d\t%c\t%f\t%f\t%f\n", i+1, xyz[j], tMagnitude[i * testDir + j][0], tMagnitude[i * testDir + j][1], tMagnitude[i * testDir + j][1] - tMagnitude[i * testDir + j][0]);
            fprintf(sfp, "%d\t%c\t%f\t%f\t%f\n", i+1, xyz[j], tMagnitude[i * testDir + j][0], tMagnitude[i * testDir + j][1], tMagnitude[i * testDir + j][1] - tMagnitude[i * testDir + j][0]);
        }
        
    }

    fclose(sfp);

    getchar();
    
    return 0;
}

void fileCopy(char *path_from, char *path_to)
{
	FILE *fp_read = NULL;
    FILE *fp_write = NULL;
    char ch = !EOF;
    fp_read = fopen(path_from, "r");
    if (fp_read == NULL)
    {
        printf("File %s is not Exist!\n", path_from);
    }
    fp_write = fopen(path_to, "w");
    
    while ((ch = fgetc(fp_read)) != EOF)
    {
        fputc(ch,fp_write);       
    }
    fclose(fp_read);
    fclose(fp_write);
}
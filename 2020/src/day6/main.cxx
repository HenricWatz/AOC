// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* --- Day 5: Binary Boarding --- */

#define MAXCHAR (int)100
#define MaxId (int)832

bool seatInList[MaxId] = { false };

/* Function declarations */
int parse_input(char* filename);
int parseSeatId(char* row);
int findEmptySeat(void);

/* Parse file */
int parse_input(char* filename)
{
    FILE* fp;
    char str[MAXCHAR];

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    /* Parse row by row */
    bool questionYes[26] = { false };
    int numOfYes;
    int total = 0;
    char* row_p;
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        // Treat array as pointer
        row_p = str;

        // first char is newline -> new group
        if ((*row_p) == '\n')
        {
            // Count Yes and clear array
            numOfYes = 0;
            for (char question = 'a'; question <= 'z'; question++)
            {
                if (questionYes[(question - 'a')])
                {
                    numOfYes += 1;
                    questionYes[(question - 'a')] = false;
                }
            }

            // Add groups answers to total
            total += numOfYes;
        }
        else
        {
            while ((*row_p) != '\n')
            {
                for (char question = 'a'; question <= 'z'; question++)
                {
                    if ((*row_p) == question)
                    {
                        questionYes[(question - 'a')] = true;
                    }
                }

                // Next char
                row_p += 1;
            }
        }
    
        printf("%s", str);
    }
     
    printf("sum of those counts: %d", total);
    fclose(fp);

    return 0;
}

/* Parse file part 2*/
int parse_input2(char* filename)
{
    FILE* fp;
    char str[MAXCHAR];

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    /* Parse row by row */
    int questionYes[26] = { 0 };
    int numInGroup = 0;
    int numOfYes;
    int total = 0;
    char* row_p;
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        // Treat array as pointer
        row_p = str;

        // first char is newline -> new group
        if ((*row_p) == '\n')
        {
            // Count Yes and clear array
            numOfYes = 0;
            for (char question = 'a'; question <= 'z'; question++)
            {
                if (questionYes[(question - 'a')] == numInGroup)
                {
                    numOfYes += 1;
                }

                questionYes[(question - 'a')] = 0;
            }

            // Reset group counter
            numInGroup = 0;

            // Add groups answers to total
            total += numOfYes;
        }
        else
        {
            while ((*row_p) != '\n')
            {
                for (char question = 'a'; question <= 'z'; question++)
                {
                    if ((*row_p) == question)
                    {
                        questionYes[(question - 'a')] += 1;
                    }
                }

                // Next char
                row_p += 1;
            }

            // Every person in a group ends in newline
            numInGroup += 1;
        }

        printf("%s", str);
    }

    printf("sum of those counts: %d", total);
    fclose(fp);

    return 0;
}



/* Main */
int main (int argc, char *argv[])
{

    // example
    parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day6\example_1.txt)");

    // input
    parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day6\input_1.txt)");

    // example
    parse_input2(R"(C:\Users\Watz\Desktop\AOC\2020\src\day6\example_1.txt)");

    // input
    parse_input2(R"(C:\Users\Watz\Desktop\AOC\2020\src\day6\input_1.txt)");
}


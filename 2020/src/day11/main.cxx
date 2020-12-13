// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAXCHAR         (int)10
#define AREA_MAX_WIDTH  (int)100
#define AREA_MAX_LENGTH (int)100

/* Function declarations */
int parse_input(char* filename);

/* Parse file */
int parse_input(char* filename)
{
    FILE* fp;
    char    str[MAXCHAR];
    char* row_p;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    /* Parse row by row */
    int Idx = 0;

    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        // Treat array as pointer
        row_p = str;

    }
    return 0;
}

/* Main */
int main(int argc, char* argv[])
{
    // example
    //parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day10\example_1.txt)");
    //parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day10\example_2.txt)");

    // input 1
    //parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day10\input_1.txt)");

    // zenbook path
    parse_input(R"(C:\Users\watz\Documents\GitHub\AOC\2020\src\day10\example_1.txt)");
    parse_input(R"(C:\Users\watz\Documents\GitHub\AOC\2020\src\day10\input_1.txt)");
}


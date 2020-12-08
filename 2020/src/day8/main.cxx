// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* --- Day 5: Binary Boarding --- */

#define MAXCHAR         (int)20
#define MAXINSTRUCTIONS (int)700

enum instructionID
{
    NA = 0,
    acc = 1,
    jmp,
    nop,
};

typedef struct
{
    instructionID id;
    int opValue;
    bool exec;
}INSTRUCTION;

INSTRUCTION instructionList[MAXINSTRUCTIONS] = { NA, 0, false };
int numberOfIntructions;

/* Function declarations */
bool compareCharArray(char* lhs, char* rhs, int length);
int parse_input(char* filename);
int executeOperations(void);

// compare strings
bool compareCharArray(char* lhs, char* rhs, int length)
{
    bool rtn_bool = true;

    for (int i = 0; i < length; i++)
    {
        if ((*rhs) != (*lhs))
        {
            rtn_bool = false;
        }

        // Iterate pointers
        rhs++;
        lhs++;
    }

    return rtn_bool;
}

/* Parse file */
int parse_input(char* filename)
{
    FILE*   fp;
    char    str[MAXCHAR];
    char*   row_p;
    
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    /* Parse row by row */
    int instructionIdx = 0;
    int sign;
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        // Treat array as pointer
        row_p = str;

        // Determine operator
        if (compareCharArray(row_p, "acc", 3))
        {
            instructionList[instructionIdx].id = acc;           
        }
        else if (compareCharArray(row_p, "jmp", 3))
        {
            instructionList[instructionIdx].id = jmp;
        }
        else if (compareCharArray(row_p, "nop", 3))
        {
            instructionList[instructionIdx].id = nop;
        }
        row_p += 4;

        // Determine OpValue
        sign = (*row_p == '-') ? -1 : 1;
        row_p += 1;
        while (*row_p != '\n')
        {
            instructionList[instructionIdx].opValue = instructionList[instructionIdx].opValue * 10 + (*row_p - '0');
            row_p += 1;
        }
        instructionList[instructionIdx].opValue *= sign;

        // increase idx
        instructionIdx += 1;
    }
    numberOfIntructions = instructionIdx;
    fclose(fp);

    return 0;
}

int executeOperations(void)
{
    int accValue = 0;
    int idx = 0;

    while (!instructionList[idx].exec)
    {
        instructionList[idx].exec = true;
        if (instructionList[idx].id == jmp)
        {
            idx += instructionList[idx].opValue;
        }
        else if (instructionList[idx].id == acc)
        {
            accValue += instructionList[idx].opValue;
            idx++;
        }
        else if (instructionList[idx].id == nop)
        {
            idx++;
        }
        else if (idx == numberOfIntructions)
        {
            // terminated succesfully
            printf("Accumulated value (at termination): %d", accValue);
            return 0;
        }
        else if (idx > numberOfIntructions)
        {
            // out of bounds
            return -1;
        }
    }

    // reset exec flags
    for (int i = 0; i < numberOfIntructions; i++)
    {
        instructionList[i].exec = false;
    }

    //printf("Accumulated value (at crash): %d", accValue);
    return -1;
}

void repair(void)
{
    for (int idx = 0; idx < numberOfIntructions; idx++)
    {
        // Change jmp -> nop or nop -> jmp
        if (instructionList[idx].id == jmp)
        {
            instructionList[idx].id = nop;
        }
        else if (instructionList[idx].id == nop)
        {
            instructionList[idx].id = jmp;
        }

        if (executeOperations() == 0)
        {
            break;
        }

        // Change back
        if (instructionList[idx].id == jmp)
        {
            instructionList[idx].id = nop;
        }
        else if (instructionList[idx].id == nop)
        {
            instructionList[idx].id = jmp;
        }

    }
}


/* Main */
int main(int argc, char* argv[])
{


    // example
    //parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day8\example_1.txt)");
    //executeOperations();
    //repair();

    parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day8\input_1.txt)");
    executeOperations();
    repair();
}


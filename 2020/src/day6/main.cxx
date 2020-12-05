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

/* Calc seat id from char row */
int parseSeatId(char* row)
{
    int seat_row = 0;
    float row_segment = 128;
    float col_segment = 8;
    int seat_col = 0;
    int seat_ID;

    while (*row != '\n')
    {
        /* Row */
        if (*row == 'B')
        {
            row_segment = row_segment / 2;
            seat_row += row_segment;
        }
             
        if (*row == 'F')
            row_segment = row_segment / 2;

        /* Colummn */
        if (*row == 'R')
        {
            col_segment = col_segment / 2;
            seat_col += col_segment;
        }

        if (*row == 'L')
        {
            col_segment = col_segment / 2;
        }
            
        /* Next str char */
        row += 1;
    }

    seat_ID = (seat_row * 8 + seat_col);
    printf("Row: %d, Col: %d, ID: %d\n", seat_row, seat_col, seat_ID);

    return seat_ID;
}

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
    int seat_id = 0;
    int max_seat_id = 0;
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        seat_id = parseSeatId(str);
        
        seatInList[seat_id] = true;
        if (seat_id > max_seat_id)
        {
            max_seat_id = seat_id;
        }
        printf("%s", str);
    }
     
    printf("Max ID: %d", max_seat_id);
    fclose(fp);

    return 0;
}

int findEmptySeat(void)
{
    int idx = 0;

    /* Find first ocupide seat */
    while (seatInList[idx] == false)
    {
        idx += 1;
    }

    /* Find next empty seat */
    while (seatInList[idx] == true)
    {
        idx += 1;
     }

    return idx;
}

/* Main */
int main (int argc, char *argv[])
{

    // example
    parse_input(R"(C:\Users\watz\Documents\GitHub\AOC\2020\src\day5\example_1.txt)");
    
    // input
    parse_input(R"(C:\Users\watz\Documents\GitHub\AOC\2020\src\day5\input_1.txt)");
    printf("My seat: %d", findEmptySeat());

}


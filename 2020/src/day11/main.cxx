// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAXCHAR         (int)100
#define AREA_MAX_WIDTH  (int)100
#define AREA_MAX_LENGTH (int)100

enum CHAIR_STATE
{
    FLOOR = 0,
    EMPTY = 1,
    BECOMING_EMPTY = 2,
    SEATED = 3,
    BECOMING_SEATED = 4
};

/* Function declarations */
int parse_input(char* filename);
void print_array(CHAIR_STATE array[AREA_MAX_WIDTH][AREA_MAX_LENGTH], int dim_w, int dim_h);

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
    int Idx_w = 0, Idx_h = 0, dim_w = 0, dim_h = 0;
    CHAIR_STATE array[AREA_MAX_WIDTH][AREA_MAX_LENGTH] = { FLOOR };
    
    // Fill array with seats
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        // Treat array as pointer
        row_p = str;

        while ((*row_p != '\n') && (*row_p != '\0'))
        { 
            if (*row_p == '.')
            {
                array[Idx_w][Idx_h] = FLOOR;
            }

            if (*row_p == 'L')
            {
                array[Idx_w][Idx_h] = EMPTY;
            }

            Idx_w++;
            if (Idx_w > dim_w)
            {
                dim_w = Idx_w;
            }

            row_p++;
        }

        Idx_w = 0;
        Idx_h++;
        dim_h = Idx_h; 
    }


    int adjOccupid;
    bool toggled = true;

    while (toggled)
    {
        toggled = false;

        // print
        print_array(array, dim_w, dim_h);
        printf("\n");

        // tick
        for (int h = 0; h < dim_h; h++)
        {
            for (int w = 0; w < dim_w; w++)
            {
                if (array[w][h] != FLOOR)
                {
                    // Check adj.
                    adjOccupid = 0;
                    for (int i = -1; i <= 1; i++)
                    {
                        for (int j = -1; j <= 1; j++)
                        {
                            if (((array[w + i][h + j] == SEATED) ||
                                (array[w + i][h + j] == BECOMING_EMPTY))
                                &&
                                ((i != 0) && (j != 0))
                                &&
                                ((w + i) >= 0 )
                                &&
                                ((h + j) >= 0))
                            {
                                adjOccupid += 1;
                            }
                        }
                    }

                    // toggle seat
                    if ((adjOccupid >= 4) && (array[w][h] == SEATED))
                    {
                        array[w][h] = BECOMING_EMPTY;
                        toggled = true;
                    }
                    else if ((adjOccupid == 0) && (array[w][h] == EMPTY))
                    {
                        array[w][h] = BECOMING_SEATED;
                        toggled = true;
                    }
                    else
                    {
                        /* Do nothing */
                    }
                }
            }
        }

        for (int h = 0; h < dim_h; h++)
        {
            for (int w = 0; w < dim_w; w++)
            {
                if (array[w][h] == BECOMING_EMPTY)
                {
                    array[w][h] = EMPTY;
                }

                if (array[w][h] == BECOMING_SEATED)
                {
                    array[w][h] = SEATED;
                }
            }
        }
    }

    // print
    print_array(array, dim_w, dim_h);
    printf("\n");
    
    return 0;
}


void print_array(CHAIR_STATE array[AREA_MAX_WIDTH][AREA_MAX_LENGTH], int dim_w, int dim_h)
{
    for (int h = 0; h < dim_h; h++)
    {
        for (int w = 0; w < dim_w; w++)
        {
            if (array[w][h] == EMPTY)
            {
                printf("L");
            }
            else if (array[w][h] == SEATED)
            {
                printf("#");
            }
            else
            {
                printf(".");
            }
        }
        printf("\n");
    }
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
    parse_input(R"(C:\Users\watz\Documents\GitHub\AOC\2020\src\day11\example_1.txt)");
    //parse_input(R"(C:\Users\watz\Documents\GitHub\AOC\2020\src\day11\input_1.txt)");
}


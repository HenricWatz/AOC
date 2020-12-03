// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* --- Day 3: Toboggan Trajectory --- */

#define MAXCHAR (int)100
#define MAX_WIDTH 40
#define MAX_HEIGHT 400

/* Put map global becouse I cant figure out how to pass them as reference in cpp... */
char global_map[MAX_WIDTH][MAX_HEIGHT];

int parse_input(char* filename);
int addRowToMap(char* row_p, int heightIdx);
int treverseMap(int mapHeight, int mapWidth, int slopeHight, int slopeWidth);

/* Treverse map */
int treverseMap(int mapHeight, int mapWidth, int slopeHight, int slopeWidth)
{
    unsigned int height_pos = 0;
    unsigned int width_pos = 0;
    int treeCount = 0;

    while (height_pos <= mapHeight)
    {
        /* loop around if outside of map */
        if (width_pos >= mapWidth)
        {
            width_pos -= mapWidth;
        }

        /* Check for tree */
        if (global_map[width_pos][height_pos] == '#')
        {
            treeCount += 1;
        }

        /* Update position */
        width_pos += slopeWidth;
        height_pos += slopeHight;
    }

    printf("Slope: [H:%d, W:%d] - Tree count: %d\n", slopeHight, slopeWidth, treeCount);

    return treeCount;
}

/* Add row to map, return width */ 
int addRowToMap(char * row_p, int heightIdx)
{
    char* char_p = row_p;
    int widthIdx = 0;

    while ((*row_p) != '\n')
    {
        global_map[widthIdx][heightIdx] = (*row_p);
        widthIdx += 1;
        row_p += sizeof(char);
    }

    return widthIdx;
}


/* Parse file */
int parse_input(char* filename)
{
    int map_width = -1;
    int row_width = -1;

    FILE* fp;
    char str[MAXCHAR];

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    /* Parse row by row */
    int map_height = 0;
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        row_width = addRowToMap(str, map_height);
        if (row_width >= map_width)
        {
            map_width = row_width;
        }

        map_height += 1;
        for (int i = 0; i < row_width; i++)
        {
            printf("%c", global_map[i][map_height-1]);
        }
        printf("\n");
        
    }
    map_height -= 1; // Adjust for blank row at end
    printf("map height: %d, map width: %d \n", map_height, map_width);

    long long int product = 1;
    product *= treverseMap(map_height, map_width, 1, 1);
    product *= treverseMap(map_height, map_width, 1, 3);
    product *= treverseMap(map_height, map_width, 1, 5);
    product *= treverseMap(map_height, map_width, 1, 7);
    product *= treverseMap(map_height, map_width, 2, 1);

    printf("Product: %lld", product);

    fclose(fp);

    return 0;
}


/* Main */
int main (int argc, char *argv[])
{
    parse_input(R"(C:\Users\watz\Documents\GitHub\AOC\2020\src\day3\example_1.txt)");

    parse_input(R"(C:\Users\watz\Documents\GitHub\AOC\2020\src\day3\input_1.txt)");
}


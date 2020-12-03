// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* --- Day 2: Password Philosophy --- */

#define MAXCHAR (int)100

typedef struct
{
    char letter;
    int min;
    int max;
} data_1_str;

typedef struct
{
    char letter;
    int idx1;
    int idx2;
} data_2_str;

int check_entry_part1(char* row_p);
int parse_input(char* filename, data_1_str* data);

/* Parse row, part 1 */ 
int check_entry_part1(char* row_p)
{
    data_1_str rtn;

    char* char_p = row_p;

    // min
    rtn.min = 0;
    while ((*char_p) != '-')
    {
        rtn.min = rtn.min * 10 + (*char_p) - (char)'0';
        char_p += sizeof(char);
    }
    char_p += sizeof(char);
    //printf("min: %d", rtn.min);

    // max
    rtn.max = 0;
    while ((*char_p) != ' ')
    {
        rtn.max = rtn.max * 10 + (*char_p) - (char)'0';
        char_p += sizeof(char);
    }
    char_p += sizeof(char);
    //printf(", max: %d", rtn.max);

    // letter
    rtn.letter = (*char_p);
    char_p += sizeof(char)*2;
    //printf(", letter: %c", rtn.letter);

    // count letter
    int count = 0;
    while ((*char_p) != '\n')
    {
        if ((*char_p) == rtn.letter)
        {
            count += 1;
        }
        char_p += sizeof(char);
    }
    //printf(", count: %d", count);
    //printf("\n");

    if ((count <= rtn.max) && (count >= rtn.min))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* Parse row, part 2 */
int check_entry_part2(char* row_p)
{
    data_2_str rtn;

    char* char_p = row_p;

    // idx 1
    rtn.idx1 = 0;
    while ((*char_p) != '-')
    {
        rtn.idx1 = rtn.idx1 * 10 + (*char_p) - (char)'0';
        char_p += sizeof(char);
    }
    char_p += sizeof(char);
    printf("idx: %d", rtn.idx1);

    // idx 2
    rtn.idx2 = 0;
    while ((*char_p) != ' ')
    {
        rtn.idx2 = rtn.idx2 * 10 + (*char_p) - (char)'0';
        char_p += sizeof(char);
    }
    char_p += sizeof(char);
    printf(", idx: %d", rtn.idx2);

    // letter
    rtn.letter = (*char_p);
    char_p += sizeof(char) * 3;
    printf(", letter: %c", rtn.letter);

    // Check indexes
    int count = 0;
    int idx = 1;
    while ((*char_p) != '\n')
    {
        if (((*char_p) == rtn.letter) && 
            ((idx == rtn.idx1) || (idx == rtn.idx2)))
        {
            count += 1;
        }
        char_p += sizeof(char);
        idx += 1;
    }

    printf(", count: %d", count);
    printf("\n");

    if (count == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/* Parse file */
int parse_input(char* filename, data_1_str * data)
{
    FILE* fp;
    char str[MAXCHAR];

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    /* Parse row by row */
    int numOfCorrectPasswords = 0;
    int numOfCorrectPasswrodsPart2 = 0;
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        numOfCorrectPasswords += check_entry_part1(str);
        numOfCorrectPasswrodsPart2 += check_entry_part2(str);
        printf("%s", str);
    }
    printf("number of passwords correctly formated: %d\n", numOfCorrectPasswords);
    printf("number of passwords correctly formated (part 2): %d\n", numOfCorrectPasswrodsPart2);
        
    fclose(fp);

    return 0;
}

/* Main */
int main (int argc, char *argv[])
{
    data_1_str example1[3];
    data_1_str input1[1000];
    data_1_str * input_p;

    input_p = example1;
    parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day2\example_1.txt)", input_p);

    input_p = input1;
    parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day2\input_1.txt)", input_p);


}


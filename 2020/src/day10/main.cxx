// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAXCHAR         (int)10
#define MAXENTRIES      (int)110

/* Function declarations */
int parse_input(char* filename);
void sort_array(int* array, int length);
void count_diff(int* array, int length);
int count_permutations(int* array, int length);
int fact(int input);

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
    int adapterList[MAXENTRIES] = { 0 };
    int current = 0;
    int numOfAdapters;

    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        // Treat array as pointer
        row_p = str;

        while (*row_p != '\n')
        {
            current = current * 10 + (*row_p - '0');
            row_p++;
        }

        // Update
        adapterList[Idx] = current;
        current = 0;

        // increase idx with wraparound
        Idx += 1;
    }
    numOfAdapters = Idx;
    fclose(fp);

    sort_array(adapterList, numOfAdapters);

    for (int i = 0; i < numOfAdapters; i++)
    {
        printf("%d\n", adapterList[i]);
    }

    count_diff(adapterList, numOfAdapters);

    int numOfRedundant;
    numOfRedundant = count_permutations(adapterList, numOfAdapters);
    printf("Permutations: %d\n", numOfRedundant);

    return 0;
}

void sort_array(int* array, int length)
{
    int temp;
    bool isSorted = false;

    /* bouble sort */
    while (!isSorted)
    {
        isSorted = true;
        for (int i = 0; i < (length - 1); i++)
        {
            if (array[i] > array[i + 1])
            {
                temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;

                isSorted = false;
            }
        }
    }

    return;
}

#define MAX_DIFF (int)3
void count_diff(int* array, int length)
{
    int diff[MAX_DIFF + 1] = { 0 };

    /* First entry diffed against 0 */
    diff[array[0] - 0] += 1;

    for (int i = 0; i < length; i++)
    {
        if (i == length - 1)
        {
            diff[3] += 1;
        }
        else
        {
            diff[array[i + 1] - array[i]] += 1;
        }
    }

    for (int i = 0; i <= MAX_DIFF; i++)
    {
        printf("Number of %d diffs: %d jolt(s)\n", i, diff[i]);
    }
    printf("1 jolts * 3 jolts = %d * %d = %d\n", diff[1], diff[3], diff[1] * diff[3]);
}

int count_permutations(int* array, int length)
{
    int numOfOnes = 0;
    int numOfPermutations = 1; // no plugs removed

    for (int i = 0; i < length-1; i++)
    {
        if (array[i + 1] - array[i] == 1)
        {
            numOfOnes += 1;
        }
        else
        {
            if (numOfOnes == 2)
            {
                numOfPermutations *= 2;
            }

            if (numOfOnes == 3)
            {
                numOfPermutations *= 4;
            }

            if (numOfOnes == 4)
            {
                numOfPermutations *= 7;
            }

            numOfOnes = 0;
        }
    }

    return numOfPermutations;
}

int fact(int input)
{
    if (input == 1)
    {
        return 1;
    }
    else
    {
        return (input * fact(input - 1));
    }
}


/* Main */
int main(int argc, char* argv[])
{
    printf("fact 1: %d\n", fact(1));
    printf("fact 2: %d\n", fact(2));
    printf("fact 3: %d\n", fact(3));
    printf("fact 4: %d\n", fact(4));

    // example
    parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day10\example_1.txt)");
    parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day10\example_2.txt)");

    // input 1
    //parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day10\input_1.txt)");

}


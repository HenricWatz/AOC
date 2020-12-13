// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define MAXCHAR         (int)20
#define MAXPREAMBLE     (int)25
#define MAXENTRIES      (int)1000

/* Function declarations */
int parse_input(char* filename, int preamble);
bool checkEntry(int preList[], int preamble, int current);

/* Parse file */
int parse_input(char* filename, int preamble)
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
    int preList[MAXPREAMBLE] = { 0 };
    int entryList[MAXENTRIES] = { 0 };
    int* entry_p = entryList;
    int current = 0;
    int faultyValue;
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        // Treat array as pointer
        row_p = str;

        // Get current number
        current = 0;
        while (*row_p != '\n')
        {
            current = current * 10 + (*row_p - '0');
            row_p++;
        }

        // Don't check position until list is filled
        if (preList[preamble - 1] != 0)
        {
            if (!checkEntry(preList, preamble, current))
            {
                printf("First wrong entry: %d\n", current);
                break;
            }
        }

        // Update previous list with new entry
        preList[Idx] = current;
        *entry_p = current;
        entry_p += 1;

        // increase idx with wraparound
        Idx = (Idx + 1) % preamble;
    }
    faultyValue = current;
    fclose(fp);

    bool found = false;
    int sum;
    int i = 0;
    while (!found)
    {
        sum = entryList[i];
        int max = entryList[i];
        int min = entryList[i];
        for (int j = (i + 1); j < MAXENTRIES; j++)
        {
            max = (entryList[j] > max) ? entryList[j] : max;
            min = (entryList[j] < min) ? entryList[j] : min;

            sum += entryList[j];
            if (sum == faultyValue)
            {
                found = true;
                printf("encryption weakness: %d and %d producing %d\n", min, max, (max + min));
                break;
            }
            else if (sum > faultyValue)
            {
                i += 1;
                break;
            }
        }
    }

    return 0;
}

bool checkEntry(int preList[], int preamble, int current)
{
    for (int i=0; i < preamble; i++)
    {
        for (int j=0; j < preamble; j++)
        {
            if ((preList[i] + preList[j]) == current)
            {
                return true;
            }
        }
    }

    return false;
}


/* Main */
int main(int argc, char* argv[])
{


    // example
    parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day9\example_1.txt)", 5);

    // input 1
    parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day9\input_1.txt)", 25);

}


// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* --- Day 2: Password Philosophy --- */

#define MAXCHAR (int)100

typedef struct
{
    bool ecl;
    bool pid;
    bool eyr;
    bool hcl;
    bool byr;
    bool iyr;
    bool cid;
    bool hgt;
} passport_entry;


/* Parse file, return number of inputs */
int parse_input_1(char* filename, passport_entry* data_p)
{
    FILE* fp;
    char str[MAXCHAR];
    char* row;
    int idx;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    /* Parse row by row */
    int num_of_entries = 0;
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        /* Detect new entry */
        if (str[0] == '\n')
        {
            num_of_entries += 1;
            data_p += 1;
        }

        idx = 0;
        while (str[idx] != '\n')
        {
            if (str[idx + 3] == ':')
            {
                if ((str[idx] == 'b') && (str[idx + 1] == 'y') && (str[idx + 2] == 'r'))
                    data_p->byr = true;

                if ((str[idx] == 'c') && (str[idx + 1] == 'i') && (str[idx + 2] == 'd'))
                    data_p->cid = true;

                if ((str[idx] == 'e') && (str[idx + 1] == 'c') && (str[idx + 2] == 'l'))
                    data_p->ecl = true;

                if ((str[idx] == 'e') && (str[idx + 1] == 'y') && (str[idx + 2] == 'r'))
                    data_p->eyr = true;

                if ((str[idx] == 'h') && (str[idx + 1] == 'c') && (str[idx + 2] == 'l'))
                    data_p->hcl = true;

                if ((str[idx] == 'h') && (str[idx + 1] == 'g') && (str[idx + 2] == 't'))
                    data_p->hgt = true;

                if ((str[idx] == 'i') && (str[idx + 1] == 'y') && (str[idx + 2] == 'r'))
                    data_p->iyr = true;

                if ((str[idx] == 'p') && (str[idx + 1] == 'i') && (str[idx + 2] == 'd'))
                    data_p->pid = true;
            }

            idx += 1;
        }

        //printf("%s", str);
    }

    printf("number of passport entries: %d\n", num_of_entries);
    fclose(fp);

    return num_of_entries;
}

/* Parse file, return number of inputs */
int parse_input_2(char* filename, passport_entry* data_p)
{
    FILE* fp;
    char str[MAXCHAR];
    char* row;

    int idx;
    int numEntry;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    /* Parse row by row */
    int num_of_entries = 0;
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        /* Detect new entry */
        if (str[0] == '\n')
        {
            num_of_entries += 1;
            data_p += 1;
        }

        idx = 0;
        while (str[idx] != '\n')
        {
            if (str[idx + 3] == ':')
            {
                if ((str[idx] == 'b') && (str[idx + 1] == 'y') && (str[idx + 2] == 'r'))
                {
                    numEntry = (str[idx + 4] - '0') * 1000 + (str[idx + 5] - '0') * 100 + (str[idx + 6] - '0') * 10 + (str[idx + 7] - '0');
                    if((numEntry >= 1920) && (numEntry <= 2002))
                        data_p->byr = true;
                }
                    
                if ((str[idx] == 'c') && (str[idx + 1] == 'i') && (str[idx + 2] == 'd'))
                    data_p->cid = true; // dont' care

                if ((str[idx] == 'e') && (str[idx + 1] == 'c') && (str[idx + 2] == 'l'))
                {
                    if (((str[idx + 4] == 'a') && (str[idx + 5] == 'm') && (str[idx + 6] == 'b')) ||
                        ((str[idx + 4] == 'b') && (str[idx + 5] == 'l') && (str[idx + 6] == 'u')) ||
                        ((str[idx + 4] == 'g') && (str[idx + 5] == 'r') && (str[idx + 6] == 'y')) ||
                        ((str[idx + 4] == 'g') && (str[idx + 5] == 'r') && (str[idx + 6] == 'n')) ||
                        ((str[idx + 4] == 'h') && (str[idx + 5] == 'z') && (str[idx + 6] == 'l')) ||
                        ((str[idx + 4] == 'o') && (str[idx + 5] == 't') && (str[idx + 6] == 'h')) ||
                        ((str[idx + 4] == 'b') && (str[idx + 5] == 'r') && (str[idx + 6] == 'n')))
                    {
                        data_p->ecl = true;
                    }
                }
                    

                if ((str[idx] == 'e') && (str[idx + 1] == 'y') && (str[idx + 2] == 'r'))
                {
                    numEntry = (str[idx + 4] - '0') * 1000 + (str[idx + 5] - '0') * 100 + (str[idx + 6] - '0') * 10 + (str[idx + 7] - '0');
                    if ((numEntry >= 2020) && (numEntry <= 2030))
                        data_p->eyr = true;
                }

                if ((str[idx] == 'h') && (str[idx + 1] == 'c') && (str[idx + 2] == 'l'))
                {
                    if (((str[idx + 4]) == '#') &&
                        ((((str[idx + 5]) >= '0') && ((str[idx + 5]) <= '9')) || (((str[idx + 5]) >= 'a') && ((str[idx + 5]) <= 'f'))) &&
                        ((((str[idx + 6]) >= '0') && ((str[idx + 6]) <= '9')) || (((str[idx + 6]) >= 'a') && ((str[idx + 6]) <= 'f'))) &&
                        ((((str[idx + 7]) >= '0') && ((str[idx + 7]) <= '9')) || (((str[idx + 7]) >= 'a') && ((str[idx + 7]) <= 'f'))) &&
                        ((((str[idx + 8]) >= '0') && ((str[idx + 8]) <= '9')) || (((str[idx + 8]) >= 'a') && ((str[idx + 8]) <= 'f'))) &&
                        ((((str[idx + 9]) >= '0') && ((str[idx + 9]) <= '9')) || (((str[idx + 9]) >= 'a') && ((str[idx + 9]) <= 'f'))) &&
                        ((((str[idx + 10]) >= '0') && ((str[idx + 10]) <= '9')) || (((str[idx + 10]) >= 'a') && ((str[idx + 10]) <= 'f'))) &&
                        (((str[idx + 11]) == ' ') || ((str[idx + 11]) == '\n')))
                    {
                        data_p->hcl = true;
                    }
                }
                    

                if ((str[idx] == 'h') && (str[idx + 1] == 'g') && (str[idx + 2] == 't'))
                {
                    if ((str[idx + 6] == 'i') && (str[idx + 7] == 'n'))
                    {
                        numEntry = (str[idx + 4] - '0') * 10 + (str[idx + 5] - '0');
                        if((numEntry >= 59) && (numEntry <= 76))
                            data_p->hgt = true;
                    }

                    if ((str[idx + 7] == 'c') && (str[idx + 8] == 'm'))
                    {
                        numEntry = (str[idx + 4] - '0') * 100 + (str[idx + 5] - '0') * 10 + (str[idx + 6] - '0');
                        if ((numEntry >= 150) && (numEntry <= 193))
                            data_p->hgt = true;
                    }
                }

                if ((str[idx] == 'i') && (str[idx + 1] == 'y') && (str[idx + 2] == 'r'))
                {
                    numEntry = (str[idx + 4] - '0') * 1000 + (str[idx + 5] - '0') * 100 + (str[idx + 6] - '0') * 10 + (str[idx + 7] - '0');
                    if ((numEntry >= 2010) && (numEntry <= 2020))
                        data_p->iyr = true;
                }

                if ((str[idx] == 'p') && (str[idx + 1] == 'i') && (str[idx + 2] == 'd'))
                {
                    if ((((str[idx + 4]) >= '0') && ((str[idx + 4]) <= '9')) &&
                        (((str[idx + 5]) >= '0') && ((str[idx + 5]) <= '9')) &&
                        (((str[idx + 6]) >= '0') && ((str[idx + 6]) <= '9'))  &&
                        (((str[idx + 7]) >= '0') && ((str[idx + 7]) <= '9')) &&
                        (((str[idx + 8]) >= '0') && ((str[idx + 8]) <= '9')) &&
                        (((str[idx + 9]) >= '0') && ((str[idx + 9]) <= '9')) &&
                        (((str[idx + 10]) >= '0') && ((str[idx + 10]) <= '9')) &&
                        (((str[idx + 11]) >= '0') && ((str[idx + 11]) <= '9')) &&
                        (((str[idx + 12]) >= '0') && ((str[idx + 12]) <= '9')) &&
                        (((str[idx + 13]) == ' ') || ((str[idx + 13]) == '\n')))
                    {
                        data_p->pid = true;
                    }
                }
            }

            idx += 1;
        }

        //printf("%s", str);
    }

    printf("number of passport entries: %d\n", num_of_entries);
    fclose(fp);

    return num_of_entries;
}

void checkEntries(passport_entry data[], int num_of_entries)
{
    bool data_ok;
    int num_of_valid = 0;

    for (int idx = 0; idx < num_of_entries; idx++)
    {
        data_ok = true;

        if ((!data[idx].byr) ||
            //(!data[idx].cid) ||
            (!data[idx].ecl) ||
            (!data[idx].eyr) ||
            (!data[idx].hcl) ||
            (!data[idx].hgt) ||
            (!data[idx].iyr) ||
            (!data[idx].pid))
        {
            /* Do nothing */
        }
        else
        {
            num_of_valid += 1;
        }
    }

    printf("Number of valid passports: %d\n", num_of_valid);
}

void validateInvalid(passport_entry* data_p)
{
    // entry 0:
    if (data_p->byr != true) { printf("byr failed for idx 0\n"); }
    //if (data_p->cid != true) { printf("cid failed for idx 0\n"); }
    if (data_p->ecl != true) { printf("ecl failed for idx 0\n"); }
    if (data_p->eyr != false) { printf("eyr failed for idx 0\n"); }
    if (data_p->hcl != true) { printf("hcl failed for idx 0\n"); }
    if (data_p->hgt != false) { printf("hgt failed for idx 0\n"); }
    if (data_p->iyr != true) { printf("iyr failed for idx 0\n"); }
    if (data_p->pid != false) { printf("pid failed for idx 0\n"); }

    // entry 1:
    data_p += 1;
    if (data_p->byr != true) { printf("byr failed for idx 1\n"); }
    //if (data_p->cid != false) { printf("cid failed for idx 1\n"); }
    if (data_p->ecl != true) { printf("ecl failed for idx 1\n"); }
    if (data_p->eyr != false) { printf("eyr failed for idx 1\n"); }
    if (data_p->hcl != true) { printf("hcl failed for idx 1\n"); }
    if (data_p->hgt != true) { printf("hgt failed for idx 1\n"); }
    if (data_p->iyr != true) { printf("iyr failed for idx 1\n"); }
    if (data_p->pid != true) { printf("pid failed for idx 1\n"); }

    // entry 2:
    data_p += 1;
    if (data_p->byr != true) { printf("byr failed for idx 2\n"); }
    //if (data_p->cid != true) { printf("cid failed for idx 2\n"); }
    if (data_p->ecl != true) { printf("ecl failed for idx 2\n"); }
    if (data_p->eyr != true) { printf("eyr failed for idx 2\n"); }
    if (data_p->hcl != false) { printf("hcl failed for idx 2\n"); }
    if (data_p->hgt != true) { printf("hgt failed for idx 2\n"); }
    if (data_p->iyr != true) { printf("iyr failed for idx 2\n"); }
    if (data_p->pid != true) { printf("pid failed for idx 2\n"); }

    // entry 3:
    data_p += 1;
    if (data_p->byr != false) { printf("byr failed for idx 3\n"); }
    //if (data_p->cid != false) { printf("cid failed for idx 3\n"); }
    if (data_p->ecl != false) { printf("ecl failed for idx 3\n"); }
    if (data_p->eyr != false) { printf("eyr failed for idx 3\n"); }
    if (data_p->hcl != false) { printf("hcl failed for idx 3\n"); }
    if (data_p->hgt != false) { printf("byr failed for idx 3\n"); }
    if (data_p->iyr != false) { printf("iyr failed for idx 3\n"); }
    if (data_p->pid != false) { printf("pid failed for idx 3\n"); }
}

/* Main */
int main(int argc, char* argv[])
{
    int num_of_entries;
    passport_entry ex_input[10] = { false };
    passport_entry input1[1000] = { false };
    passport_entry invlaid[10]  = { false };
    passport_entry valid[10]    = { false };
    passport_entry input2[1000] = { false };

    passport_entry* input_p;

    printf("Example:\n");
    input_p = ex_input;
    num_of_entries = parse_input_1(R"(C:\Users\Watz\Desktop\AOC\2020\src\day4\example_1.txt)", input_p);
    checkEntries(input_p, num_of_entries);

    printf("Input:\n");
    input_p = input1;
    num_of_entries = parse_input_1(R"(C:\Users\Watz\Desktop\AOC\2020\src\day4\input_1.txt)", input_p);
    checkEntries(input_p, num_of_entries);

    printf("Invalid:\n");
    input_p = invlaid;
    num_of_entries = parse_input_2(R"(C:\Users\Watz\Desktop\AOC\2020\src\day4\invalid_2.txt)", input_p);
    validateInvalid(input_p);
    checkEntries(input_p, num_of_entries);

    printf("Valid:\n");
    input_p = valid;
    num_of_entries = parse_input_2(R"(C:\Users\Watz\Desktop\AOC\2020\src\day4\valid_2.txt)", input_p);
    checkEntries(input_p, num_of_entries);

    printf("Input (2):\n");
    input_p = input2;
    num_of_entries = parse_input_2(R"(C:\Users\Watz\Desktop\AOC\2020\src\day4\input_1.txt)", input_p);
    checkEntries(input_p, num_of_entries);
}


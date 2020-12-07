// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* --- Day 5: Binary Boarding --- */

#define MAXCHAR (int)150

#define MAXCOLOURLENGTH         (int)30
#define MAX_BAGTYPES_IN_BAGS    (int)6
#define MAX_BAGS_CONTAINED_IN   (int)10
#define MAX_BAG_TYPES           (int)600

enum containBagColour
{
    UNKNOWN = 0,
    YES,
    NO
};

// Data structure for bag tree
typedef struct BAG BAG;
struct BAG
{
    char colour[MAXCOLOURLENGTH];
    int  colourLength;
    BAG * contentColour_p[MAX_BAGTYPES_IN_BAGS];
    int contentAmount[MAX_BAGTYPES_IN_BAGS];
    containBagColour containBagColourFlag;
};

/* Data structure for bag tree */
int     number_of_bag_colours;
BAG     bagList[MAX_BAG_TYPES] = { "", 0, NULL, 0 };


/* Function declarations */
bool compareCharArray(char* lhs, char* rhs, int length);
int isContaining(BAG* bag_p, char* bagColour);
int parse_input(char* filename);

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
    FILE* fp;
    char    str[MAXCHAR];
    char*   bagColour_p;
    char*   row_p;
    int     bagIdx;
    int     contentIdx;
    char    bagColour[MAXCOLOURLENGTH];


    // POPULATE BAG LIST WITH COLOURS
    bagIdx = 0;
    bagColour_p = bagList[bagIdx].colour;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    /* Parse row by row */
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        // Treat array as pointer
        row_p = str;

        while (!compareCharArray(row_p, " bags contain", 13))
        {
            // Add char to name text
            *bagColour_p = *row_p;

            // next char
            bagColour_p++;
            row_p++;

            // Save length of bag colour for search purposes
            bagList[bagIdx].colourLength++;
        }
        
        // Update colour pointer (add next bag)
        bagIdx++;
        bagColour_p = bagList[bagIdx].colour;
    }
    number_of_bag_colours = bagIdx;
    fclose(fp);




    // POPULATE BAG LIST WITH CONTENT
    bagIdx = -1;

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    /* Parse row by row */
    while (fgets(str, MAXCHAR, fp) != NULL)
    {
        // Treat array as pointer
        row_p = str;

        // Update bag colour being mapped
        bagIdx++;
        while (!compareCharArray(row_p, " bags contain", 13))
        {
            /* Bags come in the same order so we know index (and colour) of current bag */
            row_p++;
        }
        row_p += 13 + 1;  // plus one for trailing space

        // Identify bags with no content
        if (compareCharArray(row_p, "no other bags.", 14))
        {
            /* Move on to next bag colour */
        }
        else
        {
            // Add amount to index 0
            contentIdx = 0;
            bagList[bagIdx].contentAmount[contentIdx] = (*row_p - '0'); // this works since no bag contains more then 9 of the same colour
            row_p += 2; //number + trailing space

             // pointer to color of bag
            bagColour_p = bagColour;

            while (!compareCharArray(row_p, " bags.", 6) &&
                   !compareCharArray(row_p, " bag.", 5))
            {
                if (compareCharArray(row_p, " bags,", 6) ||
                    compareCharArray(row_p, " bag,", 5))
                {
                    // Remove "bags" + trailing space
                    if (compareCharArray(row_p, " bags,", 6))
                    {
                        row_p++;
                    }
                    row_p += 6;
                    

                    // find index of bag colour and add pointer to bag struct
                    for (int i = 0; i < number_of_bag_colours; i++)
                    {
                        if (compareCharArray(bagList[i].colour, bagColour, bagList[i].colourLength))
                        {
                            bagList[bagIdx].contentColour_p[contentIdx] = &bagList[i];
                        }
                    }

                    // Reset colour pointer
                    bagColour_p = bagColour;

                    // Update content index
                    contentIdx++;

                    // Add amount 
                    bagList[bagIdx].contentAmount[contentIdx] = (*row_p - '0'); // this works since no bag contains more then 9 of the same colour
                    row_p += 2; //number + trailing space
                }

                // Add char to bag colour
                *bagColour_p = *row_p;

                if (bagColour_p < (bagColour + MAXCOLOURLENGTH))
                {
                    bagColour_p++;
                }
                row_p++;
            }

            // Add last colour to results
            for (int i = 0; i < number_of_bag_colours; i++)
            {
                if (compareCharArray(bagList[i].colour, bagColour, bagList[i].colourLength))
                {
                    bagList[bagIdx].contentColour_p[contentIdx] = &bagList[i];
                }
            }
        }

        //printf("%s", str);
    }
    fclose(fp);

    for (int i = 0; i < number_of_bag_colours; i++)
    {
        printf("Bag color %s: ", bagList[i].colour);

        if (bagList[i].contentColour_p[0] == NULL)
        {
            printf("Contains no bags!");
        }
        else
        {

            int idx = 0;
            while (bagList[i].contentColour_p[idx] != NULL)
            {
                printf("%s, ", bagList[i].contentColour_p[idx]->colour);
                idx++;
            }
        }

        printf("\n");
    }
    
    return 0;
}

int isContaining(BAG* bag_p, char* bagColour)
{
    int contentIdx;
    bool rtn_value;

    if (bag_p->containBagColourFlag == UNKNOWN)
    {
        if (compareCharArray(bagColour,
            bag_p->colour,
            bag_p->colourLength))
        {
            // Bag contains itself.
            rtn_value = true;
            bag_p->containBagColourFlag = YES;
        }
        else if (bag_p->contentColour_p[0] == NULL)
        {
            // Bag don't contain any other bags
            rtn_value = false;
            bag_p->containBagColourFlag = NO;
        }
        else
        {
            // Look through the content
            contentIdx = 0;
            rtn_value = false;
            while (bag_p->contentColour_p[contentIdx] != NULL)
            {
                if (isContaining(bag_p->contentColour_p[contentIdx], bagColour))
                {
                    rtn_value = true;
                }
                contentIdx++;
            }

            // Remember result
            if (rtn_value == true)
            {
                bag_p->containBagColourFlag = YES;
            }
            else
            {
                bag_p->containBagColourFlag = NO;
            }
        }
    }
    else
    {
        // Use old value if exist
        if (bag_p->containBagColourFlag == YES)
        {
            rtn_value = true;
        }
        else
        {
            rtn_value = false;
        }

    }

    return rtn_value;
}

int countBagColoursContainingColour(char* bagColour)
{
    int rtn_value = 0;

    for (int i = 0; i < number_of_bag_colours; i++)
    {
        if (isContaining(&bagList[i], bagColour))
        {
            rtn_value++;
        }
    }

    // Don't count the bagColour itself
    rtn_value -= 1;

    return rtn_value;
}

BAG * getBagByColour(char* bagColour)
{
    int idx = 0;

    while (!compareCharArray(bagList[idx].colour, bagColour, bagList[idx].colourLength))
    {
        idx++;
    }

    return &bagList[idx];
}

int countBagsInBag(BAG* bag_p)
{
    int contentIdx;
    int rtn_value = 1;

    contentIdx = 0;
    while (bag_p->contentColour_p[contentIdx] != NULL)
    {
        rtn_value += countBagsInBag(bag_p->contentColour_p[contentIdx]) * bag_p->contentAmount[contentIdx];
        contentIdx++;
    }

    return rtn_value;
}

/* Main */
int main(int argc, char* argv[])
{


    // example
    //parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day7\example_1.txt)");
    //printf("Bags containing shiny gold: %d", countBagColoursContainingColour("shiny gold"));

    // example 2
    //parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day7\example_2.txt)");
    //printf("Shiny gold contains: %d Bags", countBagsInBag(getBagByColour("shiny gold")) - 1);

    parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day7\input_1.txt)");
    printf("Bags containing shiny gold: %d\n", countBagColoursContainingColour("shiny gold"));
    printf("Shiny gold contains: %d Bags\n", countBagsInBag(getBagByColour("shiny gold")) - 1);



    //// input
    //parse_input(R"(C:\Users\Watz\Desktop\AOC\2020\src\day6\input_1.txt)");

    //// example
    //parse_input2(R"(C:\Users\Watz\Desktop\AOC\2020\src\day6\example_1.txt)");

    //// input
    //parse_input2(R"(C:\Users\Watz\Desktop\AOC\2020\src\day6\input_1.txt)");
}


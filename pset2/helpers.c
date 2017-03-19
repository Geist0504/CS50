/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    for(int i = 0; i < value; i++)
    {
        if(values[i] == n)
        {
            return true;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement an O(n^2) sorting algorithm
    int counter = 1;
    while(counter !=0){
        for(int i = 0; i< n; i++){
            counter = 0;
            if(values[i] > values[i+1]){
                int swapOne = values[i];
                int swapTwo = values[i+1];
                values[i] = swapTwo;
                values[i+1] = swapOne;
                counter++;
            }
        }
    }
}

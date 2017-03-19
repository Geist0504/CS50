/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
 
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    int start = 0;
    int mid = 0;
    int end = n;
    while(end-start > -1)
    {
        mid = (start+end)/2;
        if(values[mid] == value)
        {
            return true;
        }
        else if (values[mid] > value)
        {
            end = mid-1;
            //search(value, values, end);
        }
        else if (values[mid] < value)
        {
            start = mid + 1;
            //search(value, values, end);
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
        counter = 0;
        for(int i = 0; i < n-1; i++){
            if(values[i] > values[i+1]){
                int swapOne = values[i];
                int swapTwo = values[i+1];
                values[i] = swapTwo;
                values[i+1] = swapOne;
                counter++;
            }
        }
    }
    for(int i = 0; i< n; i++){
        printf("%i\n", values[i]); 
    }

}

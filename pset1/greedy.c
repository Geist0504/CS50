#include <stdio.h>
#include <cs50.h>

void coins_needed(float f);

int main(void)
{
    printf ("O hai! How much change is owed? ");
    float change = get_float();
    while (change < 0){
        printf("Number must be positive. Please try again: ");
        change = get_float();
    }
    printf ("%.2f\n", change);
    coins_needed(change);
}

void coins_needed(float f)
{
    int count = 0;
    while (f > 0.0)
    {
        if (f >= .25)
        {
            f -= .25;
            count +=1;
        }
        else if (f >=.10)
        {
            f -= .10;
            count +=1;
        }
        else if (f >=.05)
        {
            f -= .05;
            count +=1;
        }
        else
        {
            f -= .01;
            count +=1;
        }
    }
    printf("%i coins needed\n", count);
}
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Minutes: ");
    int water = get_int();
    printf("Bottles of water: %i\n", water * 12);
}
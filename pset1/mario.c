#include <stdio.h>
#include <cs50.h>

void build(int n);

int main(void)
{
    printf("How many rows?: ");
    int rows = get_int();
    while (rows < 0 || rows > 23){
        printf("Number must be between 0 & 23. Please try again: \n");
        rows = get_int();
    }
        build(rows);
}

void build(int n){
    for (int i = 0; i<n; i++){
        for (int b = 0; b<n-i; b++){
            printf(" ");
        }
        if( i > 0){
            for (int c = 0; c<i; c++){
                printf("#");
            }
        }
        printf("##\n");
    }
}

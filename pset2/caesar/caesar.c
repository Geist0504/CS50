#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int flatten(int j);
void rotate(string str, int i);


int main(int argc, string argv[])
{
    if(argc == 2)
    {
        int i = flatten(atoi(argv[1]));
        printf("plaintext:");
        string s = get_string();
        printf("ciphertext:"); 
        rotate(s, i);
        printf("\n");
        return 0;
    }
    else{
        printf("Error code 1. Please input interger\n");
        return 1;
    }
}


void rotate(string str, int i)
{
    //iterates through entire string
    for (int j = 0; j<strlen(str); j++)
    {
        int key = i;
        //checks if letter is capital
        if(str[j] > 64 && str[j] <91){
            //test if character will need to wrap around & wrap if needed
            if(str[j]+i >= 91){
                key = str[j]+i - 90;
                printf("%c",64+key);
            }
            else{
                printf("%c",str[j]+key);
            }
        }
        //checks if lower case
        else if (str[j] > 96 && str[j] <123)
        {
            //test if character will need to wrap around & wrap if needed
            if(str[j]+i>=123){
                key = str[j]+i - 122;
                printf("%c",96+key);
            }
            else
            {
            printf("%c",str[j]+i);
            }
        }
        else
        {
            printf("%c", str[j]);
        }
    }
}

//takes integer and reduces it to equivalent on 26 point scale to provide a workable key
int flatten(int j)
{
    if (j >= 26)
    {
        return j % 26;
    }
    else
    {
        return j;
    }
}
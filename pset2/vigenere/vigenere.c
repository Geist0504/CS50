#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int keyPos = 0;

int flatten(int j);
void rotate(string str, string code);
int test(string str);
int getKey(string codeWord);

int main(int argc, string argv[])
{
    if(argv[1] == NULL){
        printf("Error code 1. Please input key word\n");
        return 1;
    }
    int boo = test(argv[1]);
    if(argc == 2 && boo == 0)
    {
        string code = argv[1];
        printf("plaintext:");
        string s = get_string();
        printf("ciphertext:"); 
        rotate(s, code);
        printf("\n");
        return 0;
    }
    else{
        printf("Error code 2. Please input words only\n");
        return 1;
    }
}

//gets key value based on place in key word
int getKey(string codeWord)
{
    if(keyPos >= strlen(codeWord))
    {
        keyPos = 0;
    }
    char key = toupper(codeWord[keyPos]);
    //printf("key is %c\n", key);
    return key - 65;
}

//prints out coded word
void rotate(string str, string code)
{
    //iterates through entire string
    for (int j = 0; j<strlen(str); j++)
    {
        //gets key and initializes a wrap value
        int i = getKey(code);
        int wrap = 0;
        //checks if letter is capital
        if(str[j] > 64 && str[j] <91){
            //test if character will need to wrap around & wrap if needed
            if(str[j]+i >= 91){
                wrap = str[j]+i - 90;
                printf("%c",64+wrap);
            }
            else{
                printf("%c",str[j]+i);
            }
            keyPos++;
        }
        //checks if lower case
        else if (str[j] > 96 && str[j] <123)
        {
            //test if character will need to wrap around & wrap if needed
            if(str[j]+i>=123){
                wrap = str[j]+i - 122;
                printf("%c",96+wrap);
            }
            else
            {
            printf("%c",str[j]+i);
            }
            keyPos++;
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

//test if all characters in a string are alphabetical returns false if any non-alphabetical
int test(string str)
{
    for (int j = 0; j<strlen(str); j++)
    {
        //checks if letter is capital
        if(str[j] < 64 || str[j] >= 123){
            return 1;
        }
        //checks if lower case
        else if (str[j] < 96 && str[j] >= 91)
        {
            return 1;
        }
    }
    return 0;
}
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#define _XOPEN_SOURCE
#include <unistd.h>

int crypt(char key, int t);

int main(int argc, string argv[])
{
    string t = argv[1];
    char key[3];
    strncpy(key, t, 2);
    key[2] = '\0';
    char pw = crypt(key, t);
    printf("%c", pw);
}
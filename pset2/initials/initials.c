#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    //Obtain Name from user
    string s = get_string();
    
    //Capture initials, print first initial
    char init = toupper(s[0]);
    printf("%c",init);
    
    //iterate over name and print relevant intials
    for (int i = 1; i < strlen(s); i++)
    {
        if (s[i] == ' '){
            printf("%c",toupper(s[i+1]));
        }
    }
    printf("\n");
    
}

/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int count = 0;

//create the struct node
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//initialize a hashtable
node *hashtable[HASHTABLE_SIZE];

//hashing function
int hash_word(const char* to_hash)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(to_hash); i<n; i++)
    {
        hash = (hash << 2) ^ tolower(to_hash[i]);
    }
    return hash % HASHTABLE_SIZE;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary,"r");
    if (dict == NULL)
    {
        printf("Could not load %s\n", dictionary);
        return false;
    }
    
    //malloc a node to hold values
    node *new_node = malloc(sizeof(node));
    if (new_node == NULL)
    {
        unload();
        return false;
    }
    //scan dictionary word by word
    while (fscanf(dict, "%s", new_node->word) != EOF)
    {
        //hash the word
        int index = hash_word(new_node->word);
        
        //create new node to be added to hash table
        node *curr = malloc(sizeof(node));
        if (curr == NULL)
        {
            unload();
            return false;
        }
        strcpy(curr->word, new_node->word);
        
        //insert word into hashtable
        if (hashtable[index] == NULL)
        {
            curr->next = NULL;
            hashtable[index] = curr;
            count++;
        }
        else
        {
            curr->next = hashtable[index]->next;
            hashtable[index]->next = curr;
            count++;
        }
    }
    return true;
}
 

/**
 * Returns true if word is in dictionary else false.
 */

 
bool check(const char *word)
{
    //hashes word
    int index = hash_word(word);
    //initializes nodes
    node *head = hashtable[index];
    node *cursor = head;
    
    while (cursor != NULL)
    {
        //case compares supplied word with word at current node
        const char *comp = cursor->word;
        if(strcasecmp(word, comp) == 0)
        {
            return true;
        }
        else
        {
            cursor = cursor->next;
        }
    }
    //word not found
    return false;
}



/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{

    return count;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    //
    for(int i=0; i <=HASHTABLE_SIZE; i++)
    {
        node *cursor = hashtable[i];
        if(cursor == NULL)
        {
            continue;
        }

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }
        
    }
    return true;
}

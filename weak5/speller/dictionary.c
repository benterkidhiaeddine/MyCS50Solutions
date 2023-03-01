// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include <math.h>

#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26 *26*26 * 26*26;

// Hash table
node *table[N];

//size of Dictionnar

unsigned int Size = 0 ;

//add_node to linked list
void add_node(  node** head , char* word);

//free_list the whole linked list

void free_list (node * head );

// Returns true if word is in dictionary, else false
bool check(const char *word)
{


    //first we hash the word to go to the apropriate bucket in the array
    unsigned int hashed = hash (word);

    //we itterate over the linked list looking for the word with strcmp

    for ( node * tmp = table [hashed];tmp!= NULL;tmp = tmp->next)
    {
        if(strcasecmp (tmp->word , word)== 0)
        {

            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hashed = 0 ;
    //a detrmines how manny letters after the first one we consider as buckt
    int a =6;
    for (int i =1 ;word[i]!='\0';i++)
    {
        if (word[i])
        hashed += (toupper(word[i]) - 'A')* pow(26,a-i)<0? 0 : (toupper(word[i]) - 'A') * pow(26,a-i);
    }
    // TODO: Improve this hash function
    return hashed%N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //buffer char to store chars that we are going to put in word

    char letter;

    //string to store the word we have read from the dictionnary
    char word_dic[LENGTH +1];

    //open the dictionnary
    FILE * dict =fopen((dictionary) ,"r");

    //checks if the the opening of the dictionary is successful
    if ( dict == NULL)
    {
        return false;
    }


    //read words from the dictionnary file one char  at a time :every words starts with a lower case letter and ends with '\0'
        //declare a variable to keep track of the index for each word



        //while we haven't reached end of file

    while ( fscanf(dict , "%s" , word_dic)!=EOF)
    {

            //each time a word is read we increment the size by one

            Size++;

            //we put the word through the hash function


            unsigned int hashed = hash(word_dic);

            //we put the words into the hash tablle
                //to do that we need to add the word to a node of the linked list whose head pointer is at the location table [hashed]
            // we define a function that add new nodes to linked list taking as input a pointer to the pointer of head of the linked list and the value with return void
            add_node(&table[hashed],word_dic);
    }




    //closes the dictionnary
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return Size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //we itterate over each element of the array
    for (int i=0 ; i < N ; i++)
    {
        //we free the linked list therin
        free_list(table[i]);
    }

    return true;
}


void add_node( node ** head , char* wordd)
{
    //allocate the necessary memory for the new node
    node * new =malloc(sizeof(node));

    //check if there exists a chunk of memory for the necessary node
    if(new == NULL)
    {
        return;
    }

    //add the new node to the linked list
    //set the next pointer of the new node pointing to the old head of the list
    new -> next = (*head);
    //set the word of the new word to the word argument given to the fucntion using the strcpy
    strcpy(new -> word , wordd);
    //finally set the new node as the new head of the list

    (*head)=new;


}

//function that free the linked list recursivly
void free_list (node * head )
{
    if (head == NULL)
    {
        return ;
    }

    free_list(head -> next) ;
    free(head);

}


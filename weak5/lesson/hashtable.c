#include <stdio.h>
#include <stdlib.h>

// we are going to define nodes of linked lists so we we can incorrperate them into an array of said nodes and we call a hashtable
int LONGEST_AVAIBLE_WORD =124;
typedef struct node

{
    //we are going to hash names
    char word [LONGEST_AVAIBLE_WORD+1];
    struct node * next ;


}
node;

int main (void)
{
    //hash table is an array of pointers to nodes which are the begining of a linked list

    node* hashtable [26];
     //here 26 denotes the numbers of letters in the alphabet denoting the begining letter of each word in our hastable

     // to know where each name goes we use a hash function
     /* for example we ha ve a name harry harry starts with an h
     we take the h and we substract 65 from so we get it's index in accordance with the alphabet which is 8
     so 'h' - 65 and we insert harry in hashtable [8]->word= harry*/

}
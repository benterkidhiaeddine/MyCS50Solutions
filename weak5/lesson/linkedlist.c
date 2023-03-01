#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

 //we first define a node data structure as part of the linked list building block
typedef struct node
{
        //the node contains a number and a pointer to next node
        int number ;
        struct node* next;

}
node;

bool is_present ( node * head , int target);
void free_lls (node * head );
node* insert (node * head , int number1);
void destroy( node* head);


int main (void)
{
    //we should note that searching linked lists take in the worst case scenario O(n) time and inserting take O(1) if we don't care about keeping the list sorted and O(n) if we want to keep the list sorted because we will go through the whole list

    //now to declare a linked list in C we use a pointer to  a node as good practice we set it NULL
    node * linked_list = NULL;

    //then we allocate enough memory for the node and set the adress of that chunk of memory to the n pointer

    node * n = malloc(sizeof(node));
    if( n==NULL)
    {

        return 1;
    }
    //we use the derefrence operator *n to acess what's in the memory chunk pointed at by n and .number to acess the number variable part of that node struct
    //(*n).number = 1;
    // we have as syntactic sugar the following symbol that means the same as the above which is ->
    n->number=1;
    n->next = NULL;

    //now we set the adress of n to linked_list
    linked_list = n;

    //now to add another element to this list what we need to do is allocate new memory with a new adress to n
    n=malloc(sizeof(node));
    if(n==NULL)
    {
        free(linked_list);
        return 2 ;
    }
    //we set number of n to our next number 2
    n->number = 2;
    n->next =NULL ;

    //and then weset linked_list . next which means the pointer of the first elemnt to the adress of our new element
    linked_list->next = n;


    //lastly we add the third element as an example

    //allocate memory to n

    n= malloc (sizeof(node));
    if (n==NULL)
    {
        //we should always free the memory allocate to the nodes in reverse order because we shoudl never free memory that has been already been freed
        free(linked_list->next);
        free(linked_list);
        return 3;
    }

    n->number = 3;
    n->next = NULL;
    linked_list->next->next = n;

    //printing the value in a linked list is diffrent , we can't use the brackets with i notation in a for loop
    //insted we use the following for loop make use of the fact that the final node of a linked list the next pointer in it points to NULL so we know that we are at the end of a list
    //we declare  a new pointer which is the same a list pointing to the begining of our first elemnt in the list and to itterate we assign to that pointer  whatever pointer is  the next field of the first node of list and so on


    linked_list =insert (linked_list , 7);
    linked_list =insert (linked_list , 9);
    linked_list =insert (linked_list , 10);

    for(node * tmp = linked_list; tmp!= NULL ;tmp=tmp->next)
    {
        printf("%i\n",tmp->number);
    }

    printf(is_present ( linked_list , 10)? "found\n": "not found\n");





    destroy ( linked_list);
    return 0;
}


// create a function that searchs through a linked list for a given value

bool is_present ( node * head , int target)
{
    for ( node * searcher = head ; searcher!= NULL;searcher = searcher ->next)
    {
        if (searcher-> number == target )
        {
            return true;
        }
    }

    return false ;


}

//create a fucntion that inserts a new node in  the linked_list we prefer that this node is inserted at the begining to avoid the fact that we have to go through all the list to do making the time complexity O(n) to insert a single element


node* insert (node * head , int number1)


{
    node * new = malloc(sizeof(node));
    if(new!=NULL)
    {
        new -> next = head;
        new -> number  = number1;
        head = new ;
    }
 return  head ;

}

//create a function that frees all the nodes in the lined list

void free_lls (node * head )
{
    while (head != NULL)
    {
        node * tmp = head ->next;
        free (head);
        head = tmp ;

    }


}

//a function that destroys the linked_list it's basicaly recursivly freeing the linked list

void destroy( node* head)
{

    if ( head == NULL)
    {
        return;
    }

    destroy ( head->next);
    free(head);

}
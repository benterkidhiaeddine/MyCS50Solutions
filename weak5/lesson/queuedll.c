#include <stdlib.h>
#include <stdio.h>

//try to implement a queue data structure as a doubly linked list


typedef struct node_queue
{
    int value ;
    struct node_queue* prev;
    struct node_queue* next;
}queue;

//declare the queue's front
queue * front = NULL;

//declare the queue's tail

queue* tail =NULL;


void enqueue (queue ** taill , int num);

int main (void)
{



    queue * n = malloc(sizeof(queue));
    if(n==NULL)
    {
        return 1 ;
    }

    n->value = 10;
    n->prev =NULL;
    n->next =NULL;
    //setting the front value
    front = n;

     n = malloc (sizeof( queue));

    if (n==NULL)
    {
        free(front);
        return 1;
    }

    n->value = 20;
    n->prev = front ;
    n->next =NULL;

    //setting the tail value
    tail = n ;

    front ->next = tail;

    enqueue ( &tail , 30);
    enqueue ( &tail , 40);
    enqueue ( &tail , 50);


    for ( queue * traverse = front ; traverse !=NULL;traverse = traverse ->next)
    {
        printf("%i\n",traverse->value);
    }



}



void enqueue (queue ** taill , int num)


{
    queue * new = malloc(sizeof(queue));
    if(new!=NULL)
    {
        //set the next of new to NULL because it's the last added value to doubly linked list
        new -> next = NULL;
        //set the prev value to point to the old tail of the ddllist
        new -> prev  = (*taill);
        //set the numerical value to be storded
        new -> value =num;
        //set the old tail to point to the new tail
        (*taill)->next = new ;
        //set the tail pointer to point to the new value
        (*taill) = new  ;
    }
 return  ;

}
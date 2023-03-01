#include <stdlib.h>
#include <stdio.h>

#define CAPACITY 10
//queus are a first in first out data structure FIFO



//there are two main functions we can apply on a queue data structure
//enqueue which is to add an element to the end of the list
//dequeue which is to remove the oldest element from the front of the list

typedef struct queue
{
    int queue_arr[CAPACITY];
    int front;
    int size;
}queue;

void enqueue (queue * q , int num);
int dequeue (queue * q);

int main (void)
{

    //initialising a queue data structure with its front and size set to 0
    queue q;
    q.front=0;
    q.size=0;

    enqueue (&q , 1);
    enqueue (&q , 2);
    enqueue (&q , 4);
    enqueue (&q , 8);
    enqueue (&q , 10);

    //print the element of the queue for testing purposes after enqueing them
    for (int i=0 ; i < 5 ;i++)
    {
        printf("%i\n",q.queue_arr[q.front+i]);
    }

    //print the element of the queue for each dequeue


    for (int i=0;i < 5; i++)
    {
        printf("%i\n",dequeue(&q));
    }

     //print the element of the queue for testing purposes after dequeing them
    for (int i=0 ; i < 5 ;i++)
    {
        printf("%i\n",q.queue_arr[q.front+i]);
    }

    return 0;
}

//def a fucntion that enqueus an element


void enqueue (queue * q , int num)
{
    //add the newst element  to array location front +size taken to modul of the CAPACITY so it wraps around when it reach the end of array
    q->queue_arr[(q->front + q->size)%CAPACITY ]=num;
    q->size++;

}


//def a function that dequeues an element


int dequeue (queue * q)
{
    int temp = q ->queue_arr [q-> front ];
    q->front ++;
    q->size --;
    return temp;
}
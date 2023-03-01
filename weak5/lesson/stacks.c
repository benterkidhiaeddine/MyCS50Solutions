#include <stdlib.h>
#include <stdio.h>

#define CAPACITY  10
typedef struct stack
{
    //the stack is composed of two elements the first one is the array that is going to hold the elements of the stack
    int stack_array [CAPACITY];

    //an integer that keeps track of the index of the latest element addded on top of the stack

    int top;
}stack;

void push ( stack * s , int num);
int pop(stack * s );

//to interact with a stack we need to define two functions
// the push() function that pushed an element on top of the stack
//the pop () function that get us the element on top of the stack
//both these functions need to be implemented using pointer we need to act on the stack variable by refrence and not by value

int main(void)
{


    stack s ;

    //initilise the top as -1 so we can increment before adding elements ot the stack

    s.top=-1;

    push (&s , 4);
    push (&s , 0);
    push (&s , 2);
    push (&s , 3);
    push (&s , 5);


    for (int i=0 ; i<3 ; i++)
    {
        printf("%i\n",pop( &s));
    }

    return 0;
}


//define the push()

void push ( stack * s , int num)
{
    //if the top is the element of the array then return the stack is full and we can't add another element
    if (s->top == CAPACITY - 1 )
    {
        return;
    }
    //++s->top just means to increment the top value before adding

    s->stack_array[++s->top]=num;

}

//define the pop() function  it return the value that was popped and accepts the pointer to the stack data structure as an argument

int pop(stack * s )
{
    if (s->top == -1)
    {
        return 010;
    }
    int poped ;
    poped = s->stack_array[s->top--];

    return poped;
}
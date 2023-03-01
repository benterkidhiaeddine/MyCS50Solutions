#include <stdlib.h>
#include <stdio.h>
//to define a node for a double linked list we need to add to the structure defintion another pointer to a node and we call one of the two left meaning it points to precedent node and right to the next node

typedef struct dllist
{
    int number;
    struct dllist * left ;
    struct dllist * right;

}dllnode;

dllnode * insert ( dllnode* head , int num);
dllnode* delete (dllnode* head  ,int target);
void destroy( dllnode* head);



int main(void)
{

    // create the head node for the new dllist

    dllnode * dllist =NULL;

    dllnode* n = malloc (sizeof( dllnode));

    if( n== NULL)
    {
        return 1;
    }

    n->left = NULL;
    n->right = NULL;
    n->number = 1 ;

    dllist = n ;


    dllist =insert (dllist , 2);
    dllist =insert (dllist , 4);
    dllist =insert (dllist , 7);


    for(dllnode* tmp = dllist ; tmp!=NULL;tmp=tmp->right )
    {
        printf("%i\n",tmp->number);

    }

    dllist=delete(dllist , 7);

    // test after the deletion
    for(dllnode* tmp = dllist ; tmp!=NULL;tmp=tmp->right )
    {
        printf("%i\n",tmp->number);

    }











}

//A function to insert a new node in a doubly linked list

dllnode * insert ( dllnode* head , int num)
{
    //first we allocate the necessary memory for the new node
    dllnode* new = malloc(sizeof(dllnode));
    if (new!= NULL)
    {
        new->number =num;
        new ->right = head ;
        head->left = new;
        head = new ;
    }
    return head;




}

//a function that deletes a single node in a doubly linked list

dllnode*  delete (dllnode* head  ,int target)


{
    for(dllnode* tmp = head ; tmp!=NULL;tmp=tmp->right)
    {
        if(tmp ->number == target )
        {
            //we need to stitch the precedent node  to the right node  first head->left->right = head->right
            /*                                                                head->right->left = head->left
            free(head)*/
            if (tmp->number == head->number)
            {
                head = tmp->right;
                free (tmp );
                return head;

            }

             //change left only the node to be deleted isn't the first node
            if (tmp ->left != NULL )
            {
                 tmp->left->right = tmp-> right;
            }

            //change righ only the node to be deleted isn't the last node
            if(tmp->right !=NULL)
            {
                 tmp->right->left = tmp->left;

            }


         free( tmp);
         return head;

            }



        }
        return head;

    }


void destroy( dllnode* head)
{
    if (head==NULL)
    {
        return;
    }
    destroy (head->right);
    free (head);

}
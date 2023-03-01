#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//define the node of a tree
typedef struct node
{
    //number of the node
    int number;
    //pointer to the node left of this node
    struct node * left;
    //pointer to the node right to this node
    struct node * right;
}node;

void free_tree(node* root);
void print_tree(node* root);
bool search_num (node * root , int target);

int main (void)
{


    //declaring the first pointer to the tree data structure and we set it pointing to NULL

    node * tree = NULL;

    //we set a temporary pointer to a node n and malloc to it the necessary memory

    node * n =malloc (sizeof(node));

    //safety check exist the programme if it dosent exist sufficent memory for the node
    if(n == NULL)
    {
        return 1;
    }

    //assign to n the number 4 as the first number in our tree  and the pointer left and right to NUll since we didn't add any more element to the tree yet

    n->number =4;
    n->left =NULL;
    n->right =NULL ;

    // now we sett tree equals to n equating tree is pointing to the first node in the tree

    tree = n;

    // now if we want to add another element to the left of the free node

    //we start by allocating the necessary memory to n the temporary node

    n = malloc(sizeof(node));

    //safety check as always
    if(n==NULL)

    {
        //in this case before we exist the programme we need to free any already allocated memory
        free(tree);
        return 2;
    }

    //now we allocate the number 3 and the left and right pointer of this node to NULL

    n->number= 3;
    n->left =NULL;
    n->right =NULL;


    //then we assign tree->left equak to n

    tree->left =n;

    // and the same if we add a node to the right of the root node

    n = malloc(sizeof(node));
    if(n==NULL)
    {
        free(tree);
        free(tree->left);
        return 3;
    }

    n->number = 5;
    n->left =NULL;
    n->right =NULL;

    tree->right = n ;


    print_tree(tree);
    printf(search_num (tree , 5)?"true" :"false");
    free_tree(tree);




return 0;





}


//now to automate the freeing process we make use of the fact that the tree datastructure is recursive in nauture

void free_tree(node* root)
{
    //if the root element is pointing to NULL there is nothing to free  so we just return
    if(root ==NULL)
    {
        return ;
    }

    //else we call the same free_tree fucntion on the left node of the root and the right node of the rooot then we free the root last (this is very important if dont free the root node and do it first we can't acess the child nodes)
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}


//using the same logic to automate the printing of the elemnts of the tree

void print_tree(node* root)
{
    if (root ==NULL)
        {
            return;
        }

    //the printing depends on the order we want if from smaller to bigger we print left root then right if the opposit we want from bigger to smaller we print right root then left

    print_tree(root->left);
    printf("%i\n",root->number);
    print_tree(root->right);
}



//try implementing a search algorithm for findning a number in a tree data structure

//the algorithm that i tried to implement on my own is correct but dosent make use of the fact that the elemnts in the tree are sorted  so it's not efficent

bool search_num (node * root , int target)


{
    if(root == NULL)
    {
        return false;
    }

    else if (  target < root->number )
    {
        return search_num (root->left,target) ;
    }

    else if ( target > root->number )
    {
        return search_num (root->right,target) ;
    }

    else
    {
        return true;
    }


}


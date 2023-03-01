//implemnting a trie data structure which is a tree whose nodes consist of an array of pointers to


//the try we are going to implement an  example of a trie consisting of a node containing a string and an array of pointers to other nodes of the same type
//the string denotes the name of a university and the sucession of the array index to follow to arrive at the final node containing the name of the university
//consists of the year it was founded on
typedef struct node

{
    char name_of_university [10] ;
    struct node * tries [number_of_letters];

}node;

int main(void )
{

node * trie_head=NULL.

node * n =malloc (sizeof (node));

if (n==NULL)
{
    return 1;
}

trie_head=n;

//never touche the head of the trie data structure use another pointer who points to the same data structure
node * traverse = head ;

traverse->tries[1]=malloc(sizeof(node));
if (traverse->tries[1]== NULL)

{
    free (trie_head);
    return 1;
}
traverse=traverse->tries[1];

traverse->tries [7]=malloc(sizeof(node));

if( traverse->tries [7]==NULL)
{
    free(trie_head->tries[1]);
    free(trie_head);
    return 2;
    
}



}
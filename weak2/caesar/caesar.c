#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*The formal definition of the cesar cipher is that for a given plain text P , the P(i)is the i(th)
letter in P ,a key K and C(i) the i(ith)letter in the cypher text C
we define the formula that give us C(i) as follows
C(i)=(P(i)+K)%26 */

/*the particular thing about this programme is that you will give the key K of the cypher as
a command line argument.
K must be >=0*/
char cipher(char c,int key);
bool only_nums(string input);

int main(int argc , string argv[])
{

    //Exception making sure there is only one command line argument inputed by the user
    //besides the name of the programm
    if (argc!=2)
    {
        printf("error pleas maximum of one key!\n");
        return 1;
    }

    //Exception making sure the command line argument is not less than 0
    if (argv <0)
    {
       printf("error pleas input a postive key\n");
       return 1;
    }

    //Exception making sure the command line argument dosent contain other charachters
    //besides numerals.
    if(!only_nums(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        int key=atoi(argv[1]);
        printf("plain text: ");
        string input=get_string("");
        printf("ciphertext: ");

        int len_input=strlen(input);
        for(int i=0;i<len_input;i++)
            {
                 printf("%c",cipher(input[i],key));
            }
        printf("\n");
        return 0;

    }

}

//Function that rotates the letter according to the caesar cipher

char cipher(char c,int key)
{
    if(islower(c))
    {
        return 'a'+(c-'a'+key)%26;
    }
    if(isupper(c))
    {
        return 'A'+(c-'A'+key)%26;
    }
    return c;
}

//Function that checks if a string has only numerals and returns true if that's the case
bool only_nums(string input)
{
    int len =strlen(input);
    for(int i=0;i<len;i++)
        {
            if(!isdigit(input[i]))
                {
                    return false;
                }
        }
    return true;
}





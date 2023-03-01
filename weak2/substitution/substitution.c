#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


bool only_letters(string input);
char replacer (char c,string key);
bool is_duplicate(string key1);

int main(int argc, string argv[])
{

    //Terminates the programme if the user dosent provide a key or provides too many keys
    if(argc!=2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //Terminates the programme if the user dosent give a valid key

    int argv_len=strlen(argv[1]);
    if(!only_letters(argv[1])||argv_len!=26||is_duplicate(argv[1]))
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    printf("plaintext: ");
    string input=get_string("");
    printf("ciphertext: ");
    int len_input=strlen(input);
    for(int i=0;i<len_input;i++)
    {
        if(isalpha(input[i]))
        {
            printf("%c",replacer(input[i],argv[1]));
        }
        else
        {
            printf("%c",input[i]);
        }
    }
    printf("\n");
    return 0 ;
}

//A function that checks that the string contains only letters
bool only_letters(string input)
{
    int len=strlen(input);
    for(int i=0;i<len;i++)
    {
        if(!isalpha(input[i]))
        {
            return false;
        }
    }
    return true;

}


//A function that replaces the letter with the corresponding letter according to the string key
char replacer (char c,string key)
{

    if(isupper(c))
    {
        int letter=c-65;
        c=key[letter];
        return toupper(c);
    }
    else
    {
        int letter=c-97;
        c=key[letter];
        return tolower(c);
    }

}

//A function that checks if the key have duplicate charachters
bool is_duplicate(string key1)
{
    int len=strlen(key1);
    for (int i =0;i<len;i++)
    {
        for(int j=i+1;j<len;j++)
        {

            if(tolower(key1[i])==tolower(key1[j]))
                {
                    return true;
                }
        }
    }
    return false;
}

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string input);
int count_words(string input);
int count_sentences(string input);
int index(int sentences,int words,int letters);

int main(void)
{
    printf("Text: ");
    string text=get_string("");
    int letters=count_letters(text);
    int words=count_words(text);
    int sentences=count_sentences(text);
    int index1=index(sentences,words,letters);

    if(index1<=16 && index1>=1)
    {
        printf("Grade %i\n",index1);
    }
    else if(index1 <1)
    {
        printf("Before Grade 1\n");
    }
    else if(index1>16)
    {
        printf("Grade 16+\n");
    }
}


//A function that counts letters contained in a given string
int count_letters(string input)
{
    int count =0;
    int len=strlen(input);
    for(int i=0;i<len;i++)
    {
        if(isalpha(input[i]))
        {
            count++;
        }
    }
    return count;
}


//A function that counts the numbers of words for a given string
int count_words(string input)
{
    int count=1;
    int len=strlen(input);
    for(int i=0;i<len;i++)
    {
        if(isblank(input[i]))
        {
            count+=1;
        }
    }
    return count;
}

//A function that counts the number of  sentances
int count_sentences(string input)
{
    int count=0;
    int len=strlen(input);
    for(int i=0;i<len;i++)
    {
        if(input[i]=='?'||input[i]=='!'||input[i]=='.')
        {
            count++;
        }
    }
    return count;
}

//calculates index = 0.0588 * L - 0.296 * S - 15.8
int index(int sentences,int words,int letters)
{
       return (int)round( (0.0588*(letters/(float)words)* 100)-(0.296*(sentences/(float)words)*100)-15.8);

}


















































































































































































































































































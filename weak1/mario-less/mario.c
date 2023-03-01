#include <cs50.h>
#include <stdio.h>


void white_space(int number_of_white);
void bricks(int number_of_bricks);

int main(void)

{
    int hight;
    do
    {
            hight = get_int("what is the hight of the pyramid?: ");
    }
    while (hight <1 || hight >8);

    int hight_h=hight;

    for (int i=0;i<hight;i++)
    {
     white_space(hight_h-1);
     hight_h--;
     bricks(i+1);
     white_space(2);
     bricks(i+1);
     printf("\n");
    }
}




























void white_space(int number_of_white)
{
    for(int k=0;k<number_of_white;k++)
    {
         printf(" ");
    }

}

void bricks(int number_of_bricks)
{
    for(int x=0;x<number_of_bricks;x++)
    {
        printf("#");
    }
}

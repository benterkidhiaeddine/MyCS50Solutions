#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    /*to convert an image to grayscale we need to set all the RGBTRIPLE values to the same one where this value is the average
    of the three original values
    1.itterate over all the the RGBTRIPLES
    2.compute for each RGBTRIPLES the average of all the values and set all the values to the new computed one*/
    for(int i =0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            /*we devide by 3.0 here so we dont lose too much informatin : the result will be a float*/
            float average=((image[i][j].rgbtBlue+image[i][j].rgbtRed+image[i][j].rgbtGreen)/3.0);
            int rounded=lround(average);
            image[i][j].rgbtBlue=rounded;
            image[i][j].rgbtRed=rounded;
            image[i][j].rgbtGreen=rounded;
        }
    }
    return;


}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
/*These are the formulae for obtaining the new RGBTRIPLE values
sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
  sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
  sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
  make sure to round to the nearst integer using lround
  and when the resulting value is greater then 255 cap it at 255*/
   for(int i =0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            /*first we create new variables to store the original values */
            int Original_blue=image[i][j].rgbtBlue;
            int Original_red=image[i][j].rgbtRed;
            int Original_green=image[i][j].rgbtGreen;
            /*second we calculate the new values and checking if they are greater than 255 if they are not
            assign them to the image 2D array as they are if not assign 255 insted*/
            int New_blue= lround(.272 * Original_red + .534 * Original_green + .131 * Original_blue);
            int New_red=lround(.393 * Original_red + .769 * Original_green + .189 * Original_blue);
            int New_Green=lround(.349 * Original_red + .686 * Original_green + .168 * Original_blue);

            if(New_blue>255)
            {
                image[i][j].rgbtBlue=255;
            }
            else
            {
                image[i][j].rgbtBlue=New_blue;
            }

            if(New_red>255)
            {
                image[i][j].rgbtRed=255;
            }
            else
            {
                image[i][j].rgbtRed=New_red;
            }

            if(New_Green>255)
            {
                image[i][j].rgbtGreen=255;
            }
            else
            {
                image[i][j].rgbtGreen=New_Green;
            }
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    /* to reflect an image horizontaly we go to each Row meaning for a fixed i and we swap the color
    values for each RGBTRiple color of the pixel j with pixel l-1-j until j reaches l/2-1
    to do this we need temporary place holder for the colors
    tmp_red tmb_blue tmb_green*/
    for(int i =0;i<height;i++)
    {
        for (int j=0;j<width/2;j++)
        {
            int tmp_red=image[i][width-1-j].rgbtRed;
            image[i][width-j-1].rgbtRed=image[i][j].rgbtRed;
            image[i][j].rgbtRed=tmp_red;

            int tmp_blue=image[i][width-1-j].rgbtBlue;
            image[i][width-j-1].rgbtBlue=image[i][j].rgbtBlue;
            image[i][j].rgbtBlue=tmp_blue;

            int tmp_green=image[i][width-1-j].rgbtGreen;
            image[i][width-j-1].rgbtGreen=image[i][j].rgbtGreen;
            image[i][j].rgbtGreen=tmp_green;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    /*To blur the image wee need to take the average of all the RGBTTRIPLE color values 1 pixel
    away from the given pixel and including its values in the calculation of the average
    1.for each ittiration of every pixel we create a for loop to itterate over all the values in the small square
    with hight from k_begin=i-1 to k_end=i+2 and width m_begin=j-1 to m_end=j+1 if k_begin <0  or k_end>height k_begin and k_end must become k_begin=0 to k_end=hight
    if m_begin<0 or m_end>width m_begin and m_end must become m_begin=0 and m_end=width*/
    int new_red [height][width];
    int new_blue [height][width];
    int new_green [height][width];

    for(int i =0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            //initialising the variable that keeps track of the hight of the new box

            int k_end=i+1>height-1?height-1:i+1;
            //initialising the variables that keep track of the width of the new box

            int m_end=j+1>width-1?width-1:j+1;

            //to calulcate the average of each color we need the sum of all the values of the surrounding color(sum_color-name) and the divider which the number of the boxes itterated over (counter)
            int sum_red=0;
            int sum_blue=0;
            int sum_green=0;
            int counter=0;

            for(int k_begin=i-1<=0?0:i-1;k_begin<=k_end;k_begin++)
            {
                for(int m_begin=j-1<=0?0:j-1;m_begin<=m_end;m_begin++)
                {
                    sum_red+=image[k_begin][m_begin].rgbtRed;
                    sum_blue+=image[k_begin][m_begin].rgbtBlue;
                    sum_green+=image[k_begin][m_begin].rgbtGreen;
                    counter++;

                }
            }
            //now we calulculate the average for each color
            int average_red=lround(sum_red/(float)counter);
            int average_blue=lround(sum_blue/(float)counter);
            int average_green=lround(sum_green/(float)counter);

            //assign the new values to a 2D temporarily and not directly into the image to not make the calculation faulty
            new_red[i][j]=average_red;
            new_blue[i][j]=average_blue;
            new_green[i][j]=average_green;
        }
    }
    //finally assign all the calculated values into our final image
    for (int i=0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            image[i][j].rgbtRed=new_red[i][j];
            image[i][j].rgbtBlue=new_blue[i][j];
            image[i][j].rgbtGreen=new_green[i][j];
        }
    }

    return;
}

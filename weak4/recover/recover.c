#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//define a Byte type to make going through the bytes stored in the file easier
typedef uint8_t Byte;
int BLOCK_SIZE=512;

int main(int argc, char *argv[])
{
    //accepts only one command line argument
    if (argc!=2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    //opens the file we want to work on
    FILE *file_input=fopen(argv[1],"r");

    //if the file can't be opend it returns an Error
    if(file_input == NULL)
    {
        printf("the forensic image couldn't be opened for reading");
        return 1;
    }

    //to keep track of how many file we have and the name of each one
    int file_number=0;

    //stirng of file name
    char* filename=malloc(8*sizeof(Byte));
    //if memory allocation fails
    if(filename ==NULL)
    {
        return 2;
    }

    //we need one array of bytes to use to check for the sequence that defines a JPEG file
    Byte check [512];
    //if memory allocation fails

    //target file
    FILE * newfile = NULL;

    //this loop is used to read all the avaible bytes from the file into our check buffer
    while(fread(check,1,BLOCK_SIZE,file_input)==BLOCK_SIZE)
    {
        //check if it a JPEG file
        if(check[0]==0xff && check[1]==0xd8 && check[2]==0xff && ((check[3] & 0xf0)==0xe0))
        {
                //close any already open file before opening a new one we use the >0 condition because the file is not open yet for the first one when count is 0 to avoid an error message of closing a file that is not open
                if (file_number==0 )
                {
                //create the file name
                sprintf(filename,"%03i.jpg",file_number);
                //open the new fille
                newfile=fopen(filename,"w");

                //write into the new file
                fwrite(check,1,BLOCK_SIZE,newfile);

                //keep track of the file number
                file_number++;
                }


                else if(file_number>0)
                {
                    //close the old file
                    fclose(newfile);

                    //create new file name
                    sprintf(filename,"%03i.jpg",file_number);

                    //open new file with new filename
                    newfile=fopen(filename,"w");
                    //write into the new file name
                    fwrite(check,1,BLOCK_SIZE,newfile);
                    file_number++;

                }

        }
        //check if the file is already open meaning the pointer does point to somthing and not the default NULL
        else if(newfile!= NULL)
        {

         fwrite(check,1,BLOCK_SIZE,newfile);
        }


    }
    //close all open files
    fclose(file_input);
    fclose(newfile);

    //free all allocated memory
    free(filename);
    return 0;


}




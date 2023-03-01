// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file

    /*declare the uint8_t array where we will be storing the header file*/

    uint8_t* header=malloc(HEADER_SIZE*(sizeof(uint8_t)));

    //we always make sure the pointer dosent point to a null value
    if(header!=NULL)
    {
        /*using the fread() to read the header bytes from the input file and puting them in
    our header array */
            fread(header,sizeof(uint8_t),HEADER_SIZE,input);
     /*using the fwrite() to coppy the contents of our header array to the output file */
            fwrite(header,sizeof(uint8_t),HEADER_SIZE,output);
    }
    // never forget the free the allocated memory space to avoid any memory leak
    free(header);

    // TODO: Read samples from input file and write updated data to output file

    /*first we need to create a variable to store the audio samples whose size is 2 bytes
    second we start reading from the 45th byte and assiging each time 2 bytes size of audio samples
    into our audio sample variable
   */
    //we set the file indicator to the 45th byte using the fseek(input,45,SEEK_SET) where SEEK_SET is the start of the file
    fseek(input,SEEK_SET,45);

    int16_t audio_sample;
    // the predicate inside the while loop is the fread fucntion itself it returns each time it sucssefuly reads
    //an audio sample from the file it returns 1 meaning it hasnt reached the end of file yet
    while(fread(&audio_sample,sizeof(int16_t),1,input))
    {
        //if the condidtion is satisfied as stated above we multiply the audio sample by a factor specified by the user
        audio_sample*=factor;
        //then we write the result into the output file
        fwrite(&audio_sample,sizeof(int16_t),1,output);
    }
    // Close files
    fclose(input);
    fclose(output);
}

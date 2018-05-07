#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: must enter image name\n");
        return 1;
    }

    //declare file to read
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");

    //if input does not exist, print error
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //set outptr to NULL -- space allocated and points to no chunk of memory
    FILE *outptr = NULL;

    //define jpg filename array with a length of 8 for filename and null char
    char filename[8];

    //counter for filename creation
    int counter = 0;

    //size of buffer per size of jpg
    BYTE buffer[512];

    //read into 512 bytes of data until end of inptr
    while (fread(&buffer, sizeof(buffer), 1, inptr) == 1)
    {
        //check if first 4 bytes correspond to jpg data
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            //use bitwise operator '&' because this byte can vary
            (buffer[3] & 0xf0) == 0xe0)

        {
            //if a jpg...
            //sprintf returns the total number of characters written to ptr
            //the 0 flag indicates leading zeroes, the 3 indicates their shall be at most 3 leading zeroes
            //and the i indicates it should format the variable as an int
            sprintf(filename, "%03i.jpg", counter);

            //open file to give write privelege
            outptr = fopen(filename, "w");

            //write to file
            fwrite(buffer, sizeof(buffer), 1, outptr);

            //increment counter int for int in filename
            counter++;
        }

        //if outptr contains a jpg
        else if (outptr != NULL)
        {
            //write bytes to jpg file
            fwrite(buffer, sizeof(buffer), 1, outptr);
        }
    }
}
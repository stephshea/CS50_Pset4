#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t  BYTE;

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
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //need?
    FILE *outptr = NULL;

    //define jpg filename array
    char filename[8];

    //counter for filename creation
    int counter = 0;

    BYTE buffer[512];

    // while(!EOF)
    // while (counter != 50)


    //read into 512 bytes of data
    while (fread(&buffer, sizeof(buffer), 1, inptr) == 1)
    {
        //check if first 4 bytes correspond to jpeg data
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            //use bitwise operator & because this byte can vary
            (buffer[3] & 0xf0) == 0xe0)

        {
            //if old file exists, close old file

            //save with file name, start at 000 and increment so need count, type jpg
            sprintf(filename, "%03i.jpg", counter);

            //open file to give write privelege
            // FILE *img = fopen(filename, "w");
            outptr = fopen(filename, "w");

            fwrite(buffer, sizeof(buffer), 1, outptr);
            counter++;

            //fwrite(pointer to struc that contains bytes reading from,
            //size,number, new image FILE *
            //check for EOF
        }

        else if (outptr != NULL)

        {
            fwrite(&buffer, sizeof(buffer), 1, outptr);
        }
    }
    //close raw file
    fclose(inptr);
    //close last jpg
    fclose(outptr);

    // success
    return 0;
}
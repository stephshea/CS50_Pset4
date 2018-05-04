#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: must enter image name\n");
        return 1;
    }

   char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //counter for filename creation
    int counter = 0;
    char *buffer[512];

//while !EOF

    //read into first 512 bytes of data
    fread (&buffer, sizeof(buffer), 1, infile);
    // fread (buffer, 1, 512, infile)

    //check if first 4 bytes correspond to jpeg data
    if (buffer[0] ==0xff &&
        buffer[1] == 0xd8 &&
        buffer[2] == 0xff &&
        //use bitwise operator & because this byte can vary
        (buffer[3] & 0xf0) == 0xe0)

        {

            //if old file exists, close old file

            //save with file name, start at 000 and increment so need count, type jpg
            sprintf(filename, "%03i.jpg", 2);

            //open file to give write privelege
            FILE *img = fopen(filename, "w");

            fwrite(buffer, sizeof(buffer),1 outptr)
            //fwrite(pointer to struc that contains bytes reading from,
            // size,number, new image FILE *
//check for EOF
        }
    else if
        {
           //not a jpg
           //start at the next 512 block to check for jpg
        }

        // fclose(file); new jpg

    // success
    return 0;
}
// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    //convert input to float
float n = (atof(argv[1]));

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose( inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
printf("float, %.2lf", n * 4);

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

long oldwidth = bi.biWidth;
printf("wid %f", oldwidth * 3.2);
long oldheight = bi.biHeight;
printf("h %f", oldheight * 3.2);
int oldpadding = (4 - (oldwidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // determine padding for scanlines in infile


bi.biWidth *= n;
printf("new w %d", bi.biWidth);
bi.biHeight *= n;
printf("new h %d", bi.biHeight);

float newpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;


bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + newpadding) * abs(bi.biHeight);

bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);



    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);



    // iterate over infile's scanlines
    for (int i = 0, biHeight = labs(oldheight); i < biHeight; i++)
    {
        for(float resizeh = 0; resizeh < n; resizeh++)
            {
             // iterate over pixels/columns in scanline
            for (int j = 0; j < oldwidth; j++)
                {


                // temporary storage
                RGBTRIPLE triple;

                //read RGB values of infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for(float resizew = 0; resizew < n; resizew++)
                    {

                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

                    }

                }
        //write to outfile's padding

        // skip over padding of infile, if any; outfile will have its own unrelated to infile padding
        // fseek(inptr, oldpadding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (float k = 0; k < newpadding; k++)
                {

                fputc(0x00, outptr);
                }

                if (resizeh < n-1)
                {
                    fseek(inptr, -(oldwidth * sizeof(RGBTRIPLE)), SEEK_CUR);
                }

        }
        fseek(inptr, oldpadding , SEEK_CUR);
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

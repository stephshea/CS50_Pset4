// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    //declare n and convert to int
    int n = (atoi(argv[1]));

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
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    printf("int, %d", n);

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

    //store infile's width and height
    long inwidth = bi.biWidth;
    printf("inwidth %li", inwidth);
    long inheight = bi.biHeight;
    printf("inheight %li", inheight);

    //store infile padding
    int inpadding = (4 - (inwidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //decalre out file width & height increase by n
    bi.biWidth *= n;
    bi.biHeight *= n;

    //formula to determine outfile padding
    int outpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    //create outfile header info
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + outpadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = labs(inheight); i < biHeight; i++)
    {
        //iterate over outfile's scanlines
        for (int resizeh = 0; resizeh < n; resizeh++)
        {
            // iterate over pixels/columns in scanline
            for (int j = 0; j < inwidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                //read RGB values from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                //iterate over outfile's pixels
                for (int resizew = 0; resizew < n; resizew++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

        // add padding to outfile
        for (int k = 0; k < outpadding  ; k++)
            {
                fputc(0x00, outptr);
            }

            if (resizeh < n - 1)
            {
                //go to beginning of next scanline
                fseek(inptr, -(inwidth * sizeof(RGBTRIPLE)), SEEK_CUR);
            }
        }
         // skip over padding of infile, if any; outfile will have its own unrelated to infile padding
        fseek(inptr, inpadding, SEEK_CUR);
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
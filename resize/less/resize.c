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
        fclose( inptr);
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

BITMAPFILEHEADER bfResize = bf;
BITMAPINFOHEADER biResize = bi;

biResize.biWidth *= n;
biResize.biHeight *= n;

int newpadding = (4 - (biResize.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

biResize.biSizeImage = ((sizeof(RGBTRIPLE) * biResize.biWidth) + newpadding) * abs(biResize.biHeight);
bfResize.bfSize = biResize.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfResize, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biResize, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for(int resizeh = 0;  biResize.biHeight = abs(biResize.biHeight); resizeh < n; resizeh++)
            {
        // iterate over pixels/columns in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {


            // temporary storage
            RGBTRIPLE triple;

            //read RGB values of infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
 for(int resizew = 0; resizew < n; resizew++)
                {

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

        }

        }
//write to outfile's padding

        // skip over padding of infile, if any; outfile will have its own unrelated to infile padding
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < newpadding; k++)
        {
            while(resizeh < n-1)
            {
            fputc(0x00, outptr);
        }
}
    }
}
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

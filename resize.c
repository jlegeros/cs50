// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // get factor
    int factor = atoi(argv[1]);

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

    int inputWidth = bi.biWidth;
    int inputHeight = bi.biHeight;
    bi.biWidth = inputWidth * factor;
    bi.biHeight = inputHeight * factor;

    // determine input file padding
    int inputPadding = (4 - (inputWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine output file padding
    int outputPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // Calculate new size of image
    bi.biSizeImage = ((bi.biWidth * 3) + outputPadding) * abs(bi.biHeight);

    // Calculate new bitmap file size (image plus headers)
    bf.bfSize = 54 + bi.biSizeImage;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(inputHeight); i < biHeight; i++)
    {
        RGBTRIPLE tripleArray[bi.biWidth];

        // iterate over pixels in the row
        for (int j = 0; j < inputWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            for (int widthFactor = 0; widthFactor < factor; widthFactor++) 
            {
                // write triple to the array...
                tripleArray[(j * factor) + widthFactor] = triple;
            }
        }
        for (int heightFactor = 0; heightFactor < factor; heightFactor++)
        {
            fwrite(&tripleArray, sizeof(RGBTRIPLE) * bi.biWidth, 1, outptr);
            for (int k = 0; k < outputPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }

        // skip over padding, if any
        fseek(inptr, inputPadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

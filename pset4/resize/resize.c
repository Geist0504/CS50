/**
 * Resizes a BMP piece by piece by a factor of N, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    //ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage ./resize scale infile outfile\n");
        return 1;
    }
    
    int scale = atoi(argv[1]);
    
    if (scale < 1 || scale >100)
    {
        fprintf(stderr, "Scale must be a positive integer bwtween 0 and 100\n");
        return 1;
    }
    
    //remember file names & scale
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
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
    
    //get useful original header constants
    int oriWidth = bi.biWidth;
    int oriHeight = bi.biHeight;
    
    // create outfile's HEADER & modify
    BITMAPFILEHEADER of;
    fread(&of, sizeof(BITMAPFILEHEADER), 1, outptr);
    BITMAPINFOHEADER oi;
    fread(&oi, sizeof(BITMAPINFOHEADER), 1, outptr);
    // need to change fields in these based on scale
    bi.biWidth *=scale;
    bi.biHeight *=scale;
    //fprintf(stderr, "%i\n", bi.biWidth);
    //fprintf(stderr, "%i\n", oriWidth);
    //what it this
    
    // determine padding for scanlines
    int paddingIn =  (4 - (oriWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingOut =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    //fprintf(stderr, "%i\n", paddingOut);
    //fprintf(stderr, "%i\n", paddingIn);
    
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + paddingOut) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + 54;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    

    
    //go through each input line
    for (int i = 0, biHeight = abs(oriHeight); i < biHeight; i++)
    {
        //do this n time for the output. This is verticle scale
        for (int m = 0; m < scale-1; m++)
        {
        // iterate over pixels in input scanline
        for (int j = 0; j < oriWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // write RGB triple to outfile scale times. This is Horizontal scale
            for (int k = 0; k < scale; k++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        //write padding
        for (int l = 0; l < paddingOut; l++)
        {
                fputc(0x00, outptr);
        }
        //move cursor back to original line in inptr to rescan
        fseek(inptr, -(long int)(sizeof(RGBTRIPLE)*oriWidth),SEEK_CUR);
        }
        //print previous line once more to close things off
        for (int j = 0; j < oriWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // write RGB triple to outfile scale times. This is Horizontal scale
            for (int k = 0; k < scale; k++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        for (int l = 0; l < paddingOut; l++)
        {
            fputc(0x00, outptr);
        }
        // skip over inptr padding, if any
        fseek(inptr, paddingIn, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);
    
    //success!
    return 0;
}
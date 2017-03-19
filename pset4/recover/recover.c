/**
 * Scans throguh memory card capturing Jpeg images.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main (int argc, char *argv[])
{
    //ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage ./recover infile\n");
        return 1;
    }
    
    //create type BYTE
    typedef uint8_t  BYTE;
    
    //remember file name and location
    char *infile = argv[1];
    
    //open the file
    FILE *inptr =  fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }
    
    //initialize constants
    BYTE buffer[512];
    bool state = true;
    int jCount = 0;
    char filename[8];
    FILE *img;
    
    //read through the entire file
    while(state == true)
    {
        //read a chunk & test for completeness (ie not the end of the file)
        if (fread(buffer, 512, 1, inptr) != 0)
        {
            
            //test for the begining of a JPEG
            if(buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
            {
                //test if first file
                if(jCount == 0)
                {
                    //Open first found JPEG
                    sprintf(filename, "%03i.jpg", jCount);
                    img = fopen(filename, "w");
                }
                else
                {
                    //close old file, create new one
                    fclose(img);
                    sprintf(filename, "%03i.jpg", jCount);
                    img = fopen(filename, "w");
                }
                //increment JPG file name number
                jCount++;
                //Write JPEG block to given file
                fwrite(buffer,512,1, img);
            }
            //have we already found a JPEG
            else if(jCount>0)
            {
                fwrite(buffer,512,1, img);
            }
            //there are no open files, and we didn't find the begining of a file
            else
            {
                continue;
            }
            
        }
        else
        {
            //close last jpeg and quit loop
            fclose(img);
            state = false;
        }
    }
    
    //close card
    fclose(inptr);
    
    //success
    return 0;
}
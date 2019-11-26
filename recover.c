#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;
//block of 512 bytes
typedef struct
{
    BYTE b1;
    BYTE b2;
    BYTE b3;
    BYTE b4;
    BYTE image[508];
}
BUFFER;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: recover filename\n");
        return 1;
    }

    // store filename to recover
    char *infile = argv[1];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }
    FILE *outptr = NULL;

    BUFFER buffer;
    int count = 0;
    int mask = 0xf0;

    while (fread(&buffer, sizeof(BUFFER), 1, inptr) == 1)
    {
        int extractedBits = mask & buffer.b4;

        // start of new JPG
        if (buffer.b1 == 0xff && buffer.b2 == 0xd8 && buffer.b3 == 0xff && extractedBits == 0xe0)
        {
            if (outptr != NULL)
            {
                // close output file, get ready to write to a new file.
                fclose(outptr);
            }
            // open output file labeled xxx.jpg where xxx is count
            char outputfilename[12];
            sprintf(outputfilename, "%03d.jpg", count);

            outptr = fopen(outputfilename, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", outputfilename);
                return 3;
            }
            count++;
        }

        // if output file is open, copy contents of buffer in to the file
        if (outptr != NULL)
        {
            fwrite(&buffer, sizeof(BUFFER), 1, outptr);
        }

        //printf("test? %hhu %hhu %hhu %hhu\n", buffer.b1, buffer.b2, buffer.b3, buffer.b4);
    }
    fclose(inptr);
    if (outptr != NULL)
    {
        fclose(outptr);
    }
    //printf("%d\n", count);

    return 0;
}

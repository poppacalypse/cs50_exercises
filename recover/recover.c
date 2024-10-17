#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open %s\n", argv[1]);
        return 1;
    }

    // Create a buffer for a block of data
    uint8_t buffer[512];
    // Initialise variables
    int jpeg_count = 0;
    FILE *outptr = NULL;
    char filename[8]; // 000.jpg\0
    bool first_jpeg = true;

    // Read 512 bytes into a buffer
    // While there's still data left to read from the memory card, repeat until end of card:
    while (fread(buffer, sizeof(uint8_t), 512, card) == 512)
    {
        // Create JPEGs from the data
        // If start of new JPEG (check if buffer starts with JPEG signature)
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // If first JPEG
            if (first_jpeg)
            {
                // Open new file for writing
                sprintf(filename, "%03i.jpg", jpeg_count);
                outptr = fopen(filename, "w");
                if (outptr == NULL)
                {
                    fclose(card);
                    printf("Could not create %s\n", filename);
                    return 1;
                }
                // Start writing JPEG data
                fwrite(buffer, sizeof(uint8_t), 512, outptr);
                first_jpeg = false;
                jpeg_count++;
            }
            // Else (not first JPEG)
            else
            {
                // Close previous file is one was open
                fclose(outptr);
                // Open new file for next JPEG
                sprintf(filename, "%03i.jpg", jpeg_count);
                outptr = fopen(filename, "w");
                if (outptr == NULL)
                {
                    fclose(card);
                    printf("Could not create %s\n", filename);
                    return 1;
                }
                // Start writing new JPEG data
                fwrite(buffer, sizeof(uint8_t), 512, outptr);
                jpeg_count++;
            }
        }
        // Else (not start of new JPEG)
        else
        {
            // If already found JPEG
            if (!first_jpeg)
            {
                // Continue writing to current JPEG file
                fwrite(buffer, sizeof(uint8_t), 512, outptr);
            }
        }
    }
    // Close any remaining files
    if (outptr != NULL)
    {
        fclose(outptr);
    }
    // Close input file (card)
    fclose(card);
    return 0;
}

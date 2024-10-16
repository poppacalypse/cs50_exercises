#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            float average = (
              image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed
            ) / 3.0;
            
            // Round to nearest integer
            int gray_value = round(average);

            // Update pixel values (set each colour value to the average value)
            image[i][j].rgbtBlue = gray_value;
            image[i][j].rgbtGreen = gray_value;
            image[i][j].rgbtRed = gray_value;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;

            // Round to nearest integer & update pixel with sepia values
            image[i][j].rgbtBlue = (round(sepiaBlue) > 255) ? 255 : round(sepiaBlue);
            image[i][j].rgbtGreen = (round(sepiaGreen) > 255) ? 255 : round(sepiaGreen);
            image[i][j].rgbtRed = (round(sepiaRed) > 255) ? 255 : round(sepiaRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temp copy of the image to store the blurred values
    RGBTRIPLE (*temp)[width] = malloc(height * width * sizeof(RGBTRIPLE));
    if (temp == NULL)
    {
        return;
    }

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialise variables to store colour sums and pixel counts (to calc avg)
            int sumBlue = 0, sumGreen = 0, sumRed = 0;
            int count = 0;

            // Loop over 3x3 box centred on current pixel
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <=1; dj++)
                {
                    // Calculate coordinates of neighbouring pixel
                    int ni = i + di;
                    int nj = j + dj;

                    // Check if neighbouring pixel is within image bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        // Add neighbour colour values to sums
                        sumBlue += image[ni][nj].rgbtBlue;
                        sumGreen += image[ni][nj].rgbtGreen;
                        sumRed += image[ni][nj].rgbtRed;

                        // Increment pixel count
                        count++;
                    }
                }
            }

            // Calculate average colour values + round to nearest integer
            temp[i][j].rgbtBlue = round((float)sumBlue / count);
            temp[i][j].rgbtGreen = round((float)sumGreen / count);
            temp[i][j].rgbtRed = round((float)sumRed / count);
        }
    }

    // Copy blurred image from temp array back to original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    // Free memory allocated for temp copy of image
    free(temp);
    return;
}

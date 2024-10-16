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
            // Take average of blue, green, and red
            float average =
                (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;

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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        // only need to swap the first half of the pixels with the second half, hence divide width by 2
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
    RGBTRIPLE(*temp)[width] = malloc(height * width * sizeof(RGBTRIPLE));
    if (temp == NULL)
    {
        return;
    }

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialise variables to store colour sums and pixel counts (to calculate average)
            int sumBlue = 0, sumGreen = 0, sumRed = 0;
            int count = 0;

            // Loop over 3x3 box centred on current pixel
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
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

            // Calc avg colour values + round to nearest integer
            temp[i][j].rgbtBlue = round((float)sumBlue / count);
            temp[i][j].rgbtGreen = round((float)sumGreen / count);
            temp[i][j].rgbtRed = round((float)sumRed / count);
        }
    }

    // Copy blurred image fro mtemp array back to origina liamge
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a temp copy of the image to store the edge values
    RGBTRIPLE(*temp)[width] = malloc(height * width * sizeof(RGBTRIPLE));
    if (temp == NULL)
    {
        return;
    }

    // Define Sobel operators for x and y directions
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int Gy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialise variables to store Sobel values
            double GxRed = 0, GxGreen = 0, GxBlue = 0;
            double GyRed = 0, GyGreen = 0, GyBlue = 0;

            // Loop over 3x3 box centred on current pixel
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj ++)
                {
                    // Calculate coordinates of neighbouring pixel
                    int ni = i + di;
                    int nj = j + dj;

                    // Check if neighbouring pixel is within image bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        // Add neighbour colour values to sums
                        GxRed += image[ni][nj].rgbtRed * Gx[di + 1][dj + 1];
                        GxGreen += image[ni][nj].rgbtGreen * Gx[di + 1][dj + 1];
                        GxBlue += image[ni][nj].rgbtBlue * Gx[di + 1][dj + 1];
                        GyRed += image[ni][nj].rgbtRed * Gy[di + 1][dj + 1];
                        GyGreen += image[ni][nj].rgbtGreen * Gy[di + 1][dj + 1];
                        GyBlue += image[ni][nj].rgbtBlue * Gy[di + 1][dj + 1];
                    }
                }
            }

            // Calculate final colour values
            double redEdge = sqrt(GxRed * GxRed + GyRed * GyRed);
            double greenEdge = sqrt(GxGreen * GxGreen + GyGreen * GyGreen);
            double blueEdge = sqrt(GxBlue * GxBlue + GyBlue * GyBlue);

            temp[i][j].rgbtRed = (round(redEdge) > 255) ? 255 : round(redEdge);
            temp[i][j].rgbtGreen = (round(greenEdge) > 255) ? 255 : round(greenEdge);
            temp[i][j].rgbtBlue = (round(blueEdge) > 255) ? 255 : round(blueEdge);
        }
    }

    // Copy edge-detected image from temp array back to original image
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

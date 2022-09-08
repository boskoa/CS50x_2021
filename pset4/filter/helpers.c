#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    int average;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            average = (int) ((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width]) {
    int rgbtB;
    int rgbtG;
    int rgbtR;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            rgbtB = (int) (0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);
            rgbtG = (int) (0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            rgbtR = (int) (0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);

            image[i][j].rgbtBlue = rgbtB > 255 ? 255 : rgbtB;
            image[i][j].rgbtGreen = rgbtG > 255 ? 255 : rgbtG;
            image[i][j].rgbtRed = rgbtR > 255 ? 255 : rgbtR;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE temp_img[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            temp_img[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][width - j] = temp_img[i][j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE temp_img[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            temp_img[i][j] = image[i][j];
        }
    }

    RGBTRIPLE b_average;
    int b_sum_b, b_sum_g, b_sum_r;
    float counter;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            b_sum_b = 0;
            b_sum_g = 0;
            b_sum_r = 0;
            counter = 0.0;
            int x, y;
            for (x = -1; x < 2; x++) {
                for (y = -1; y < 2; y++) {
                    if ((j + y < 0) || (i + x < 0) || (i + x > height - 1) || (j + y > width - 1)) {
                        continue;
                    }
                    else {
                        b_sum_b += temp_img[i + x][j + y].rgbtBlue;
                        b_sum_g += temp_img[i + x][j + y].rgbtGreen;
                        b_sum_r += temp_img[i + x][j + y].rgbtRed;
                        counter++;
                    }
                }
            }
            b_average.rgbtBlue = (int) (b_sum_b / counter);
            b_average.rgbtGreen = (int) (b_sum_g / counter);
            b_average.rgbtRed = (int) (b_sum_r / counter);
            image[i][j].rgbtBlue = b_average.rgbtBlue;
            image[i][j].rgbtGreen = b_average.rgbtGreen;
            image[i][j].rgbtRed = b_average.rgbtRed;
        }
    }

    return;
}

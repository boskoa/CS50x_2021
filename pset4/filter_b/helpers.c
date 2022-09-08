#include <math.h>

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width]) {
    RGBTRIPLE temp_img[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            temp_img[i][j] = image[i][j];
        }
    }

    RGBTRIPLE b_average;
    int x_sum_b, x_sum_g, x_sum_r, y_sum_b, y_sum_g, y_sum_r;
    float sum_b, sum_g, sum_r;
    int arr_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int arr_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            x_sum_b = 0;
            x_sum_g = 0;
            x_sum_r = 0;
            y_sum_b = 0;
            y_sum_g = 0;
            y_sum_r = 0;
            sum_b = 0.0;
            sum_g = 0.0;
            sum_r = 0.0;
            int x, y;
            for (x = -1; x < 2; x++) {
                for (y = -1; y < 2; y++) {
                    if ((j + y < 0) || (i + x < 0) || (i + x > height - 1) || (j + y > width - 1)) {
                        continue;
                    }
                    else {
                        x_sum_b += ((int) temp_img[i + x][j + y].rgbtBlue) * arr_x[x + 1][y + 1];
                        x_sum_g += ((int) temp_img[i + x][j + y].rgbtGreen) * arr_x[x + 1][y + 1];
                        x_sum_r += ((int) temp_img[i + x][j + y].rgbtRed) * arr_x[x + 1][y + 1];

                        y_sum_b += ((int) temp_img[i + x][j + y].rgbtBlue) * arr_y[x + 1][y + 1];
                        y_sum_g += ((int) temp_img[i + x][j + y].rgbtGreen) * arr_y[x + 1][y + 1];
                        y_sum_r += ((int) temp_img[i + x][j + y].rgbtRed) * arr_y[x + 1][y + 1];
                    }
                }
            }
            sum_b = sqrt(x_sum_b * x_sum_b + y_sum_b * y_sum_b);
            sum_g = sqrt(x_sum_g * x_sum_g + y_sum_g * y_sum_g);
            sum_r = sqrt(x_sum_r * x_sum_r + y_sum_r * y_sum_r);
            image[i][j].rgbtBlue = sum_b > 255 ? 255 : (int) (sum_b);
            image[i][j].rgbtGreen = sum_g > 255 ? 255 : (int) (sum_g);
            image[i][j].rgbtRed = sum_r > 255 ? 255 : (int) (sum_r);
        }
    }

    return;
}

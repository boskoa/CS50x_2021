#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int f_count = 0;
char f_name[8];
int img_arr[100] = {0};


int main(int argc, char *argv[]) {
    // Check for command line argument
    if (argc != 2) {
        printf("Incorrect usage. Enter: ./recover name-of-file\n");
        return 1;
    }

    // Open file for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("File couldn't be opened.");
        return 1;
    }

    // Get file size
    fseek(input, 0, SEEK_END);
    int file_size = ftell(input);
    fseek(input, 0, SEEK_SET);


    // Find headers and get their position
    BYTE *file_buffer = malloc(file_size);
    fread(file_buffer, file_size, 1, input);
    int head_counter = 0;
    for (int i = 0; i < file_size - 3; i++) {
        if ((file_buffer[i] == 0xff) && (file_buffer[i + 1] == 0xd8) && (file_buffer[i + 2] == 0xff) && ((file_buffer[i + 3] & 0xf0) == 0xe0)) {
            img_arr[head_counter] = i;
            head_counter++;
        }
    }
    free(file_buffer);

    // Iterate through headers array and save data to files
    int distance;
    fseek(input, img_arr[0], SEEK_SET);
    for (int p = 0; p < head_counter - 1; p++) {
        distance = img_arr[p + 1] - img_arr[p];
        BYTE *buffer = malloc(distance);
        sprintf(f_name, "%03d.jpg", f_count);
        FILE *output = fopen(f_name, "w");
        if (output == NULL) {
            printf("Couldn't open new file.\n");
            return 1;
        }
        f_count++;
        fread(buffer, 1, distance, input);
        fwrite(buffer, distance, 1, output);
        fclose(output);
        free(buffer);
    }

    // Get the last image
    BYTE *buffer = malloc(distance);
    sprintf(f_name, "%03d.jpg", f_count);
    FILE *output = fopen(f_name, "w");
    if (output == NULL) {
        printf("Couldn't open new file.\n");
        return 1;
    }
    fread(buffer, 1, file_size - img_arr[head_counter], input);
    fwrite(buffer, file_size - img_arr[head_counter], 1, output);
    fclose(output);
    free(buffer);
    fclose(input);
}
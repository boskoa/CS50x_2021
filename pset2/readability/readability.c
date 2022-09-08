#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void get_input(char text[]);
void counter(char text[], int *words, int *letters, int *sentences);
float index(int letters, int words, int sentences);

int main(void){
    // Variables for storing text, word, letter and sentence count.
    char text[1000];
    int words = 0;
    int letters = 0;
    int sentences = 0;
    int grade;

    // Get user input.
    printf("Text:\n");
    get_input(text);

    // Count letters, words and sentences.
    counter(text, &words, &letters, &sentences);

    // Evaluate grade.
    grade = index(letters, words, sentences);
    if (grade < 1) {
        printf("Before Grade 1\n");
    }
    else if (grade > 16) {
        printf("Grade 16+\n");
    }
    else {
        printf("Grade %i\n", grade);
    }

    return 0;
}

// Store user input.
void get_input(char text[]) {
    scanf("%[^\n]s", text);
}

// Counter function.
void counter(char text[], int *words, int *letters, int *sentences) {
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            *letters += 1;
        }
        else if (text[i] == ' ') {
            *words += 1;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            *sentences += 1;
        }
    }
    *words += 1;
}

// Define index.
float index(int letters, int words, int sentences) {
    float i = 0.0588 * (100 / (float)words) * letters - 0.296 * (100 / (float)words) * sentences - 15.8;
    return round(i);
}
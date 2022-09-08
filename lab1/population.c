#include <stdio.h>

int start();
int end();
int years(int start, int end, int year);

int main(void) {
    int start_m = 0;
    int end_m = 0;
    int year_m = 0;

    // Ask until starting population is not less than 9.
    while (start_m < 9) {
        start_m = start();
    }

    // Ask until target population is greater than starting population.
    while (!(end_m > start_m)) {
        end_m = end();
    }

    int answer = years(start_m, end_m, year_m);

    printf("Number of years required for the llama population to grow from %i individuals to %i individuals is: %i.\n", start_m, end_m, answer);

    return 0;
}

// Get the starting population from the user.
int start() {
    int pop_s;
    printf("Enter the starting population size: \n");
    scanf("%i", &pop_s);
    return pop_s;
}

// Get the target population from the user.
int end() {
    int pop_e;
    printf("Enter the ending population size: \n");
    scanf("%i", &pop_e);
    return pop_e;
}

// Calculate the necessary number of years. Recursively.
int years(int start, int end, int year) {
    int final_year = year + 1;
    int pop = start / 3 - start / 4;
    start += pop;

    if (start >= end) {
        return final_year;
    }
    else {
        return years(start, end, final_year);
    }
}
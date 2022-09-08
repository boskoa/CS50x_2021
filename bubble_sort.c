#include <stdio.h>

void input();
void output();

int arr[100];
int length;

int main(void) {

    input();
    output();

    // Print the sorted sequence.
    printf("Sorted: ");
    for (int j = 0; j < length; j++) {
        printf("%i\t", arr[j]);
    }
    printf("\n");

    return 0;
}

// Get a sequence.
void input() {
    printf("Enter the length of a sequence:\n");
    scanf("%i", &length);
    printf("Insert a sequence of numbers to be sorted:\n");
    for (int i = 0; i < length; i++) {
        scanf("%i", &arr[i]);
    }
}

// Sort the sequence
void output() {
    int higher;
    for (int y = length - 1; y > -1; y--) {
        for (int ind = 0; ind < y; ind++) {
            if (arr[ind] > arr[ind + 1]) {
                higher = arr[ind];
                arr[ind] = arr[ind + 1];
                arr[ind + 1] = higher;
            }
        }
    }
}
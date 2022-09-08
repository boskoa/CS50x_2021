#include <stdio.h>

void input();
void output();

int arr[100];
int length;

int main(void) {

    input();
    output();

    // Print result
    printf("Sorted: ");
    for (int i = 0; i < length; i++) {
        printf("%d\t", arr[i]);
    }
    printf("\n");

    return 0;
}

// Get an array
void input() {
    printf("Enter the length of a sequence:\n");
    scanf("%i", &length);
    printf("Insert a sequence of numbers to be sorted:\n");
    for (int i = 0; i < length; i++) {
        scanf("%i", &arr[i]);
    }
}

// Sort an array
void output() {
    int low;
    int low_num;
    for (int i = 0; i < length; i++) {
        low = i;
        for (int y = i; y < length - 1; y++) {
            if (arr[y + 1] < arr[low]) {
                low = y + 1;
            }
        }
        low_num = arr[low];
        arr[low] = arr[i];
        arr[i] = low_num;
    }
}
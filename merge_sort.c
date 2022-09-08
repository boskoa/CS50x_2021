#include <stdio.h>

void sort(int sa[], int sarr_l[], int sarr_r[], int sl);
void divide(int a[], int l);
void input();

int arr[100];
int length;
int div_point;

int main(void) {

    // Run functions
    input();
    divide(arr, length);

    // Print result
    printf("Sorted: ");
    for (int z = 0; z < length; z++) {
        printf("%i\t", arr[z]);
    }
    printf("\n");

    return 0;
}

// Divide (recursively) until 1 element in array.
// Then, call sort function to sort and merge halves.
void divide(int a[], int l) {
    int len_l = l / 2;
    int len_r = l - len_l;
    int arr_l[len_l];
    int arr_r[len_r];
    for (int j = 0; j < len_l; j++) {
        arr_l[j] = a[j];
    }
    for (int k = 0; k < len_r; k++) {
        arr_r[k] = a[len_l + k];
    }

    if (len_l > 1) {
        divide(arr_l, len_l);
    }
    if (len_r > 1) {
        divide(arr_r, len_r);
    }

    sort(a, arr_l, arr_r, l);


}

// Get a sequence
void input() {
    printf("Enter the length of the sequence: ");
    scanf("%i", &length);
    printf("Enter the numbers:\n");
    for (int n = 0; n < length; n++) {
        scanf("%i", &arr[n]);
    }
}

// Sort and merge two halves of the given array.
void sort(int sa[], int sarr_l[], int sarr_r[], int sl) {

    int l = 0;
    int r = 0;
    int m = 0;
    for (int i = 0; (l < (sl / 2)) && (r < (sl - sl / 2)); i++) {
        if (sarr_l[l] > sarr_r[r]) {
            sa[i] = sarr_r[r];
            r++;
            m++;
        }
        else {
            sa[i] = sarr_l[l];
            l++;
            m++;
        }
    }

    // Add remaining elements to the array.
    while (l < (sl / 2)) {
        sa[m] = sarr_l[l];
        l++;
        m++;
    }
    while (r < (sl - sl / 2)) {
        sa[m] = sarr_r[r];
        r++;
        m++;
    }
}
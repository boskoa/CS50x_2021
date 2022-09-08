#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void input(char plain[]);
void output(char plain_text[], char cipher_text[], int key);

int main(int argc, char *argv[]) {

    // Check if valid command line argument (count).
    if ((argc != 2) || (!(atoi(argv[1])))) {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Variables to store text.
    char plaintext[500];
    char ciphertext[500];
    // Variable to store cipher.
    int cipher = atoi(argv[1]);

    input(plaintext);

    output(plaintext, ciphertext, cipher);

    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

// Get text and store it.
void input(char plain_text[]) {
    printf("plaintext: ");
    scanf("%s", plain_text);
}

// Encrypt the text.
void output(char plain_text[], char cipher_text[], int key) {
    for (int i = 0; i < strlen(plain_text); i++) {
        int rest = key % 26;
        if (isalpha(plain_text[i])) {
            if ((int) plain_text[i] > 96) {
                if ((rest + (int) plain_text[i]) > 122) {
                    cipher_text[i] = (char) (96 + rest + (int) plain_text[i] - 122);
                }
                else {
                    cipher_text[i] = (char) ((int) plain_text[i] + rest);
                }
            }
            else {
                if ((rest + (int) plain_text[i]) > 90) {
                    cipher_text[i] = (char) (64 + rest + (int) plain_text[i] - 90);
                }
                else {
                    cipher_text[i] = (char) ((int) plain_text[i] + rest);
                }
            }
        }
        else {
            cipher_text[i] = plain_text[i];
        }
    }
}
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void input(char *plaintext);
void encrypt(char *plaintext, char *ciphertext, int *cipher);

int main(int argc, char *argv[]) {

    // Check command line argument.
    if (argc != 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26) {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // Variables to store text and cipher.
    char plaintext[500];
    char ciphertext[500];
    int cipher[26];
    for (int i = 0; i < 26; i++) {
        if (argv[1][i] > 96) {
            cipher[i] = argv[1][i] - 97;
        }
        else {
            cipher[i] = argv[1][i] - 65;
        }
    }

    // Store input
    input(plaintext);

    // Run encryption
    encrypt(plaintext, ciphertext, cipher);

    // Print encrypted text
    printf("ciphertext: %s\n", ciphertext);

    return 0;
}

// Get user input and store it in main variable.
void input(char *plaintext) {
    printf("plaintext: ");
    scanf("%[^\n]s", plaintext);
}

// Encrypt text function.
void encrypt(char *plaintext, char *ciphertext, int *cipher) {
    for (int i = 0; i < strlen(plaintext); i++) {
        if (isalpha(plaintext[i])) {
            if (plaintext[i] > 96) {
                ciphertext[i] = cipher[plaintext[i] - 97] + 97;
            }
            else {
                ciphertext[i] = cipher[plaintext[i] - 65] + 65;
            }
        }
        else {
            ciphertext[i] = plaintext[i];
        }
    }
}
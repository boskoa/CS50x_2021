// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 18000;

// Hash table
node *table[N];

int word_count = 0;

// Exponentiation function.
unsigned int expon(int a, int b) {
    unsigned int result = 1;
    for (int x = 0; x < b; x++) {
        result *= a;
    }

    return result;
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *trv = table[hash(word)];
    char tmp_word[strlen(word) + 1];
    for (int i = 0; i < strlen(word); i++) {
        tmp_word[i] = tolower(word[i]);
    }
    tmp_word[strlen(word)] = '\0';
    while (trv != NULL) {
        if (strcmp(trv->word, tmp_word) == 0) {
            return true;
        }
        else {
            trv = trv->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    unsigned int hash_v = 0;
    for (int i = 0; (i < strlen(word)) && (i < 3); i++) {
        if (isalpha(word[i])) {
            hash_v += expon(tolower(word[i]) - 96, i + 1);
        }
    }

    return hash_v;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL) {
        return false;
    }
    char word_buffer[LENGTH + 1];
    while (fscanf(dict, "%s", word_buffer) != EOF) {
        node *w = malloc(sizeof(node));
        if (w == NULL) {
            fclose(dict);
            return false;
        }
        strcpy(w->word, word_buffer);
        w->next = table[hash(word_buffer)];
        table[hash(word_buffer)] = w;
        word_count++;
    }
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for ( int i = 0; i < N; i++) {
        node *trv = table[i];
        while (trv) {
            node *tmp = trv;
            trv = trv->next;
            free(tmp);
        }

        if ((i == N - 1) && (trv == NULL)) {
            return true;
        }
    }
    return false;
}

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

// Node struct for every letter in a word.
typedef struct node {
    struct node *desc[26];
    bool exists;
} node;

node *create_node(void);
void insert(node *dict, char *word);
bool check_word(node *dict, char *word);

int main(void) {
    node *dict = create_node();
    insert(dict, "joy");
    insert(dict, "joyful");
    check_word(dict, "joy");
    check_word(dict, "proba");
    check_word(dict, "joyful");
    check_word(dict, "jo");

    return 1;
}

// Create a node.
node *create_node(void) {
    node *new_node = malloc(sizeof(node));

    for (int i = 0; i < 26; i++) {
        new_node->desc[i] = NULL;
    }
    new_node->exists = false;
    return new_node;
}

// Insert new word in a trie.
void insert(node *dict, char *word) {
    if (!(check_word(dict, word))) {
        printf("Inserting new word...\n");
        node *tmp = dict;
        for (int i = 0; i < strlen(word); i++) {
            if (!(tmp->desc[word[i] - 97])) {
                tmp->desc[word[i] - 97] = create_node();
            }
            tmp = tmp->desc[word[i] - 97];
        }
        tmp->exists = true;
    }
}

// Check if word is in a trie.
bool check_word(node *dict, char *word) {
    if (dict == NULL) {
        printf("Trie is empty.\n");
        return false;
    }

    node *tmp = dict;
    for (int i = 0; i < strlen(word); i++) {
        if (tmp->desc[word[i] - 97]) {
            tmp = tmp->desc[word[i] - 97];
        }
        else {
            printf("The word %s is not in this trie.\n", word);
            return false;
        }

        if (i == strlen(word) - 1) {
            if (tmp->exists) {
                printf("The word %s is in this trie.\n", word);
                return true;
            }
            else {
                printf("The word %s is not in this trie.\n", word);
                return false;
            }
        }
    }
    return true;
}
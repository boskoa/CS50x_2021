#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node {
    struct node *child_nodes[26];
    bool exists;
} node;

node *create_node();
bool insert(node **root, char *word);
void find_word(node *root, char *word);

int main() {
    node *dict = create_node();
    insert(&dict, "proba");
    find_word(dict, "proba");

    return 0;
}

node *create_node() {
    node *new_node = malloc(sizeof(node));

    for (int i = 0; i < 26; i++) {
        new_node->child_nodes[i] = NULL;
    }
    new_node->exists = false;
    return new_node;
}

bool insert(node **root, char *word) {
    if (*root == NULL) {
        *root = create_node();
    }

    node *tmp = *root;
    int length = strlen(word);

    for (int i = 0; i < length; i++) {
        if (tmp->child_nodes[i] == NULL) {
            tmp->child_nodes[word[i] - 97] = create_node();
        }
        tmp = tmp->child_nodes[word[i] - 97];
    }

    // Check if word already exists.
    if (tmp->exists) {
        return false;
    }
    else {
        tmp->exists = true;
        return true;
    }
}

void find_word(node *root, char *word) {
    if (root == NULL) {
        printf("Trie is empty.\n");
        return;
    }

    node *tmp = root;
    for (int i = 0; i < strlen(word); i++) {
        if (tmp->child_nodes[word[i] - 97]) {
            tmp = tmp->child_nodes[word[i] - 97];
        }
        else {
            printf("The word %s is not in the trie.\n", word);
            return;
        }
        if (i == strlen(word) - 1) {
            if (tmp->exists) {
                printf("The word %s is in the trie.\n", word);
            }
        }
    }
}
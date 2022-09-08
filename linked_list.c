#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct numb {
    int number;
    struct numb *next;
} numb;

numb *num_list = NULL;

int create_list(int n);
void print_list(numb *list);
void free_list(numb *list);
void insert(int num);
bool find(int num);
void del_num(int num);

int main(void) {
    create_list(10);
    insert(12);
    find(15);
    del_num(7);
    print_list(num_list);
    free_list(num_list);
}

// Create linked list of n numbers.
int create_list(int n) {
    for (int i = n; i > 0; i--) {
        numb *iter = malloc(sizeof(numb));
        if (iter == NULL) {
            free(iter);
            return 1;
        }
        iter->number = i;
        iter->next = num_list;
        num_list = iter;
    }
    return 0;
}

// Print linked list's elements.
void print_list(numb *list) {
    for (numb *tmp = list; tmp->next != NULL; tmp = tmp->next) {
        printf("%i\n", tmp->number);
    }
}

// Free memory
void free_list(numb *list) {
    if (list->next != NULL) {
        free_list(list->next);
    }
    free(list);
}

// Insert new elements
void insert(int num) {
    numb *new_number = malloc(sizeof(numb));
    new_number->number = num;
    new_number->next = num_list;
    num_list = new_number;
}

// Check if element is in a list
bool find(int num) {
    for (numb *tmp = num_list; tmp->next != NULL; tmp = tmp->next) {
        if (tmp->number == num) {
            printf("%i is in the list.\n", num);
            return true;
        }
    }
    printf("%i is not in the list.\n", num);
    return false;
}

// Delete an element
void del_num(int num) {
    numb *del = malloc(sizeof(numb));
    numb *cont = malloc(sizeof(numb));
    for (numb *tmp = num_list; tmp->next != NULL; tmp = tmp->next) {
        if (tmp->next->number == num) {
            del = tmp->next;
            cont = tmp->next->next;
            tmp->next = cont;
            free(del);
            printf("%i found and deleted from the list.\n", num);
            return;
        }
    }
    printf("%i is not in the list.\n", num);
}
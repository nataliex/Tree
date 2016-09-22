#define _CRT_SECURE_NO_WARNINGS 1 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 

typedef struct node 
{ 
    char *data; 
    struct node *left, *right; 
}node; 

void add_to_tree(node **tree, char *word) 
{ 
    printf("%p ", tree); 
    if (*tree == NULL) 
    { 
        *tree = (node*)malloc(sizeof(node)); 
        node* t = *tree; 
        t->data = word; 
        t->left = NULL; 
        t->right = NULL;
        free(word); 
        return; 
    } 
    node* t = *tree; 
    if (strcmp(word, t->data) < 0) 
        add_to_tree(&t->left, word); 
    else 
        add_to_tree(&t->right, word); 
} 

node* create_new_tree(char *word) 
{ 
    node *tree = (node*)malloc(sizeof(node)); 
    tree->data = word; 
    tree->left = NULL; 
    tree->right = NULL; 
    printf("%p ", tree);
    free(word); 
    return tree; 
} 

void going_tree(node* tree, FILE *file2) 
{ 
    if (!tree) 
    { 
        return; 
    } 
    going_tree(tree->right, file2); 
    fprintf(file2, "%s ", tree->data); 
    going_tree(tree->left, file2); 
} 

void free_tree(node *tree) 
{ 
    if (!tree) 
    { 
        return; 
    } 
    free_tree(tree->right); 
    free_tree(tree->left); 
    if (tree->right) 
    { 
        free(tree->right); 
    } 
    if (tree->left) 
    { 
        free(tree->left); 
    } 
    free(tree->data); 
} 

int main(int argc, char *argv[]) 
{ 
    char *wrd = NULL; 
    char ch = 0; 
    node *tree = NULL; 
    int i = 0, j = 0; 
    if (argc != 3) 
    { 
        printf("Wrong data\n"); 
        return 0; 
    } 
    FILE *file1 = fopen(argv[1], "r"); 
    if (file1 == NULL) 
    { 
        printf("Error of opening file\n"); 
        return 0; 
    } 
    do 
    { 
        do 
        { 
            ch = getc(file1); 
        } 
        while (isspace(ch) || ispunct(ch)); 
        wrd = (char*)malloc(100); 
        wrd[0] = '\0'; 
        for (i = 0; (ch != EOF) && !isspace(ch) && !ispunct(ch); i++) 
        { 
            wrd[i] = ch; 
            wrd[i + 1] = '\0'; 
            ch = getc(file1); 
        } 
        printf(wrd); 
        if (j > 0) 
        { 
            add_to_tree(&tree, wrd); 
        } 
        else 
        { 
            tree = create_new_tree(wrd); 
        } 
        j = 1; 
    } 
    while (ch != EOF); 
    fclose(file1); 
    FILE *file2 = fopen(argv[2], "w"); 
    if (file2 == NULL) 
    { 
        printf("Error of opening file\n"); 
        return 0; 
    } 
    going_tree(tree, file2); 
    free_tree(tree); 
    free(tree); 
    fclose(file2); 
    return 0; 
}

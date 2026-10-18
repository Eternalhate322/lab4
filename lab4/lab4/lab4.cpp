#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Добавление числа в дерево
struct Node* add(struct Node* root, int value) {
    if (root == NULL) {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

        if (newNode == NULL) {
            printf("Ошибка выделения памяти!\n");
            exit(1);
        }

        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;

        return newNode;
    }

    if (value < root->data) {
        root->left = add(root->left, value);
    }
    else {

        root->right = add(root->right, value);
    }

    return root;
}

// Поиск числа в дереве
int search(struct Node* root, int value) {
    if (root == NULL)
        return 0;

    if (root->data == value)
        return 1;

    if (value < root->data)
        return search(root->left, value);

    return search(root->right, value);
}

// Подсчёт вхождений числа
int count(struct Node* root, int value)
{
    if (root == NULL)
        return 0;

    int result = 0;

    if (root->data == value)
        result = 1;

    return result
        + count(root->left, value)
        + count(root->right, value);
}

void printTree(struct Node* root, int level) {
    if (root == NULL)
        return;

    printTree(root->right, level + 1);

    for (int i = 0; i < level; i++)
        printf("    ");

    printf("%d (ур. %d)\n", root->data, level);

    printTree(root->left, level + 1);
}

// Освобождение памяти
void freeTree(struct Node* root) {
    if (root == NULL)
        return;

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    setlocale(LC_ALL, "");

    struct Node* root = NULL;
    int value;

    printf("Введите числа для дерева (-1 для завершения):\n");

    while (1) {
        scanf("%d", &value);

        if (value == -1)
            break;

        root = add(root, value);
    }

    printf("\nДерево:\n");
    printTree(root, 0);

    printf("\nВведите число для поиска: ");
    scanf("%d", &value);

    if (search(root, value))
        printf("Число найдено.\n");
    else
        printf("Число не найдено.\n");

    printf("Количество вхождений: %d\n",
        count(root, value));

    freeTree(root);

    return 0;
}
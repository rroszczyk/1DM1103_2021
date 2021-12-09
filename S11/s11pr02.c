//
// Created by Radosław Roszczyk on 08.12.2021.
//
#include <stdio.h>
#include <stdlib.h>

// element listy
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// wyznacza element dzielący listę na dwa równe fragmenty i tnie ją na dwa
struct Node *split(struct Node *head)
{
    struct Node *fast = head;
    struct Node *slow = head;

    while (fast->next && fast->next->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    struct Node *temp = slow->next;
    slow->next = NULL;
    //temp->prev = NULL;
    return temp;
}

// łączy dwie listy w jedną całość zwracając uwagę na kolejność elementów
struct Node *merge(struct Node *first, struct Node *second)
{
    if (!first) {
        return second;
    }

    if (!second) {
        return first;
    }

    if (first->data < second->data)
    {
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = NULL;
        return first;
    }
    else
    {
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = NULL;
        return second;
    }
}

// sortuje listę używając algorymu merge sort
struct Node *mergeSort(struct Node *head)
{
    if (!head || !head->next) {
        return head;
    }
    struct Node *second = split(head);

    head = mergeSort(head);
    second = mergeSort(second);

    return merge(head, second);
}

// dodaje element na początku listy
void push(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->data = new_data;
    new_node->next = (*head_ref);
    new_node->prev = NULL;

    if ((*head_ref) != NULL) {
        (*head_ref)->prev = new_node;
    }

    (*head_ref) = new_node;
}

// dodaje element za wskazanym
void insertAfter(struct Node* prev_node, int new_data)
{
    if (prev_node == NULL) {
        printf("element poprzedzający musi istnieć");
        return;
    }

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    new_node->data = new_data;
    new_node->next = prev_node->next;
    prev_node->next = new_node;
    new_node->prev = prev_node;
    if (new_node->next != NULL) {
        new_node->next->prev = new_node;
    }
}

// dodaje element na końcu listy
void append(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));

    struct Node* last = *head_ref;

    new_node->data = new_data;
    new_node->next = NULL;

    if (*head_ref == NULL) {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = new_node;
    new_node->prev = last;
}

// wypisuje wszystkie elementy listy od początku oraz od końca
void printList(struct Node* node)
{
    struct Node* last;
    printf("\nOd początku \n");
    while (node != NULL) {
        printf(" %d ", node->data);
        last = node;
        node = node->next;
    }

    printf("\nOd końca \n");
    while (last != NULL) {
        printf(" %d ", last->data);
        last = last->prev;
    }
    printf("\n");
}

// usuwa wskazany element listy
void deleteNode(struct Node** head_ref, struct Node* del)
{
    if (*head_ref == NULL || del == NULL) {
        return;
    }

    if (*head_ref == del) {
        *head_ref = del->next;
    }

    if (del->next != NULL) {
        del->next->prev = del->prev;
    }

    if (del->prev != NULL) {
        del->prev->next = del->next;
    }

    free(del);
}


// usuwa element o wskazanym indeksie
void deleteNodeAtGivenPos(struct Node** head_ref, int n)
{
    if (*head_ref == NULL || n <= 0) {
        return;
    }

    struct Node* current = *head_ref;

    for (int i = 1; current != NULL && i < n; i++) {
        current = current->next;
    }

    if (current == NULL) {
        return;
    }

    deleteNode(head_ref, current);
}

int main()
{
    struct Node* head = NULL;

    append(&head, 6);
    push(&head, 7);
    push(&head, 1);
    append(&head, 4);
    append(&head, 9);
    insertAfter(head->next, 8);

    printf("\nUtworzona lista: ");
    printList(head);

    printf("\nLista po usunięciu drugiego elementu: ");
    deleteNode(&head, head->next);
    printList(head);

    printf("\nLista po usunięciu trzeciego elementu: ");
    deleteNodeAtGivenPos(&head, 3);
    printList(head);

    printf("\nLista po przesortowaniu: ");
    mergeSort(head);
    printList(head);

    return 0;
}

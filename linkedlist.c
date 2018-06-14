#include <stdlib.h>
#include <stdio.h>
/* 
 * implement a linked list,
 */
typedef struct node {
    int data;
    struct node *next;
} node_t;

void print_list(node_t *head);

node_t* create_node(int val);
void append(node_t *head, int val);
void prepend(node_t **head, int val);
int pop(node_t **head);
int remove_last(node_t **head);
int remove_by_index(node_t **head, int index);
int remove_by_value(node_t **head, int value);

int main(void) {
    node_t *head = create_node(1);
    append(head, 2);
    append(head, 3);
    append(head, 4);
    append(head, 5);
    remove_last(&head); 
    remove_by_index(&head, 1);
    remove_by_index(&head, 2);
    remove_by_value(&head, 3);
    print_list(head); // 1

    return 0;
}

void print_list(node_t *head) {
    node_t *entry = head;
    while(entry) {
        printf("%d ", entry->data);
        entry = entry->next;
    }
    printf("\n");
}

void append(node_t *head, int val) {
    //find the last of the node
    node_t *entry = head;
    if (!entry) {
        return;
    }
    while (entry->next) {
        entry = entry->next;
    }
    entry->next = create_node(val);
}

node_t* create_node(int val) {
    node_t* ret = malloc(sizeof(node_t));
    ret->data = val;
    ret->next = NULL;
    return ret;
}

void prepend(node_t **head, int val) {
    node_t* newhead = create_node(val);
    newhead->next = *head;
    *head = newhead; 
}

/* case 1 - head is null
 * case 2 - head next is null
 */
int pop(node_t **head) {
    if(!head || !*head) {
        return -1;
    }

    node_t *poped = *head;
    int val = poped->data;
    *head = poped->next;
    free(poped);
    return val;
}

int remove_last(node_t **head) {
    int ret = -1;

    if (!head || !*head) {
        return ret;
    }

    node_t **pp = head;
    node_t *entry = *head;

    while(entry->next) {
        pp = &entry->next;
        entry = entry->next;
    }

    //entry is last modify the pointer of entry
    int val = entry->data;
    node_t *del = *pp;
    *pp = entry->next;
    free(del);
    return ret;
}

int remove_by_index(node_t **head, int index) {
    int ret = -1;
    if (!head || !*head || index < 0) {
        return ret;
    }

    node_t *entry = *head;
    node_t **pp = head;
    int current = 0;
    while(entry) {
        if (current++ == index) {
            ret = entry->data;
            node_t *del = entry;
            *pp = entry->next;
            free(del);
            return ret;
        }
        pp = &entry->next;
        entry = entry->next;
    }

    return ret;
}

int remove_by_value(node_t **head, int value) {
    int ret = -1;
    if (!head || !*head) {
        return ret;
    }

    node_t **pp = head;
    node_t *entry = *head;
    while (entry) {
        if (entry->data == value) {
            node_t *del = entry;
            *pp = entry->next;
            free(del);
            return value;
        }
        pp = &entry->next;
        entry = entry->next;
    }

    return ret;
}

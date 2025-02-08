/**
 * slist.h - An elegant singly linked list implementation
 * Following the "good taste" coding philosophy of handling
 * edge cases elegantly through careful pointer manipulation.
 */

#include <stdio.h>
#include <stdlib.h>

struct list_node {
    struct list_node *next;
    int data;
};

struct list_head {
    struct list_node *head;
};

/* Initialize a new empty list */
static inline void list_init(struct list_head *list)
{
    list->head = NULL;
}

/* 
 * Insert a new entry - notice how we handle both empty and non-empty
 * list cases uniformly through indirect pointer manipulation
 */
static inline void list_add(struct list_head *list, struct list_node *new_node)
{
    struct list_node **indirect = &list->head;
    
    new_node->next = *indirect;
    *indirect = new_node;
}

/*
 * Remove an entry from the list.
 * The elegant part here is using the indirect pointer technique to
 * handle both head and non-head cases uniformly without special cases.
 */
static inline void list_remove(struct list_head *list, struct list_node *entry)
{
    struct list_node **indirect = &list->head;

    while (*indirect != entry)
        indirect = &(*indirect)->next;
    
    *indirect = entry->next;
}

/* Create a new list node with given data */
static inline struct list_node *create_node(int data)
{
    struct list_node *node = malloc(sizeof(*node));
    if (!node)
        return NULL;
        
    node->data = data;
    node->next = NULL;
    return node;
}

/* Example usage */
int main(void)
{
    struct list_head list;
    list_init(&list);

    /* Add some nodes */
    struct list_node *node1 = create_node(10);
    struct list_node *node2 = create_node(20);
    struct list_node *node3 = create_node(30);

    list_add(&list, node1);
    list_add(&list, node2);
    list_add(&list, node3);

    /* Print the list */
    printf("Initial list:\n");
    for (struct list_node *node = list.head; node; node = node->next)
        printf("%d ", node->data);
    printf("\n");

    /* Remove the middle node */
    list_remove(&list, node2);
    free(node2);

    printf("After removing 20:\n");
    for (struct list_node *node = list.head; node; node = node->next)
        printf("%d ", node->data);
    printf("\n");

    /* Clean up */
    while (list.head) {
        struct list_node *node = list.head;
        list_remove(&list, node);
        free(node);
    }

    return 0;
}

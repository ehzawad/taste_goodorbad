#include <stdio.h>
#include <stdlib.h>

// Node structure for a singly linked list
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Global head of the list
Node *head = NULL;

/**
 * remove_list_entry - Remove a given entry from the global list using an indirect pointer
 * @entry: Pointer to the Node we want to remove.
 */
void remove_list_entry(Node *entry) {
    // Pointer-to-pointer that starts at 'head'
    Node **indirect = &head;

    // Walk the list until we find the node that matches 'entry'
    while (*indirect != entry) {
        // If we get to the end without finding 'entry', just return
        if (*indirect == NULL) {
            printf("Node not found, nothing removed.\n");
            return;
        }
        indirect = &(*indirect)->next;
    }
    // Once we find 'entry', skip it in the list
    *indirect = entry->next;
}

/**
 * print_list - Prints out the entire list
 */
void print_list(void) {
    Node *current = head;
    printf("List contents: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

/**
 * create_node - Creates a new node with the given integer data
 */
Node* create_node(int value) {
    Node *new_node = malloc(sizeof(Node));
    if (!new_node) {
        perror("Failed to allocate memory for new node");
        exit(EXIT_FAILURE);
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

int main(void) {
    // Create a few nodes and link them into a list
    Node *n1 = create_node(10);
    Node *n2 = create_node(20);
    Node *n3 = create_node(30);

    // Build the list: head -> n1 -> n2 -> n3 -> NULL
    head = n1;
    n1->next = n2;
    n2->next = n3;

    // Print the list before removal
    print_list();  // Expect: 10 20 30

    // Remove the middle node (n2)
    printf("Removing node with data %d...\n", n2->data);
    remove_list_entry(n2);

    // Print the list after removal
    print_list();  // Expect: 10 30

    // Clean up allocated memory (just a quick example)
    remove_list_entry(n1); // effectively sets head -> n3
    remove_list_entry(n3); // sets head -> NULL
    free(n1);
    free(n2);  // removed from list, but we still need to free the memory
    free(n3);

    return 0;
}

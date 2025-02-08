#include <stdio.h>
#include <stdlib.h>

// A basic node structure for a singly linked list
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Global head pointer to the list
Node *head = NULL;

/**
 * remove_list_entry - Removes the specified 'entry' from the global list.
 * 
 * @entry: The node we want to remove
 *
 * This uses the "prev/walk" approach:
 *   - 'walk' traverses the list
 *   - 'prev' lags one behind, so we can re-link around 'entry'
 */
void remove_list_entry(Node *entry)
{
    Node *prev = NULL;
    Node *walk = head;

    // Walk through the list until we find 'entry' or reach the end
    while (walk != NULL && walk != entry) {
        prev = walk;
        walk = walk->next;
    }

    // If we never found 'entry', do nothing
    if (walk == NULL) {
        printf("Node not found; nothing removed.\n");
        return;
    }

    // If 'entry' was the first element, update head
    if (prev == NULL) {
        head = walk->next;
    } else {
        // Otherwise, point the previous node around 'walk'
        prev->next = walk->next;
    }
}

/**
 * print_list - Prints the contents of the global list
 */
void print_list(void)
{
    Node *current = head;
    printf("List contents: ");
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

/**
 * create_node - Allocates and initializes a new node with the given value
 */
Node* create_node(int value)
{
    Node *new_node = (Node*) malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory.\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

int main(void)
{
    // Create and link three nodes for demonstration
    Node *n1 = create_node(10);
    Node *n2 = create_node(20);
    Node *n3 = create_node(30);

    // Make head -> n1 -> n2 -> n3
    head = n1;
    n1->next = n2;
    n2->next = n3;

    // Print the list before removal
    print_list();  // Expect: 10 20 30

    // Remove the middle node (n2)
    printf("Removing node with data %d...\n", n2->data);
    remove_list_entry(n2);
    print_list();  // Expect: 10 30

    // Remove the head (n1)
    printf("Removing node with data %d...\n", n1->data);
    remove_list_entry(n1);
    print_list();  // Expect: 30

    // Finally remove the last node (n3)
    printf("Removing node with data %d...\n", n3->data);
    remove_list_entry(n3);
    print_list();  // Expect an empty list

    // Clean up memory (we've already removed them from the list, but must free individually)
    free(n1);
    free(n2);
    free(n3);

    return 0;
}

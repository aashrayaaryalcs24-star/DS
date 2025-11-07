#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
struct node {
    int data;
    struct node *next;
};

// Two global head pointers for the lists used in the program
struct node *head1 = NULL; // Main list (will hold the result of concatenation)
struct node *head2 = NULL; // Second list (for concatenation)

// --- Utility Functions ---

/**
 * @brief Utility function to insert a node at the beginning of a specified list.
 * @param head_ref A pointer to the head pointer of the list to be modified.
 * @param item The data to insert.
 */
void insert_at_beginning(struct node **head_ref, int item) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("\nOVERFLOW: Memory allocation failed.\n");
        return;
    }
    new_node->data = item;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

/**
 * @brief Displays the elements of a specified linked list.
 * @param head The head pointer of the list to display.
 * @param list_name The name of the list for display context.
 */
void display(struct node *head, const char *list_name) {
    struct node *ptr = head;
    printf("\n--- %s ---\n", list_name);
    if (ptr == NULL) {
        printf("List is empty.\n");
    } else {
        printf("Content: ");
        while (ptr != NULL) {
            printf("%d -> ", ptr->data);
            ptr = ptr->next;
        }
        printf("NULL\n");
    }
}

// --- Linked List Operations ---

/**
 * @brief Concatenates the second list (head2) to the end of the first list (head1).
 * The resulting list is stored in head1. head2 is set to NULL.
 */
void concatenate() {
    // If head1 is NULL, the result is head2
    if (head1 == NULL) {
        head1 = head2;
        head2 = NULL;
        printf("\nConcatenation complete: List 1 was empty, List 1 now equals List 2.\n");
        return;
    }
    
    // If head2 is NULL, nothing needs to be done
    if (head2 == NULL) {
        printf("\nConcatenation complete: List 2 was empty, no changes to List 1.\n");
        return;
    }

    // Traverse to the last node of the first list (head1)
    struct node *ptr = head1;
    while (ptr->next != NULL) {
        ptr = ptr->next;
    }

    // Link the last node of head1 to the head of head2
    ptr->next = head2;

    // Reset head2 to NULL as its nodes are now part of head1
    head2 = NULL;

    printf("\nConcatenation successful: List 2 added to the end of List 1.\n");
}

/**
 * @brief Reverses the order of nodes in the main list (head1).
 */
void reverse() {
    struct node *prev = NULL;
    struct node *current = head1;
    struct node *next_node = NULL;

    // Standard iterative reversal algorithm
    while (current != NULL) {
        // Store the next node
        next_node = current->next;
        
        // Reverse the current node's pointer
        current->next = prev;
        
        // Move pointers one step ahead
        prev = current;
        current = next_node;
    }
    
    // 'prev' is the new head of the reversed list
    head1 = prev;
    
    printf("\nList 1 has been successfully reversed.\n");
}

/**
 * @brief Sorts the nodes of the main list (head1) using a simple Bubble Sort algorithm.
 * Since the goal is simplicity and self-contained C code, Bubble Sort is used
 * by swapping the data fields of nodes.
 */
void sort() {
    struct node *i, *j;
    int temp_data;
    int swapped;

    if (head1 == NULL) {
        printf("\nCannot sort: List 1 is empty.\n");
        return;
    }

    // Bubble Sort implementation
    do {
        swapped = 0;
        i = head1;
        while (i->next != NULL) {
            j = i->next;
            
            if (i->data > j->data) {
                // Swap the data fields of the two nodes
                temp_data = i->data;
                i->data = j->data;
                j->data = temp_data;
                swapped = 1;
            }
            i = i->next;
        }
    } while (swapped);

    printf("\nList 1 has been successfully sorted in ascending order.\n");
}


// --- Main Program and Menu ---

void main() {
    int choice = 0, item, list_num;

    // Initial setup of List 1 (unsorted)
    insert_at_beginning(&head1, 20);
    insert_at_beginning(&head1, 5);
    insert_at_beginning(&head1, 45);
    insert_at_beginning(&head1, 10);

    // Initial setup of List 2
    insert_at_beginning(&head2, 99);
    insert_at_beginning(&head2, 33);
    insert_at_beginning(&head2, 66);

    printf("--- Initial Linked List State ---\n");
    display(head1, "List 1 (head1)");
    display(head2, "List 2 (head2)");
    
    while (choice != 7) {
        printf("\n******** LINKED LIST OPERATIONS MENU ********\n");
        printf("1. Concatenate List 2 onto List 1\n");
        printf("2. Reverse List 1\n");
        printf("3. Sort List 1 (Ascending)\n");
        printf("4. Display List 1\n");
        printf("5. Display List 2\n");
        printf("6. Insert Node (Utility)\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        
        // Input validation placeholder
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); // Clear input buffer
            choice = 0; 
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                concatenate();
                display(head1, "List 1 (Concatenated)");
                display(head2, "List 2 (Remaining)");
                break;
            case 2:
                reverse();
                display(head1, "List 1 (Reversed)");
                break;
            case 3:
                sort();
                display(head1, "List 1 (Sorted)");
                break;
            case 4:
                display(head1, "List 1");
                break;
            case 5:
                display(head2, "List 2");
                break;
            case 6:
                printf("Enter data to insert: ");
                scanf("%d", &item);
                printf("Insert into (1 or 2): ");
                scanf("%d", &list_num);
                if (list_num == 1) {
                    insert_at_beginning(&head1, item);
                } else if (list_num == 2) {
                    insert_at_beginning(&head2, item);
                } else {
                    printf("Invalid list number.\n");
                }
                display(head1, "List 1");
                display(head2, "List 2");
                break;
            case 7:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a choice between 1-7.\n");
        }
    }
}
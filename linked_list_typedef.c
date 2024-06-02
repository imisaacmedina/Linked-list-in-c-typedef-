#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

int node_length(Node* head) {
    if (head == NULL) {
        return 0;
    }
    
    int length = 0;
    Node* temp = head;
    
    while(temp != NULL) {
        temp = temp->next;
        length++;
    }
    
    return length;
}

int search(Node* head, int data) {
    if (head == NULL) {
        return -1;
    }
    
    int location = 0;
    Node* traverser = head;
    while(traverser != NULL) {
        if(traverser->data == data) {
            return location;
        }
        traverser = traverser->next;
        location++;
    }
    return -1;
}

void print_node(Node* head) {
    Node* temp = head;
    
    if (temp == NULL) {
        printf("Unable to print node as the list is empty.\n");
        return;
    }
    
    while (temp != NULL) {
        printf("%d", temp->data);
        
        if(temp->next != NULL) {
            printf(", ");
        }
        
        temp = temp->next;
    }
    
    printf("\n");
}

void insert_data(Node** head, int data) {
    Node* temp = (Node*) malloc(sizeof(Node));
    
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    printf("Insert %d: ", data);
    
    temp->data = data;
    temp->next = *head;
    *head = temp;
    
    print_node(*head);
}

void remove_data(Node** head) {
    if (*head == NULL) {
        printf("Unable to remove as the list is empty.\n");
        return;
    }
    
    Node* temp = *head;
    
    // Removing the first data in the list.
    *head = temp->next;
    free(temp);
    printf("Remove data: ");
    print_node(*head);
}

void insert_at(Node** head, int data, int index) {
    if(index < 0) {
        printf("Invalid index %d.\n", index);
        return;
    }
    
    if (*head == NULL && index > 0) {
        printf("Unable to insert at %d as the list length is 0.\n", index);
        return;
    }
    
    if (index == 0) {
        insert_data(head, data);
        return;
    }
    
    int len = node_length(*head);
    if (index > len) {
        printf("Unable to insert at index %d as the list length is only %d\n", index, len);
        return;
    }
    
    Node* temp = *head;
    Node* prev = NULL;
    for(int i = 0; i < index; i++) {
        prev = temp;
        temp = temp->next;
    }
    
    Node* new_data = (Node*)malloc(sizeof(Node));
    
    if (new_data == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    new_data->data = data;
    new_data->next = temp;
    if (prev != NULL) {
        prev->next = new_data;
    }
    
    printf("Insert %d at index %d: ", data, index);
    print_node(*head);
}

void insert_tail(Node** head, int data) {
    Node* temp = (Node*) malloc(sizeof(Node));
    
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    temp->data = data;
    temp->next = NULL;
    
    if (*head == NULL) {
        *head = temp;
    } else {
        Node* curr = *head;
        while (curr->next != NULL) {
            curr = curr->next;
        }
        curr->next = temp;
    }
    
    printf("Insert %d at tail: ", data);
    print_node(*head);
}

void remove_at(Node** head, int index) {
    if (*head == NULL) {
        printf("Unable to remove data at index %d as the list is empty.\n", index);
        return;
    }
    
    if (index < 0) {
        printf("Invalid index %d.\n", index);
        return;
    }
    
    if (index == 0) {
        remove_data(head);
        return;
    }
    
    int len = node_length(*head);
    if (index >= len) {
        printf("Unable to remove data at index %d as the list length is only %d.\n", index, len);
        return;
    }
    
    Node* curr = *head;
    Node* prev = NULL;
    for (int i = 0; i < index; i++) {
        prev = curr;
        curr = curr->next;
    }
    
    prev->next = curr->next;
    free(curr);
    
    printf("Remove data at index %d: ", index);
    print_node(*head);
}

void remove_tail(Node** head) {
    if (*head == NULL) {
        printf("Unable to remove last as the list is empty.\n");
        return;
    }
    
    Node* temp = *head;
    Node* prev = NULL;
    
    if (temp->next == NULL) {
        *head = NULL;
        free(temp);
    } else {
        while (temp->next != NULL) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = NULL;
        free(temp);
    }
    
    printf("Remove tail: ");
    print_node(*head);
}

void find(Node* head, int data) {
    int location = search(head, data);
    
    if (location == -1) {
        printf("%d is not in the list.\n", data);
    } else {
        printf("%d is in index %d.\n", data, location);
    }
}

int main() {
    Node* head = NULL;
    
    insert_at(&head, 6, 2);
    insert_at(&head, 99, 0);
    remove_tail(&head);
    insert_data(&head, 5);
    insert_data(&head, 7);
    insert_tail(&head, 888);
    remove_at(&head, 0);
    insert_data(&head, 9);
    remove_data(&head);
    insert_data(&head, 3);
    insert_at(&head, 6, 2);
    insert_at(&head, 77, 4);
    remove_tail(&head);
    find(head, 888);
    find(head, 3);
    find(head, 99);

    return 0;
}

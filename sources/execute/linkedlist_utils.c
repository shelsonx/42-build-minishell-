#include "../../includes/minishell.h"

LinkedList* allocate_list () {
    // Allocates memory for a Linkedlist pointer
    LinkedList* list = (LinkedList*) ft_calloc (1, sizeof(LinkedList));
    return list;
}

LinkedList* linkedlist_insert(LinkedList* list, Ht_item* item) {
    // Inserts the item onto the Linked List
    if (!list) {
        LinkedList* head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    } 
    
    else if (list->next == NULL) {
        LinkedList* node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    LinkedList* temp = list;
    while (temp->next) {
        temp = temp->next;
    }
    
    LinkedList* node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;
    
    return list;
}

void free_linkedlist(LinkedList* list) {
    LinkedList* temp = list;
    if (!list)
        return;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}

LinkedList** create_overflow_buckets(HashTable* table) {
    // Create the overflow buckets; an array of linkedlists
    LinkedList** buckets = (LinkedList**) ft_calloc (table->size, sizeof(LinkedList*));
    int i=0;
    while(i<table->size) {
        buckets[i] = NULL;
        i++;
    }
    return buckets;
}

void free_overflow_buckets(HashTable* table) {
    // Free all the overflow bucket lists
    LinkedList** buckets = table->overflow_buckets;
    int i=0;
    while(i<table->size){
        free_linkedlist(buckets[i]);
        i++;
    }
    free(buckets); 
}

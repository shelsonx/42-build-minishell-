#include "../../includes/minishell.h"

s_linkedList* allocate_list () {
    s_linkedList* list = (s_linkedList*) ft_calloc (1, sizeof(s_linkedList));
    return list;
}

s_linkedList* linkedlist_insert(s_linkedList* list, s_htItem* item) {
    if (!list) {
        s_linkedList* head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    } 
    
    else if (list->next == NULL) {
        s_linkedList* node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    s_linkedList* temp = list;
    while (temp->next) {
        temp = temp->next;
    }
    
    s_linkedList* node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;
    
    return list;
}

void free_linkedlist(s_linkedList* list) {
    s_linkedList* temp = list;
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

s_linkedList** create_overflow_buckets(s_hashTable* table) {
    s_linkedList** buckets = (s_linkedList**) ft_calloc (table->size, sizeof(s_linkedList*));
    int i=0;
    while(i<table->size) {
        buckets[i] = NULL;
        i++;
    }
    return buckets;
}

void free_overflow_buckets(s_hashTable* table) {
    s_linkedList** buckets = table->overflow_buckets;
    int i=0;
    while(i<table->size){
        free_linkedlist(buckets[i]);
        i++;
    }
    free(buckets); 
}

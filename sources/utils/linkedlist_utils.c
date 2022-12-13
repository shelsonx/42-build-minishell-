#include "../../includes/minishell.h"

t_linkedlist* allocate_list () {
    t_linkedlist* list = (t_linkedlist*) ft_calloc (1, sizeof(t_linkedlist));
    return list;
}

t_linkedlist* linkedlist_insert(t_linkedlist* list, t_htitem* item) {
    if (!list) {
        t_linkedlist* head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    } 
    
    else if (list->next == NULL) {
        t_linkedlist* node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }

    t_linkedlist* temp = list;
    while (temp->next) {
        temp = temp->next;
    }
    
    t_linkedlist* node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;
    
    return list;
}

void free_linkedlist(t_linkedlist* list) {
    t_linkedlist* temp = list;
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

t_linkedlist** create_overflow_buckets(t_hashtable* table) {
    t_linkedlist** buckets = (t_linkedlist**) ft_calloc (table->size, sizeof(t_linkedlist*));
    int i=0;
    while(i<table->size) {
        buckets[i] = NULL;
        i++;
    }
    return buckets;
}

void free_overflow_buckets(t_hashtable* table) {
    t_linkedlist** buckets = table->overflow_buckets;
    int i=0;
    while(i<table->size){
        free_linkedlist(buckets[i]);
        i++;
    }
    free(buckets); 
}

#include "../../includes/minishell.h"

 /*static t_htitem* linkedlist_remove(t_linkedlist* list) {
    if (!list)
        return NULL;
    if (!list->next)
        return NULL;
    t_linkedlist* node = list->next;
    t_linkedlist* temp = list;
    temp->next = NULL;
    list = node;
    t_htitem* it = NULL;
    ft_memcpy(temp->item, it, sizeof(t_htitem));
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;
}*/

t_hashtable* create_table(int size) {
    t_hashtable* table = (t_hashtable*) malloc (sizeof(t_hashtable));
    table->size = size;
    table->count = 0;
    table->items = (t_htitem**) ft_calloc (table->size, sizeof(t_htitem*));
    int i=0; 
    while(i<table->size){
        table->items[i] = NULL;
        i++;
    }
    table->overflow_buckets = create_overflow_buckets(table);

    return table;
}

void free_hashtable(t_hashtable* table) {
    int i=0;
    while(i<table->size) {
        t_htitem* item = table->items[i];
        if (item != NULL)
            free_item(item);
        i++;
    }

    free_overflow_buckets(table);
    free(table->items);
    free(table);
}

void ht_insert(t_hashtable* table, char* key, char* value) {
    t_htitem* item = create_item(key, value);

    int index = hash_function(key);

    t_htitem* current_item = table->items[index];
    
    if (current_item == NULL) {
        if (table->count == table->size) {
            printf("Insert Error: Hash Table is full\n");
            free_item(item);
            return;
        }
        table->items[index] = item; 
        table->count++;
    }

    else {
            if (ft_strcmp(current_item->key, key) == 0) {
                free(table->items[index]->value);
                table->items[index]->value = (char*) ft_calloc (ft_strlen(value) + 1, sizeof(char));
                ft_strcpy(table->items[index]->value, value);
                free_item(item);
                return;
            }
    
        else {
            handle_collision(table, index, item);
            return;
        }
    }
}

char* ht_search(t_hashtable* table, char* key) {
    int index = hash_function(key);
    t_htitem* item = table->items[index];
    t_linkedlist* head = table->overflow_buckets[index];

    while (item != NULL) {
        if (ft_strcmp(item->key, key) == 0)
            return item->value;
        if (head == NULL)
            return NULL;
        item = head->item;
        head = head->next;
    }
    return NULL;
}

/*
void print_search(t_hashtable* table, char* key) {
    char* val;
    if ((val = ht_search(table, key)) == NULL) {
        printf("%s does not exist\n", key);
        return;
    }
    else {
        printf("Key:%s, Value:%s\n", key, val);
    }
}
*/
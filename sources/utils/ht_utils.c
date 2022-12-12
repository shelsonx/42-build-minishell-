#include "../../includes/minishell.h"

 /*static s_htItem* linkedlist_remove(s_linkedList* list) {
    if (!list)
        return NULL;
    if (!list->next)
        return NULL;
    s_linkedList* node = list->next;
    s_linkedList* temp = list;
    temp->next = NULL;
    list = node;
    s_htItem* it = NULL;
    ft_memcpy(temp->item, it, sizeof(s_htItem));
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;
}*/

s_hashTable* create_table(int size) {
    s_hashTable* table = (s_hashTable*) malloc (sizeof(s_hashTable));
    table->size = size;
    table->count = 0;
    table->items = (s_htItem**) ft_calloc (table->size, sizeof(s_htItem*));
    int i=0; 
    while(i<table->size){
        table->items[i] = NULL;
        i++;
    }
    table->overflow_buckets = create_overflow_buckets(table);

    return table;
}

void free_hashtable(s_hashTable* table) {
    int i=0;
    while(i<table->size) {
        s_htItem* item = table->items[i];
        if (item != NULL)
            free_item(item);
        i++;
    }

    free_overflow_buckets(table);
    free(table->items);
    free(table);
}

void ht_insert(s_hashTable* table, char* key, char* value) {
    s_htItem* item = create_item(key, value);

    int index = hash_function(key);

    s_htItem* current_item = table->items[index];
    
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

char* ht_search(s_hashTable* table, char* key) {
    int index = hash_function(key);
    s_htItem* item = table->items[index];
    s_linkedList* head = table->overflow_buckets[index];

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
void print_search(s_hashTable* table, char* key) {
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
#include "../../includes/minishell.h"

unsigned long hash_function(char* str) {
    unsigned long i = 0;
    int j=0;
    while (str[j]){
        i += str[j];
        j++;
    }
    return i % CAPACITY;
}

s_htItem* create_item(char* key, char* value) {
    s_htItem* item = (s_htItem*) malloc (sizeof(s_htItem));
    item->key = (char*) ft_calloc (ft_strlen(key) + 1, sizeof(char));
    item->value = (char*) ft_calloc (ft_strlen(value) + 1, sizeof(char));
    
    ft_strcpy(item->key, key);
    ft_strcpy(item->value, value);

    return item;
}

void free_item(s_htItem* item) {
    free(item->key);
    free(item->value);
    free(item);
}

void handle_collision(s_hashTable* table, unsigned long index, s_htItem* item) {
    s_linkedList* head = table->overflow_buckets[index];

    if (head == NULL) {
        head = allocate_list();
        head->item = item;
        table->overflow_buckets[index] = head;
        return;
    }
    else {
        table->overflow_buckets[index] = linkedlist_insert(head, item);
        return;
    }
 }

void ht_delete(s_hashTable* table, char* key) {
    int index = hash_function(key);
    s_htItem* item = table->items[index];
    s_linkedList* head = table->overflow_buckets[index];

    if (item == NULL) {
        return;
    }
    else {
        if (head == NULL && ft_strcmp(item->key, key) == 0) {
            table->items[index] = NULL;
            free_item(item);
            table->count--;
            return;
        }
        else if (head != NULL) {
            if (ft_strcmp(item->key, key) == 0) {             
                free_item(item);
                s_linkedList* node = head;
                head = head->next;
                node->next = NULL;
                table->items[index] = create_item(node->item->key, node->item->value);
                free_linkedlist(node);
                table->overflow_buckets[index] = head;
                return;
            }

            s_linkedList* curr = head;
            s_linkedList* prev = NULL;
            
            while (curr) {
                if (ft_strcmp(curr->item->key, key) == 0) {
                    if (prev == NULL) {
                        free_linkedlist(head);
                        table->overflow_buckets[index] = NULL;
                        return;
                    }
                    else {
                        prev->next = curr->next;
                        curr->next = NULL;
                        free_linkedlist(curr);
                        table->overflow_buckets[index] = head;
                        return;
                    }
                }
                curr = curr->next;
                prev = curr;
            }

        }
    }

}


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

t_htitem* create_item(char* key, char* value) {
    t_htitem* item = (t_htitem*) malloc (sizeof(t_htitem));
    item->key = (char*) ft_calloc (ft_strlen(key) + 1, sizeof(char));
    item->value = (char*) ft_calloc (ft_strlen(value) + 1, sizeof(char));
    
    ft_strcpy(item->key, key);
    ft_strcpy(item->value, value);

    return item;
}

void free_item(t_htitem* item) {
    free(item->key);
    free(item->value);
    free(item);
}

void handle_collision(t_hashtable* table, unsigned long index, t_htitem* item) {
    t_linkedlist* head = table->overflow_buckets[index];

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

void ht_delete(t_hashtable* table, char* key) {
    int index = hash_function(key);
    t_htitem* item = table->items[index];
    t_linkedlist* head = table->overflow_buckets[index];

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
                t_linkedlist* node = head;
                head = head->next;
                node->next = NULL;
                table->items[index] = create_item(node->item->key, node->item->value);
                free_linkedlist(node);
                table->overflow_buckets[index] = head;
                return;
            }

            t_linkedlist* curr = head;
            t_linkedlist* prev = NULL;
            
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


#include "../../includes/minishell.h"

/* static Ht_item* linkedlist_remove(LinkedList* list) {
    // Removes the head from the linked list
    // and returns the item of the popped element
    if (!list)
        return NULL;
    if (!list->next)
        return NULL;
    LinkedList* node = list->next;
    LinkedList* temp = list;
    temp->next = NULL;
    list = node;
    Ht_item* it = NULL;
    ft_memcpy(temp->item, it, sizeof(Ht_item));
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;
} */

HashTable* create_table(int size) {
    // Creates a new HashTable
    HashTable* table = (HashTable*) malloc (sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item**) ft_calloc (table->size, sizeof(Ht_item*));
    int i=0; 
    while(i<table->size){
        table->items[i] = NULL;
        i++;
    }
    table->overflow_buckets = create_overflow_buckets(table);

    return table;
}

void free_hashtable(HashTable* table) {
    // Frees the table
    int i=0;
    while(i<table->size) {
        Ht_item* item = table->items[i];
        if (item != NULL)
            free_item(item);
        i++;
    }

    free_overflow_buckets(table);
    free(table->items);
    free(table);
}

void ht_insert(HashTable* table, char* key, char* value) {
    // Create the item
    Ht_item* item = create_item(key, value);

    // Compute the index
    int index = hash_function(key);

    Ht_item* current_item = table->items[index];
    
    if (current_item == NULL) {
        // Key does not exist.
        if (table->count == table->size) {
            // Hash Table Full
            printf("Insert Error: Hash Table is full\n");
            // Remove the create item
            free_item(item);
            return;
        }
        
        // Insert directly
        table->items[index] = item; 
        table->count++;
    }

    else {
            // Scenario 1: We only need to update value
            if (ft_strcmp(current_item->key, key) == 0) {
                free(table->items[index]->value);
                table->items[index]->value = (char*) ft_calloc (ft_strlen(value) + 1, sizeof(char));
                ft_strcpy(table->items[index]->value, value);
                free_item(item);
                return;
            }
    
        else {
            // Scenario 2: Collision
            handle_collision(table, index, item);
            return;
        }
    }
}

char* ht_search(HashTable* table, char* key) {
    // Searches the key in the hashtable
    // and returns NULL if it doesn't exist
    int index = hash_function(key);
    Ht_item* item = table->items[index];
    LinkedList* head = table->overflow_buckets[index];

    // Ensure that we move to items which are not NULL
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
void print_search(HashTable* table, char* key) {
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

/*
void print_hashtable(HashTable* table) {
    printf("\n-------------------\n");
    int i=0;
    while (i<table->size) {
        if (table->items[i]) {
            printf("Index:%d, Key:%s, Value:%s", i, table->items[i]->key, table->items[i]->value);
            if (table->overflow_buckets[i]) {
                printf(" => Overflow Bucket => ");
                LinkedList* head = table->overflow_buckets[i];
                while (head) {
                    printf("Key:%s, Value:%s ", head->item->key, head->item->value);
                    head = head->next;
                }
            }
            printf("\n");
        }
        i++;
    }
    printf("-------------------\n");
}
*/


/*  int main() {
     HashTable* ht = create_table(CAPACITY);
     ht_insert(ht, "1", "First address");
     ht_insert(ht, "2", "Second address");
     ht_insert(ht, "Hel", "Third address");
     ht_insert(ht, "Cau", "Fourth address");
     print_search(ht, "1");
     print_search(ht, "2");
     print_search(ht, "3");
     print_search(ht, "Hel");
     print_search(ht, "Cau");  //Collision!
     print_hashtable(ht);
     ht_delete(ht, "1");
     ht_delete(ht, "Cau");
     print_hashtable(ht);
     free_hashtable(ht);
     return 0;
 } */
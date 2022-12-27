#include "../../includes/minishell.h"

int main() {
     t_hashtable*  ht = create_table(CAPACITY);
     ht_insert(ht, "1", "First address");
     ht_insert(ht, "2", "Second address");
     ht_insert(ht, "3", "Three address");
    
     ht_delete(ht, "2");
     ht_insert(ht, "2", "new value");

     printf("%s\n", ht_search(ht, "1"));
     printf("%s\n", ht_search(ht, "2"));
     printf("%s\n", ht_search(ht, "3"));

     
     free_hashtable(ht);
     return 0;
}

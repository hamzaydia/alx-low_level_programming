#include "hash_tables.h"

/**
 * hash_table_print - Prints a hash table.
 * @ht: Pointer to a hash table.
 */
void hash_table_print(const hash_table_t *ht)
{
    hash_node_t *current;
    char separator = 0;
    unsigned long int i;

    if (ht != NULL)
    {
        printf("{");
        for (i = 0; i < ht->size; i++)
        {
            current = ht->array[i];
            while (current != NULL)
            {
                if (separator == 1)
                    printf(", ");
                printf("'%s': '%s'", current->key, current->value);
                current = current->next;
                separator = 1;
            }
        }
        printf("}\n");
    }
}

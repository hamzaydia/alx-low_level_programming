#include "hash_tables.h"
/**
 * hash_table_print - Print a hash table
 * @ht: Pointer to a hash table.
 */
void hash_table_print(const hash_table_t *ht)
{
	hash_node_t *n;
	char s = 0;
	unsigned long int i;

	if (ht != NULL)
	{
		printf("{");
		for (i = 0; i < ht->size; i++)
		{
			n = (ht->array)[i];
			while (n != NULL)
			{
				if (s == 1)
					printf(", ");
				printf("'%s': '%s'", n->key, n->value);
				n = n->next;
				s = 1;
			}
		}
		printf("}\n");
	}
}

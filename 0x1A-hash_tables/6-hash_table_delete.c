#include "hash_tables.h"
/**
 * hash_table_delete - Deletes a hash table.
 * @ht: Pointer to the hash table.
 */
void hash_table_delete(hash_table_t *ht)
{
	hash_node_t *n, *c;
	unsigned long int i;

	if (ht == NULL)
		return;

	for (i = 0; i < ht->size; i++)
	{
		c = (ht->array)[i];
		while (c != NULL)
		{
			n = c->next;
			free(c->key);
			free(c->value);
			free(c);
			c = n;
		}
	}
	free(ht->array);
	free(ht);
}

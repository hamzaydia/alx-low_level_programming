#include "hash_tables.h"

/**
 * hash_table_get - Retrieves a value associated with a key.
 * @ht: Pointer to the hash table.
 * @key: Pointer to a the key string.
 * Return: Value associated with the key, or NULL if key couldn't be found.
 */
char *hash_table_get(const hash_table_t *ht, const char *key)
{
	hash_node_t *n;
	char *v = NULL;
	unsigned long int i;

	if (ht == NULL || key == NULL)
		return (NULL);

	i = key_index((const unsigned char *) key, ht->size);

	n = (ht->array)[i];
	while (n != NULL)
	{
		if (strcmp(n->key, key) == 0)
		{
			v = strdup(n->value);
			break;
		}
		n = n->next;
	}
	return (v);
}

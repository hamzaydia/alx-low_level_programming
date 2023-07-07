#include "hash_tables.h"

/**
 * hash_table_set - Adds an element to the hash table. Key collisions result in
 * the creation of a singly linkedlist at the index, with the newest value
 * added at the beginning of the list. If a key-value pair exist already, over
 * write the old value with the new value.
 * @ht: Pointer to the hash table.
 * @key: The key inside the hash table.
 * @value: The corresponding value of the key.
 * Return: 1 upon success, otherwise 0.
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	char *v, *k;
	hash_node_t *n;
	unsigned long int i;

	if (ht == NULL || key == NULL || strcmp(key, "") == 0 || value == NULL)
		return (0);

	v = strdup(value);
	if (v == NULL)
		return (0);

	i = key_index((const unsigned char *) key, ht->size);
	n = (ht->array)[i];
	while (n != NULL)
	{
		if (strcmp(n->key, key) == 0)
		{
			free(n->value);
			n->value = v;
			return (1);
		}
		n = n->next;
	}
	k = strdup(key);
	if (k == NULL)
		return (0);

	n = malloc(sizeof(hash_node_t));
	if (n == NULL)
	{
		free(v);
		free(k);
		return (0);
	}
	n->value = v;
	n->key = k;
	n->next = (ht->array)[i];
	(ht->array)[i] = n;

	return (1);
}

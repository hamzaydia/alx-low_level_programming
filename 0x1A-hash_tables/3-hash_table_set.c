#include "hash_tables.h"

/**
 * hash_table_set - Adds an element to the hash table.
 * @ht: Pointer to the hash table.
 * @key: The key inside the hash table.
 * @value: The corresponding value of the key.
 *
 * Return: 1 upon success, otherwise 0.
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
	char *v_cp, *k_cp;
	unsigned long int idx;
	hash_node_t *cur;

	if (ht == NULL || key == NULL || strcmp(key, "") == 0 || value == NULL)
		return (0);

	v_cp = strdup(value);
	if (v_cp == NULL)
		return (0);

	idx = key_index((const unsigned char *)key, ht->size);
	cur = ht->array[idx];
	while (cur != NULL)
	{
		if (strcmp(cur->key, key) == 0)
		{
			free(cur->value);
			cur->value = v_cp;
			return (1);
		}
		cur = cur->next;
	}
	k_cp = strdup(key);
	if (k_cp == NULL)
		return (0);

	cur = malloc(sizeof(hash_node_t));
	if (cur == NULL)
	{
		free(v_cp);
		free(k_cp);
		return (0);
	}
	cur->key = k_cp;
	cur->value = v_cp;
	cur->next = ht->array[idx];
	ht->array[idx] = cur;

	return (1);
}

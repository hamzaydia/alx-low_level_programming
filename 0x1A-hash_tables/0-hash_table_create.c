#include "hash_tables.h"

/**
 * hash_table_create - allocates memory for hash table
 * @size: size of new hash table
 * Return: pointer to newly allocated memory space for hash table
 */

hash_table_t *hash_table_create(unsigned long int size)
{
	hash_table_t *new_mem;

	if (size == 0)
		return (NULL);
	new_mem = malloc(sizeof(hash_table_t));
	if (!new_mem)
		return (NULL);
	new_mem->array = malloc(sizeof(hash_node_t *) * size);
	if (!new_mem->array)
	{
		free(new_mem);
		return (NULL);
	}
	new_mem->size = size;
	return (new_mem);
}

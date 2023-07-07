#include "hash_tables.h"
/**
 * hash_table_create - allocate memory for hash table
 * @size: unsigned long int
 * Return: pointer
 */
hash_table_t *hash_table_create(unsigned long int size)
{
	hash_table_t *mem;

	if (size == 0)
		return (NULL);
	mem = malloc(sizeof(hash_table_t));
	if (mem != NULL)
	{
		mem->array = malloc(sizeof(hash_node_t *) * size);
		if (mem->array == NULL)
			return (NULL);
		mem->size = size;
	}
	return (mem);
}

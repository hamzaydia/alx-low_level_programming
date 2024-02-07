#include "hash_tables.h"

/**
 * key_index - Returns an index for a hash table based on the hash of the key.
 * @key: A const unsigned char pointer to a string.
 * @size: Size of array of the hash table.
 *
 * Return: Index corresponding to the hash of the key in the array.
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	return (hash_djb2(key) % size);
}

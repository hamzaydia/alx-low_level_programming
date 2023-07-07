#include "hash_tables.h"
/**
 * key_index - get an index based on the hash of the key
 * @key: const unsigned char*
 * @size: unsigned long int
 * Return: unsigned long int
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	return ((hash_djb2(key) % size));
}

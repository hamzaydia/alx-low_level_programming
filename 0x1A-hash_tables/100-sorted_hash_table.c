#include "hash_tables.h"
/**
 * shash_table_create - Allocate memory for sorted hash table
 * @size: unsigned long int
 * Return: shash_table_t*
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *nht;
	unsigned long int i;

	if (size == 0)
		return (NULL);

	nht = malloc(sizeof(shash_table_t));
	if (nht != NULL)
	{
		nht->array = malloc(sizeof(shash_node_t *) * size);
		if (nht->array == NULL)
		{
			free(nht);
			return (NULL);
		}
		for (i = 0; i < size; i++)
			nht->array[i] = NULL;
		nht->size = size;
		nht->stail = NULL;
		nht->shead = NULL;
	}

	return (nht);
}

/**
 * shash_table_set - Add element to the sorted hash table
 * @ht: shash_table_t*
 * @key: const char*
 * @value: const char*
 * Return: int
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	char *v, *k;
	unsigned long int i;
	shash_node_t *c, *nht;

	if (ht == NULL || key == NULL || strcmp(key, "") == 0 ||
			value == NULL || ht->array == NULL || ht->size == 0)
		return (0);

	v = strdup(value);
	if (v == NULL)
		return (0);

	i = key_index((const unsigned char *) key, ht->size);
	c = (ht->array)[i];
	while (c != NULL)
	{
		if (strcmp(c->key, key) == 0)
		{
			free(c->value);
			c->value = v;
			return (1);
		}
		c = c->next;
	}
	k = strdup(key);
	if (k == NULL)
		return (0);
	nht = malloc(sizeof(shash_node_t));
	if (nht == NULL)
	{
		free(v);
		free(k);
		return (0);
	}
	nht->key = k;
	nht->value = v;
	nht->next = (ht->array)[i];
	(ht->array)[i] = nht;
	insert_sorted(ht, nht);
	return (1);
}
/**
 * insert_sorted - add element in the correct position of a sorted ht
 * @ht: shash_table_t*
 * @new: shash_node_t*
 */
void insert_sorted(shash_table_t *ht, shash_node_t *new)
{
	shash_node_t *c;

	new->sprev = NULL;
	new->snext = NULL;
	if (ht->shead == NULL)
	{
		ht->shead = new;
		ht->stail = new;
		return;
	}
	c = ht->shead;
	while (c != NULL)
	{
		if (strcmp(c->key, new->key) > 0)
		{
			new->snext = c;
			new->sprev = c->sprev;
			if (c->sprev == NULL)
				ht->shead = new;
			else
				new->sprev->snext = new;
			c->sprev = new;
			break;
		}
		c = c->snext;
	}
	if (c == NULL)
	{
		c = ht->stail;
		new->sprev = c;
		c->snext = new;
		ht->stail = new;
	}
}
/**
 * shash_table_get - Retrieve a value associated with a key
 * @ht: const shash_table_t*
 * @key: const char*
 * Return: char*
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	unsigned long int i;
	shash_node_t *c;
	char *v = NULL;

	if (ht == NULL || key == NULL || strlen(key) == 0 ||
			ht->array == NULL || ht->size == 0)
		return (NULL);
	i = key_index((const unsigned char *) key, ht->size);
	c = (ht->array)[i];
	while (c != NULL)
	{
		if (strcmp(c->key, key) == 0)
		{
			v = strdup(c->value);
			break;
		}
		c = c->next;
	}
	return (v);
}

/**
 * shash_table_print - Print a sorted hash table
 * @ht: const shash_table_t*
 */
void shash_table_print(const shash_table_t *ht)
{
	shash_node_t *c;
	char s = 0;

	if (ht != NULL)
	{
		printf("{");
		for (c = ht->shead; c != NULL; c = c->snext)
		{
			if (s == 1)
				printf(", ");
			printf("'%s': '%s'", c->key, c->value);
			s = 1;
		}
		printf("}\n");
	}
}

/**
 * shash_table_print_rev - Print a sorted hash table in reverse
 * @ht: const shash_table_t*
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	shash_node_t *c;
	char s = 0;

	if (ht != NULL)
	{
		printf("{");
		for (c = ht->stail; c != NULL; c = c->sprev)
		{
			if (s == 1)
				printf(", ");
			printf("'%s': '%s'", c->key, c->value);
			s = 1;
		}
		printf("}\n");
	}
}

/**
 * shash_table_delete - Delete a sorted hash table
 * @ht: shash_table_t*
 */
void shash_table_delete(shash_table_t *ht)
{
	shash_node_t *c, *nxt;
	unsigned long int i;

	if (ht == NULL)
		return;

	for (i = 0; i < ht->size; i++)
	{
		c = (ht->array)[i];
		while (c != NULL)
		{
			nxt = c->next;
			c->next = NULL;
			c->snext = NULL;
			c->sprev = NULL;
			free(c->key);
			c->key = NULL;
			free(c->value);
			free(c);
			c = nxt;
		}
	}
	free(ht->array);
	ht->array = NULL;
	ht->shead = NULL;
	ht->stail = NULL;
	free(ht);
}

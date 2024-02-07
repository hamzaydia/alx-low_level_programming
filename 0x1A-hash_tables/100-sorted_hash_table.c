#include "hash_tables.h"

shash_table_t *shash_table_create(unsigned long int size)
{
    shash_table_t *new;
    unsigned long int i;

    if (size == 0)
        return (NULL);

    new = malloc(sizeof(shash_table_t));
    if (new == NULL)
        return (NULL);

    new->array = malloc(sizeof(shash_node_t *) * size);
    if (new->array == NULL)
    {
        free(new);
        return (NULL);
    }

    for (i = 0; i < size; i++)
        new->array[i] = NULL;

    new->size = size;
    new->shead = NULL;
    new->stail = NULL;

    return (new);
}

int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
    char *v_cp;
    unsigned long int i;
    shash_node_t *cur, *new;
    char *k_cp;
    
    if (ht == NULL || key == NULL || value == NULL || ht->array == NULL || ht->size == 0)
        return (0);

    v_cp = strdup(value);
    if (v_cp == NULL)
        return (0);

    i = key_index((const unsigned char *)key, ht->size);
    cur = ht->array[i];

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
    {
        free(v_cp);
        return (0);
    }

    new = malloc(sizeof(shash_node_t));
    if (new == NULL)
    {
        free(v_cp);
        free(k_cp);
        return (0);
    }

    new->key = k_cp;
    new->value = v_cp;
    new->next = ht->array[i];
    ht->array[i] = new;
    insert_sorted(ht, new);

    return (1);
}

void insert_sorted(shash_table_t *ht, shash_node_t *new)
{
    shash_node_t *cur;

    new->sprev = NULL;
    new->snext = NULL;
    if (ht->shead == NULL)
    {
        ht->shead = new;
        ht->stail = new;
        return;
    }
    cur = ht->shead;
    while (cur != NULL)
    {
        if (strcmp(cur->key, new->key) > 0)
        {
            new->snext = cur;
            new->sprev = cur->sprev;
            if (cur->sprev == NULL)
                ht->shead = new;
            else
                new->sprev->snext = new;
            cur->sprev = new;
            break;
        }
        cur = cur->snext;
    }
    if (cur == NULL)
    {
        cur = ht->stail;
        new->sprev = cur;
        cur->snext = new;
        ht->stail = new;
    }
}

char *shash_table_get(const shash_table_t *ht, const char *key)
{
    unsigned long int i;
    shash_node_t *cur;
    char *v_cp = NULL;

    if (ht == NULL || key == NULL || strlen(key) == 0 || ht->array == NULL || ht->size == 0)
        return (NULL);
    i = key_index((const unsigned char *)key, ht->size);
    cur = (ht->array)[i];
    while (cur != NULL)
    {
        if (strcmp(cur->key, key) == 0)
        {
            v_cp = strdup(cur->value);
            break;
        }
        cur = cur->next;
    }
    return (v_cp);
}

void shash_table_print(const shash_table_t *ht)
{
    shash_node_t *cur;
    char separater = 0;

    if (ht != NULL)
    {
        printf("{");
        for (cur = ht->shead; cur != NULL; cur = cur->snext)
        {
            if (separater == 1)
                printf(", ");
            printf("'%s': '%s'", cur->key, cur->value);
            separater = 1;
        }
        printf("}\n");
    }
}

void shash_table_print_rev(const shash_table_t *ht)
{
    shash_node_t *cur;
    char separater = 0;

    if (ht != NULL)
    {
        printf("{");
        for (cur = ht->stail; cur != NULL; cur = cur->sprev)
        {
            if (separater == 1)
                printf(", ");
            printf("'%s': '%s'", cur->key, cur->value);
            separater = 1;
        }
        printf("}\n");
    }
}

void shash_table_delete(shash_table_t *ht)
{
    shash_node_t *cur, *nxt;
    unsigned long int i;

    if (ht == NULL)
        return;

    for (i = 0; i < ht->size; i++)
    {
        cur = (ht->array)[i];
        while (cur != NULL)
        {
            nxt = cur->next;
            cur->next = NULL;
            cur->snext = NULL;
            cur->sprev = NULL;
            free(cur->key);
            cur->key = NULL;
            free(cur->value);
            free(cur);
            cur = nxt;
        }
    }
    free(ht->array);
    ht->array = NULL;
    ht->shead = NULL;
    ht->stail = NULL;
    free(ht);
}

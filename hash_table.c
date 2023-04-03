#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long ht_hash;

typedef struct HT_Item {
    char *key;
    char *value;
    struct HT_Item *prev;
    struct HT_Item *next;
} HT_Item;

typedef struct HashTable {
    HT_Item **items;
    int count;
    int size;
} HashTable;

ht_hash hash_key(char *key, int ht_size) {
    ht_hash c = 0;

    for (int i = 0; key[i]; i++) {
        c += key[i];
    }

    return c % ht_size;
}

HT_Item* create_ht_item(char *key, char *value) {
    HT_Item *item = (HT_Item*)malloc(sizeof(HT_Item));
    item->key = malloc(strlen(key) + 1);
    item->value = malloc(strlen(value) + 1);
    strcpy(item->key, key);
    strcpy(item->value, value);

    item->prev = NULL;
    item->next = NULL;

    return item;
}

void free_ht_item(HT_Item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

HashTable* create_hash_table(int size) {
    HashTable *ht = (HashTable*)malloc(sizeof(HashTable));
    
    ht->size = size;
    ht->count = 0;
    ht->items = (HT_Item**)calloc(ht->size, sizeof(HT_Item*));

    for (int i = 0; i < ht->size; i++)
        ht->items[i] = NULL;

    return ht;
}

void free_hash_table(HashTable *ht) {
    for (int i = 0; i < ht->size; i++) {
        HT_Item *item = ht->items[i];
        if (item != NULL)
            free_ht_item(item);
    }

    free(ht->items);
    free(ht);
}

void ht_insert(HashTable *ht, char *key, char *value) {
    HT_Item *item = (HT_Item*)malloc(sizeof(HT_Item));
    item->key = key;
    item->value = value;

    ht_hash hash_idx = hash_key(key, ht->size);
    if (ht->items[hash_idx] == NULL) {
        ht->items[hash_idx] = create_ht_item(key, value);
    } else {
        // TODO: resolve collision
    }

    ht->count++;
}

void ht_print(HashTable *ht) {
    int is_empty = 1;
    for (int i = 0; i < ht->size; i++) {
        HT_Item *item = ht->items[i];
        if (item == NULL)
            continue;

        is_empty = 0;
        printf("Index: %d / Key: '%s' / Value: '%s'\n", i, item->key, item->value);
    }

    if (is_empty == 1) {
        printf("Hash Table is empty\n");
    }
}


int main(int argc, char **argv) {
    printf("Creating HashTable\n");
    HashTable *ht = create_hash_table(500);
    printf("Hash table size: %d\n", ht->size);
    printf("Hash table count: %d\n", ht->count);

    ht_hash hash1 = hash_key("Hello bro", 500);
    printf("'Hello bro' hash: %lu\n", hash1);
    ht_hash hash2 = hash_key("Hello world", 500);
    printf("'Hello world' hash: %lu\n", hash2);

    ht_insert(ht, "Hello", "World");
    ht_insert(ht, "Foo", "Bar");
    ht_print(ht);

    free(ht);
    return 0;
}

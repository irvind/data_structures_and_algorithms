#include <stdio.h>
#include <stdlib.h>

typedef struct HT_Item {
    char *key;
    char *value;
} HT_Item;

typedef struct HashTable {
    HT_Item **items;
    int count;
    int size;
} HashTable;


HashTable* create_hash_table(int size) {
    HashTable *ht = (HashTable*)malloc(sizeof(HashTable));
    
    ht->size = size;
    ht->count = 0;
    ht->items = (HT_Item**)calloc(ht->size, sizeof(HT_Item*));
    return ht;
}

void free_hash_table(HashTable *ht) {
    free(ht->items);
    free(ht);
}


int main(int argc, char **argv) {
    printf("Creating HashTable\n");
    HashTable *ht = create_hash_table(500);
    printf("Hash table size: %d\n", ht->size);
    printf("Hash table count: %d\n", ht->count);
    free(ht);
    return 0;
}
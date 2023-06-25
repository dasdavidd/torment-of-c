#include "structures.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// @see https://benhoyt.com/writings/hash-table-in-c/ for reference and even
// some copy-pasta lol

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

typedef struct {
  const char *key;
  void *value;
} ht_entry;

struct ht {
  size_t size;
  size_t capacity;
  ht_entry *items;
};

ht_t *ht_create() {
  ht_t *ht = (ht_t *)malloc(sizeof(ht_t));

  if (ht == NULL) {
    return NULL;
  }
  ht->capacity = INITIAL_CAPACITY;
  ht->size = 0;

  ht->items = calloc(ht->capacity, sizeof(ht_entry));

  if (ht->items == NULL) {
    free(ht);
    return NULL;
  }
  return ht;
}

void ht_destroy(ht_t *ht) {
  for (int i = 0; i < ht->size; i++) {
    free((void *)ht->items[i].value);
  }
  free(ht->items);
  free(ht);
}

size_t ht_length(ht_t *ht) { return ht->size; }

// Return 64-bit FNV-1a hash for key (NUL-terminated). See description:
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
static u_int64_t hash_key(const char *key) {
  u_int64_t hash = FNV_OFFSET;
  for (const char *p = key; *p; p++) {
    hash ^= (u_int64_t)(unsigned char)(*p);
    hash *= FNV_PRIME;
  }
  return hash;
}

size_t index_hash(u_int64_t hash, size_t capacity) {
  return (size_t)(hash & (u_int64_t)(capacity - 1));
}

const char *ht_set_entry(ht_entry *entries, size_t tcapacity, const char *key,
                         void *value, size_t *psize) {
  u_int64_t hash = hash_key(key);
  size_t index = index_hash(hash, tcapacity);
  while (entries[index].key != NULL) {
    // printf("Is position %zu NULL? %d\n", index, entries[index].key == NULL);
    if (strcmp(key, entries[index].key) == 0) {
      entries[index].value = value;
      return entries[index].key;
    }
    index++;
    if (index >= tcapacity) {
      index = 0;
    }
  }

  printf("Key not found in table so we needd to create it\n");

  // INFO: why it's this needed?
  key = strdup(key);

  // `strdup` internally calls `malloc` so we need to check for mem. errors
  if (key == NULL) {
    return NULL;
  }

  entries[index].key = (char *)key;
  entries[index].value = value;

  (*psize)++;

  return key;
}

const char *ht_set(ht_t *ht, const char *key, void *value) {
  if (value == NULL) {
    return NULL;
  }
  // if (ht->size >= ht->capacity / 2) {
  //   if (!ht_expand(ht)) {
  //     return NULL;
  //   }
  // }
  return ht_set_entry(ht->items, ht->capacity, key, value, &ht->size);
}

void *ht_get(ht_t *ht, const char *key) {
  u_int64_t hash = hash_key(key);
  size_t index = index_hash(hash, ht->capacity);

  while (ht->items[index].key != NULL) {
    if (strcmp(key, ht->items[index].key) == 0) {
      return ht->items[index].value;
    }
    index++;
    if (index >= ht->capacity) {
      index = 0;
    }
  }

  return NULL;
}

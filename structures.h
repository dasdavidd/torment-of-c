#include <stdbool.h>
#include <stddef.h>

#define INITIAL_CAPACITY 16

typedef struct ht ht_t;

ht_t *ht_create();

// Return is a pointer to the newly allocated item. Returns NULL if failed to
// allocate memory.
const char *ht_set(ht_t *ht, const char *key, void *value);

void *ht_get(ht_t *ht, const char *key);

void ht_destroy(ht_t *ht);

size_t ht_length(ht_t *ht);

bool ht_expand(ht_t *ht);

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <immintrin.h>

#define ROTL(x, b) (uint64_t)(((x) << (b)) | ((x) >> (64 - (b))))

#define SIPROUND           \
    do {                   \
        v0 += v1;          \
        v1 = ROTL(v1, 13); \
        v1 ^= v0;          \
        v0 = ROTL(v0, 32); \
        v2 += v3;          \
        v3 = ROTL(v3, 16); \
        v3 ^= v2;          \
        v0 += v3;          \
        v3 = ROTL(v3, 21); \
        v3 ^= v0;          \
        v2 += v1;          \
        v1 = ROTL(v1, 17); \
        v1 ^= v2;          \
        v2 = ROTL(v2, 32); \
    } while (0)

// Node data structure
typedef struct Node {
    const char* key;
    int value;
    struct Node* next;
} Node;

// The hash map data structure.
typedef struct HashMap {
    // The number of elements in the hash map.
    size_t size;
    // The capacity of the hash map.
    size_t capacity;
    // The array of linked lists used to store the key-value pairs.
    Node** buckets;
} HashMap;

void hash_map_init(HashMap* map, size_t capacity);
void hash_map_destroy(HashMap* map);
uint32_t hash_siphash(const char* str);
// Alternative simpler hash function.
uint32_t hash_djb2(const char* str);
void hash_map_insert(HashMap* map, const char* key, int value);
int hash_map_lookup(const HashMap* map, const char* key);

int main() {
    // Testing hashmap.
    HashMap map;
    hash_map_init(&map, 8);
    hash_map_insert(&map, "hello", 1);
    hash_map_insert(&map, "world", 2);
    hash_map_insert(&map, "foo", 3);
    hash_map_insert(&map, "bar", 4);
    hash_map_insert(&map, "baz", 5);
    hash_map_insert(&map, "qux", 6);
    hash_map_insert(&map, "quux", 7);
    hash_map_insert(&map, "corge", 8);
    hash_map_insert(&map, "grault", 9);
    hash_map_insert(&map, "garply", 10);
    hash_map_insert(&map, "waldo", 11);
    hash_map_insert(&map, "fred", 12);
    hash_map_insert(&map, "plugh", 13);
    hash_map_insert(&map, "xyzzy", 14);
    hash_map_insert(&map, "thud", 15);

    printf("hello: %d\n", hash_map_lookup(&map, "hello"));
    printf("world: %d\n", hash_map_lookup(&map, "world"));
    printf("foo: %d\n", hash_map_lookup(&map, "foo"));
    printf("bar: %d\n", hash_map_lookup(&map, "bar"));
    printf("baz: %d\n", hash_map_lookup(&map, "baz"));
    printf("qux: %d\n", hash_map_lookup(&map, "qux"));
    printf("quux: %d\n", hash_map_lookup(&map, "quux"));
    printf("corge: %d\n", hash_map_lookup(&map, "corge"));
    printf("grault: %d\n", hash_map_lookup(&map, "grault"));
    printf("garply: %d\n", hash_map_lookup(&map, "garply"));
    printf("waldo: %d\n", hash_map_lookup(&map, "waldo"));
    printf("fred: %d\n", hash_map_lookup(&map, "fred"));
    printf("plugh: %d\n", hash_map_lookup(&map, "plugh"));
    printf("xyzzy: %d\n", hash_map_lookup(&map, "xyzzy"));
    printf("thud: %d\n", hash_map_lookup(&map, "thud"));
    hash_map_destroy(&map);

    return 0;
}

// Initializes a hash map with a given capacity.
void hash_map_init(HashMap* map, size_t capacity) {
    map->size = 0;
    map->capacity = capacity;
    map->buckets = malloc(capacity * sizeof(struct Node*));
    memset(map->buckets, 0, capacity * sizeof(struct Node*));
}

// Cleans up the resources used by a hash map.
void hash_map_destroy(HashMap* map) {
    for (size_t i = 0; i < map->capacity; i++) {
        struct Node* node = map->buckets[i];
        while (node) {
            struct Node* next = node->next;
            free(node);
            node = next;
        }
    }
    free(map->buckets);
}

// Hashes a string using the SipHash-2-4 algorithm. The key is a 128-bit value
// that is used to seed the hash. The key is not secret, but it should be unique
// to the application.
uint32_t hash_siphash(const char* str) {
    // Constants for siphash
    const uint64_t k0 = 0x736f6d6570736575ull;
    const uint64_t k1 = 0x646f72616e646f6dull;

    uint64_t v0 = k0 ^ 0xeece66d5deadbeefull;
    uint64_t v1 = k1 ^ 0xefbeade8deadd00dull;
    uint64_t v2 = k0 ^ 0xfeedfacecafebabeull;
    uint64_t v3 = k1 ^ 0xbeeffeeddeadfaceull;
    const uint8_t* p = (const uint8_t*)str;
    while (p != NULL && *p != '\0') {
        uint64_t m = 0;
        for (int i = 0; i < 8; i++) {
            if (p != NULL) {
                m |= (uint64_t)p[i] << (8 * i);
                p++;
            }
        }
        v3 ^= m;
        SIPROUND;
        SIPROUND;
        v0 ^= m;
    }
    v2 ^= 0xff;
    SIPROUND;
    SIPROUND;
    SIPROUND;
    SIPROUND;
    return (uint32_t)(v0 ^ v1 ^ v2 ^ v3);
}

// Hashes a string using the djb2 algorithm.
uint32_t hash_djb2(const char* str) {
    uint32_t hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    return hash;
}

// Inserts a key-value pair into a hash map.
void hash_map_insert(HashMap* map, const char* key, int value) {
    // Calculate the hash of the key.
    uint32_t hash = hash_siphash(key) % map->capacity;
    // Check if the key is already in the map. If it is, update its value.
    struct Node* node = map->buckets[hash];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            node->value = value;
            return;
        }
        node = node->next;
    }
    // The key is not in the map, so insert it.
    node = malloc(sizeof(struct Node));
    node->key = key;
    node->value = value;
    node->next = map->buckets[hash];
    map->buckets[hash] = node;
    map->size++;
}

// Looks up the value for a given key in a hash map. Returns 0 if the key is not
// found.
int hash_map_lookup(const HashMap* map, const char* key) {
    // Calculate the hash of the key.
    uint32_t hash = hash_siphash(key) % map->capacity;
    // Search for the key in the linked list.
    struct Node* node = map->buckets[hash];
    while (node) {
        if (strcmp(node->key, key) == 0)
            return node->value;
        node = node->next;
    }
    return 0;
}

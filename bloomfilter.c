#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOOM_SIZE 20          // Size of the bit array
#define HASH_FUNCS 2           // Number of hash functions

unsigned char bloom[BLOOM_SIZE];

// Very simple hash functions for illustration
int hash1(const char *str) {
    int hash = 0;
    while (*str)
        hash = (hash * 31 + *str++) % BLOOM_SIZE;
    return hash;
}

int hash2(const char *str) {
    int hash = 7;
    while (*str)
        hash = (hash * 17 + *str++) % BLOOM_SIZE;
    return hash;
}

// Insert a string into the Bloom Filter
void insert(const char *str) {
    bloom[hash1(str)] = 1;
    bloom[hash2(str)] = 1;
}
// Check if the string might be present
int check(const char *str) {
    return bloom[hash1(str)] && bloom[hash2(str)];
}

int main() {
    memset(bloom, 0, sizeof(bloom));

    insert("cat");
    insert("dog");

    // Test present words
    printf("'cat' %s\n", check("cat") ? "maybe present" : "definitely not present");
    printf("'dog' %s\n", check("dog") ? "maybe present" : "definitely not present");

    // Test absent word (could show false positive if unlucky)
    printf("'bat' %s\n", check("bat") ? "maybe present" : "definitely not present");
    printf("'cot' %s\n", check("cot") ? "maybe present" : "definitely not present");

    return 0;
}

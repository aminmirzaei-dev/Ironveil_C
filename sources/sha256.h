#ifndef SHA256_H
#define SHA256_H

#include <stdint.h>
#include <stddef.h>

/*
 * SHA-256 context structure.
 * Holds intermediate state during hashing.
 */
typedef struct {
    uint32_t state[8];   // Hash state
    uint64_t bitlen;     // Total number of processed bits
    uint8_t  data[64];   // Current 512-bit block
    size_t   datalen;    // Number of bytes currently in data[]
} SHA256_CTX;

/* Initialize a SHA-256 context */
void sha256_init(SHA256_CTX *ctx);

/* Process input data */
void sha256_update(SHA256_CTX *ctx, const uint8_t *data, size_t len);

/* Finalize hashing and output 32-byte digest */
void sha256_final(SHA256_CTX *ctx, uint8_t hash[32]);

#endif







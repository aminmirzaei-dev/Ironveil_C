#include "cipher.h"
#include "sha256.h"

/*
 * XOR stream cipher based on SHA-256.
 * Generates a keystream from:
 *   key || nonce || counter
 * and XORs it with the data buffer.
 */
void iv_stream_xor(
    uint8_t *data,
    size_t len,
    const uint8_t *key,
    const uint8_t *nonce
) {
    uint32_t counter = 0;
    uint8_t keystream[32];

    for (size_t i = 0; i < len; i += 32) {
        SHA256_CTX ctx;

        /* Generate keystream block */
        sha256_init(&ctx);
        sha256_update(&ctx, key, 32);
        sha256_update(&ctx, nonce, 16);
        sha256_update(&ctx, (uint8_t *)&counter, sizeof(counter));
        sha256_final(&ctx, keystream);

        /* XOR with plaintext/ciphertext */
        size_t block = (len - i > 32) ? 32 : len - i;
        for (size_t j = 0; j < block; ++j)
            data[i + j] ^= keystream[j];

        counter++;
    }
}



#include "ironveil.h"
#include "cipher.h"
#include "sha256.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAGIC "IVL1"
#define SALT_SIZE  16
#define NONCE_SIZE 16
#define BUFFER_SIZE 4096

/*
 * Generate pseudo-random bytes.
 * NOTE: This is NOT cryptographically strong.
 * Used only for educational purposes.
 */
static void random_bytes(uint8_t *buf, size_t len) {
    for (size_t i = 0; i < len; ++i)
        buf[i] = rand() & 0xFF;
}

/*
 * Derive a 256-bit key from username, password and salt.
 */
static void derive_key(
    const char *user,
    const char *pass,
    const uint8_t *salt,
    uint8_t key[32]
) {
    SHA256_CTX ctx;
    sha256_init(&ctx);
    sha256_update(&ctx, (uint8_t *)user, strlen(user));
    sha256_update(&ctx, (uint8_t *)":", 1);
    sha256_update(&ctx, (uint8_t *)pass, strlen(pass));
    sha256_update(&ctx, salt, SALT_SIZE);
    sha256_final(&ctx, key);
}

int iv_encrypt_file(
    const char *input,
    const char *output,
    const char *username,
    const char *password
) {
    FILE *fin = fopen(input, "rb");
    FILE *fout = fopen(output, "wb");
    if (!fin || !fout) return 0;

    srand((unsigned)time(NULL));

    uint8_t salt[SALT_SIZE];
    uint8_t nonce[NONCE_SIZE];
    uint8_t key[32];

    random_bytes(salt, SALT_SIZE);
    random_bytes(nonce, NONCE_SIZE);
    derive_key(username, password, salt, key);

    /* Write file header */
    fwrite(MAGIC, 1, 4, fout);
    fwrite(salt, 1, SALT_SIZE, fout);
    fwrite(nonce, 1, NONCE_SIZE, fout);

    uint8_t buffer[BUFFER_SIZE];
    size_t len;

    /* Encrypt file content */
    while ((len = fread(buffer, 1, BUFFER_SIZE, fin)) > 0) {
        iv_stream_xor(buffer, len, key, nonce);
        fwrite(buffer, 1, len, fout);
    }

    fclose(fin);
    fclose(fout);
    return 1;
}

int iv_decrypt_file(
    const char *input,
    const char *output,
    const char *username,
    const char *password
) {
    FILE *fin = fopen(input, "rb");
    FILE *fout = fopen(output, "wb");
    if (!fin || !fout) return 0;

    char magic[4];
    fread(magic, 1, 4, fin);
    if (memcmp(magic, MAGIC, 4) != 0)
        return 0;

    uint8_t salt[SALT_SIZE];
    uint8_t nonce[NONCE_SIZE];
    uint8_t key[32];

    fread(salt, 1, SALT_SIZE, fin);
    fread(nonce, 1, NONCE_SIZE, fin);
    derive_key(username, password, salt, key);

    uint8_t buffer[BUFFER_SIZE];
    size_t len;

    /* Decrypt file content */
    while ((len = fread(buffer, 1, BUFFER_SIZE, fin)) > 0) {
        iv_stream_xor(buffer, len, key, nonce);
        fwrite(buffer, 1, len, fout);
    }

    fclose(fin);
    fclose(fout);
    return 1;
}



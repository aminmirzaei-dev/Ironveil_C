#ifndef CIPHER_H
#define CIPHER_H

#include <stdint.h>
#include <stddef.h>

/*
 * Stream cipher function for ironveil.
 *
 * This function generates a keystream using SHA-256 based on:
 *   key (32 bytes) || nonce (16 bytes) || counter (4 bytes)
 * and XORs the keystream with the data buffer in-place.
 *
 * Parameters:
 *   data   - pointer to input/output buffer
 *   len    - length of the buffer
 *   key    - 32-byte master key derived from username/password/salt
 *   nonce  - 16-byte random value for this file encryption
 *
 * Note:
 *   - Same function used for encryption and decryption.
 *   - Counter is incremented for each 32-byte block.
 */
void iv_stream_xor(
    uint8_t *data,
    size_t len,
    const uint8_t *key,
    const uint8_t *nonce
);

#endif



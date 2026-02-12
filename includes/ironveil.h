#ifndef IRONVEIL_H
#define IRONVEIL_H

/*
 * Encrypt a file using username + password.
 * The output file contains a custom header (magic, salt, nonce)
 * followed by encrypted data.
 *
 * Returns 1 on success, 0 on failure.
 */
int iv_encrypt_file(
    const char *input_path,
    const char *output_path,
    const char *username,
    const char *password
);

/*
 * Decrypt a file previously encrypted by ironveil.
 * Username and password must match the encryption inputs.
 *
 * Returns 1 on success, 0 on failure.
 */
int iv_decrypt_file(
    const char *input_path,
    const char *output_path,
    const char *username,
    const char *password
);

#endif



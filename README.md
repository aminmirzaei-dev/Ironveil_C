# Ironveil (File Encryption)

ironveil is a lightweight file encryption library written in pure C.
It is designed for educational and personal projects and does not rely on
any external cryptographic libraries.

> ⚠️ Warning: ironveil is NOT intended to replace industry-standard
cryptography (AES, libsodium, OpenSSL).  
> Use it only for learning, experimentation, or non-critical data.

---

## Features

- Pure C (C99 compatible)
- No external dependencies
- Works with C and C++
- File encryption and decryption
- Username + password based key derivation
- Random salt and nonce per file
- Stream-cipher style encryption
- Simple public API
- Portable across platforms

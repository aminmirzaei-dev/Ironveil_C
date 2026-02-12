#include <iostream>
extern "C" {
    #include "ironveil.h"
}

int main() {
    const char *username = "amin";
    const char *password = "hs3l5ndDF1@$hf"; // Relatively strong password

  // To encrypt a text file
    if (!iv_encrypt_file("document.txt", "document.ivl", username, password)) {
        std::cerr << "❌ Encryption failed" << std::endl;
        return 1;
    }
    std::cout << "✅ File encrypted successfully!" << std::endl;

  // To decrypt a text file
    if (!iv_decrypt_file("document.ivl", "document_decrypted.txt", username, password)) {
        std::cerr << "❌ Decryption failed (wrong username/password?)" << std::endl;
        return 1;
    }
    std::cout << "✅ File decrypted successfully!" << std::endl;

    return 0;
}


#include <stdio.h>
#include "ironveil.h"

int main() {
    const char *username = "amin";
    const char *password = "hs3l5ndDF1@$hf"; // Relatively strong password

  // To encrypt a text file
    if (!iv_encrypt_file("document.txt", "document.ivl", username, password)) {
        printf("Encryption failed\n");
        return 1;
    }
    std::cout << "File encrypted successfully!" << std::endl;

  // To decrypt a text file
    if (!iv_decrypt_file("document.ivl", "document_decrypted.txt", username, password)) {
        printf("Decryption failed (wrong username/password?)\n");
        return 1;
    }
    printf("File decrypted successfully!\n");

    return 0;
}

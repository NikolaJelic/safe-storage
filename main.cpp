#include <iostream>
#include "user.h"
#include "openssl.h"

int main() {
   User nikola {"nikola", "nikola", "jelic",  "lozinka", "nikola@gmail.com", "BA", "RS"};
   nikola.generate_config_file("config.txt");
    Openssl ossl{"."};
    std::cout<< ossl.hash_string("Nikola");
    return 0;
}

#include "utils.h"
#include "user_interface_backend.h"

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--debug") {
            debug = true;
            break;
        }
    }


}
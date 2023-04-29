#include "utils.h"
#include "user_interface_backend.h"

int main(int argc, char* argv[]) {
    // Check the args passed by the user while launching. So far there is only --debug
    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--debug") {
            debug = true;
            break;
        }
    }

    ui_main_menu()

}
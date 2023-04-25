#include "utils.h"
void get_user_input(void) {
    // 
}

string read_user_data(string display_to_user) {
    //this takes a string and displays it to the user, then takes the user input and returns it
    string return_value;
    cout << display_to_user << endl;
    cin >> return_value;
    return return_value;
}
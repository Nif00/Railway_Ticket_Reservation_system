#include "utils.h"
void get_user_input(void){
    // 
}

std::string read_user_data(std::string display_to_user){
    //this takes a string and displays it to the user, then takes the user input and returns it
    std::string return_value;
    std::cout << display_to_user << std::endl;
    std::cin >> return_value;
    return return_value;
    
}



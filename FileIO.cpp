#include "utils.h"
void write_to_file(std::string filename,std::string data){
    std::ofstream current_file;
    current_file.open ("./workspace/"+filename);
    current_file << data;
    current_file.close();
}
void write_to_temp(std::string data){
    //takes a string of data and saves it to a file named "tempfile.csv"
    remove("./temp/Tempfile.csv"); // remove the file before use since we will use the temp file over and over again
    std::ofstream temp_file;
    temp_file.open ("./temp/Tempfile.csv");
    temp_file << data;
    temp_file.close();
}

std::string read_from_file(std::string filename){
    std::string read_data;
    std::ifstream current_file;
    current_file.open ("./workspace/"+filename);
    current_file >> read_data;
    current_file.close();
    return read_data;
}
/*
void delete_file(std::string filename){
    std::filesystem::remove("./workspace/"+filename);
}
*/
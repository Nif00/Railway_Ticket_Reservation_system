#include "utils.h"
/*void write_to_file(string filename, string data) {
    ofstream current_file;
    current_file.open("./workspace/" + filename);
    current_file << data;
    current_file.close();
}
void write_to_temp(string data) {
    //takes a string of data and saves it to a file named "tempfile.csv"
    remove("./temp/Tempfile.csv"); // remove the file before use since we will use the temp file over and over again
    ofstream temp_file;
    temp_file.open("./temp/Tempfile.csv");
    temp_file << data;
    temp_file.close();
}

string read_from_file(string filename) {
    string read_data;
    ifstream current_file;
    current_file.open("./workspace/" + filename);
    current_file >> read_data;
    current_file.close();
    return read_data;
}
/*
void delete_file(string filename){
    filesystem::remove("./workspace/"+filename);
}
*/
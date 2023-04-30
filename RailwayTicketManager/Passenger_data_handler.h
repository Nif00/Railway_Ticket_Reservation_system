#pragma once
#include "utils.h"
struct Passenger {
    long id;
    string name;
    string surname;
    long tckn;
    int age;
};
vector<Passenger> read_passenger_data_from_csv();
void save_passenger_data_to_csv(const Passenger& new_Passenger);
Passenger find_passenger_by_id(long id);
void add_new_passenger();
long read_last_passenger_id();
void dump_passenger_csv_data(int num_lines);
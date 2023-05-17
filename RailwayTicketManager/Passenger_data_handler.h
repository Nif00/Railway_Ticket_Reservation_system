#pragma once
#include "utils.h"

extern string passenger_path;

struct Passenger {
	long id;
	string name;
	string surname;
	long tckn;
	long age;
};

vector<Passenger> read_passenger_data_from_csv();
void save_passenger_data_to_csv(const Passenger& new_Passenger);
Passenger find_passenger_by_id(long id);
Passenger find_passenger_by_name(string name, string surname);
void add_new_passenger();
long read_last_passenger_id();
void dump_passenger_csv_data(long num_lines);
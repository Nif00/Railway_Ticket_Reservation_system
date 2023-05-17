#include "Passenger_data_handler.h"

vector<Passenger> read_passenger_data_from_csv() {
	std::ifstream file(passenger_path);
	std::vector<Passenger> Passengers;

	if (!file.good()) {
		std::ofstream newfile(passenger_path);
		newfile.close();
		file.open(passenger_path);
	}

	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			std::stringstream ss(line);

			Passenger c{};
			if (ss >> c.id) {
				ss.ignore();
				if (ss >> c.name) {
					ss.ignore();
					if (ss >> c.surname) {
						ss.ignore();
						if (ss >> c.tckn) {
							ss.ignore();
							if (ss >> c.age) {
								Passengers.push_back(c);
							}
						}
					}
				}
			}
		}

		file.close();
	}
	else {
		std::cout << "Error: Unable to open file for reading." << std::endl;
	}

	return Passengers;
}

void save_passenger_data_to_csv(const Passenger& new_Passenger) {
	// Open the file for appending
	ofstream file(passenger_path, ios::app);

	// Check if the file is open
	if (file.is_open()) {
		// Write the new Passenger data to the file
		file << new_Passenger.id << ","
			<< new_Passenger.name << ","
			<< new_Passenger.surname << ","
			<< new_Passenger.tckn << ","
			<< new_Passenger.age << ",";

		// Write the end-of-line character to the file
		file << endl;

		// Close the file
		file.close();
	}
	else {
		std::cout << "Error: Unable to open file for writing." << endl;
	}
}

Passenger find_passenger_by_id(long id) {
	vector<Passenger> passengers = read_passenger_data_from_csv();
	for (const auto& p : passengers) {
		if (p.id == id) {
			return p;
		}
	}
	// If no passenger with the given ID is found, return a default campaign with ID -1
	return Passenger{ -1, "", "", -1, -1 };
}

Passenger find_passenger_by_name(string name, string surname) {
	vector<Passenger> passengers = read_passenger_data_from_csv();
	for (const auto& p : passengers) {
		if (p.name == name) {
			if (p.surname == surname) {
				return p;
			}
		}
	}
	// If no passenger with the given ID is found, return a default campaign with ID -1
	return Passenger{ -1, "", "", -1, -1 };
}

void add_new_passenger() {
	long new_passenger_id{ -1 }, tckn{ -1 }, age{ -1 };
	string name, surname;

	new_passenger_id = read_last_passenger_id() + 1;

	std::cout << "Enter Name: ";
	cin >> name;
	std::cout << "Enter Surname: ";
	cin >> surname;
	std::cout << "Enter TCKN: ";
	cin >> tckn;
	std::cout << "Enter Age: ";
	cin >> age;

	Passenger new_passenger{};
	new_passenger.id = new_passenger_id;
	new_passenger.name = name;
	new_passenger.surname = surname;
	new_passenger.tckn = tckn;
	new_passenger.age = age;
	save_passenger_data_to_csv(new_passenger);

	add_log("[Add Passenger] ID: " + to_string(new_passenger_id) + ", Name: " + name + ", Surname: " + surname + ", TCKN: " + to_string(tckn) + ", Age: " + to_string(age));
}

long read_last_passenger_id() {
	vector<Passenger> Passengers = read_passenger_data_from_csv();

	// Check if there are any Passengers in the file
	if (Passengers.empty()) {
		return 0;
	}

	// Get the last Passenger in the vector
	Passenger last_Passenger = Passengers.back();

	// Return the last Passenger's id
	return last_Passenger.id;
}

void dump_passenger_csv_data(long num_lines) {
	// Get the Passengers from the CSV file
	vector<Passenger> Passengers = read_passenger_data_from_csv();

	// Print the specified number of lines
	long lines_printed = 0;
	for (Passenger c : Passengers) {
		// Print the Passenger information
		std::cout << "Passenger ID: " << c.id << endl;
		std::cout << "Passenger Name: " << c.name << endl;
		std::cout << "Passenger Surname: " << c.surname << endl;
		std::cout << "Passenger TC NO:: " << c.tckn << endl;
		std::cout << "Passenger Age: " << c.age << endl;

		std::cout << endl;

		// Increment the number of lines printed and check if we've reached the limit
		lines_printed++;
		if (lines_printed >= num_lines) {
			break;
		}
	}
}

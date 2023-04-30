#include "utils.h"
#include "Passenger_data_handler.h"
#include "trains_data_handler.h"
#include "paths.h"

vector<Passenger> read_passenger_data_from_csv() {
	// Open the file for reading
	ifstream file(passenger_path);

	if (!file.good()) {
		ofstream newfile(passenger_path);
		newfile.close();
		file.open(passenger_path);
	}

	vector<Passenger> Passengers;

	// Check if the file is open
	if (file.is_open()) {
		string line;
		// Read each line of the file
		while (getline(file, line)) {
			// Create a stringstream from the line
			stringstream ss(line);

			// Parse the CSV data into a Passenger struct
			Passenger c;
			ss >> c.id;
			ss.ignore();
			ss >> c.name;
			ss.ignore();
			ss >> c.surname;
			ss.ignore();
			ss >> c.tckn;
			ss.ignore();
			ss >> c.age;
			ss.ignore();

			// Add the Passenger to the vector
			Passengers.push_back(c);
		}

		// Close the file
		file.close();
	}
	else {
		cout << "Error: Unable to open file for reading." << endl;
		Log::add_log("[Save Passenger Data] Error: Unable to open file for writing.");
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
		cout << "Error: Unable to open file for writing." << endl;
	}
}

Passenger find_passenger_by_id(long id) {
	vector<Passenger> passengers = read_passenger_data_from_csv();
	for (const auto& c : passengers) {
		if (c.id == id) {
			return c;
		}
	}
	// If no passenger with the given ID is found, return a default campaign with ID -1
	return Passenger{ -1, "", "", -1, -1 };
}

void add_new_passenger() {
	long new_passenger_id{ -1 }, tckn{ -1 }, age{ -1 };
	string name, surname;
	// Get the train id from user

	new_passenger_id = read_last_passenger_id() + 1;

	cout << "Enter Name: ";
	cin >> name;
	cout << "Enter Surname: ";
	cin >> surname;
	cout << "Enter TCKN: ";
	cin >> tckn;
	cout << "Enter Age: ";
	cin >> age;

	Passenger new_passenger{};
	new_passenger.id = new_passenger_id;
	new_passenger.name = name;
	new_passenger.surname = surname;
	new_passenger.tckn = tckn;
	new_passenger.age = age;
	save_passenger_data_to_csv(new_passenger);

	Log::add_log("[Add Passenger] ID: " + to_string(new_passenger_id) + ", Name: " + name + ", Surname: " + surname + ", TCKN: " + to_string(tckn) + ", Age: " + to_string(age));
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

void dump_passenger_csv_data(int num_lines) {
	if (!debug) return;
	// Get the Passengers from the CSV file
	vector<Passenger> Passengers = read_passenger_data_from_csv();

	// Print the specified number of lines
	int lines_printed = 0;
	for (Passenger c : Passengers) {
		// Print the Passenger information
		cout << "Passenger ID: " << c.id << endl;
		cout << "Passenger Name: " << c.name << endl;
		cout << "Passenger Surname: " << c.surname << endl;
		cout << "Passenger TC NO:: " << c.tckn << endl;
		cout << "Passenger Age: " << c.age << endl;

		cout << endl;

		// Increment the number of lines printed and check if we've reached the limit
		lines_printed++;
		if (lines_printed >= num_lines) {
			break;
		}
	}
}

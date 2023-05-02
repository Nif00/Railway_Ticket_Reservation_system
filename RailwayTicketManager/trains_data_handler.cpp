#include "trains_data_handler.h"

vector<Train> read_train_data_from_csv() {
	// Open the file for reading
	ifstream file(train_path);

	if (!file.good()) {
		ofstream newfile(train_path);
		newfile.close();
		file.open(train_path);
	}

	vector<Train> trains;

	// Check if the file is open
	if (file.is_open()) {
		string line;
		// Read each line of the file
		while (getline(file, line)) {
			// Create a stringstream from the line
			stringstream ss(line);

			// Parse the CSV data into a Train struct
			Train t{};
			ss >> t.id;
			ss.ignore();
			ss >> t.wagonNumber;
			ss.ignore();
			ss >> t.rows;
			ss.ignore();
			ss >> t.columns;
			ss.ignore();
		}

		// Close the file
		file.close();
	}
	else {
		std::cout << "Error: Unable to open file for reading." << endl;
	}

	return trains;
}

void save_train_data_to_csv(const Train& new_Train) {
	// Open the file for appending
	ofstream file(train_path, ios::app);

	// Check if the file is open
	if (file.is_open()) {
		// Write the new Train data to the file
		file << new_Train.id << ","
			<< new_Train.wagonNumber << ","
			<< new_Train.rows << ","
			<< new_Train.columns << ",";

		// Write the end-of-line character to the file
		file << endl;

		// Close the file
		file.close();
	}
	else {
		std::cout << "Error: Unable to open file for writing." << endl;
	}
}

Train find_train_by_id(long id) {
	vector<Train> Trains = read_train_data_from_csv();
	for (const auto& c : Trains) {
		if (c.id == id) {
			return c;
		}
	}
	// If no Train with the given ID is found, return a default Train with ID -1
	return Train{ -1, -1, -1, -1, };
}

int read_last_train_ID() {
	vector<Train> Trains = read_train_data_from_csv();

	// Check if there are any Trains in the file
	if (Trains.empty()) {
		return 0;
	}

	// Get the last Train in the vector
	Train last_Train = Trains.back();

	// Return the last Train's id
	return last_Train.id;
}

void add_new_train() {
	int train_id{ 0 }, row{ 0 }, col{ 0 }, wagonNumber{ 0 };
	std::cout << "Enter the row of seats";
	cin >> row;
	std::cout << "Enter the column of seats";
	cin >> col;
	std::cout << "Enter the number of wagons";
	cin >> wagonNumber;
	Train new_train{};
	new_train.id = read_last_train_ID() + 1;
	new_train.columns = col;
	new_train.rows = row;
	new_train.wagonNumber = wagonNumber;
	save_train_data_to_csv(new_train);
}

void dump_train_csv_data(int num_lines) {
	// Get the Trains from the CSV file
	vector<Train> Trains = read_train_data_from_csv();

	// Print the specified number of lines
	int lines_printed = 0;
	for (Train c : Trains) {
		// Print the Train information
		std::cout << "Train ID: " << c.id << endl;
		std::cout << "Wagon Number: " << c.wagonNumber << endl;
		std::cout << "Rows: " << c.rows << endl;
		std::cout << "Columns: " << c.columns << endl;
		std::cout << "Seats: ";

		// Increment the number of lines printed and check if we've reached the limit
		lines_printed++;
		if (lines_printed >= num_lines) {
			break;
		}
	}
}
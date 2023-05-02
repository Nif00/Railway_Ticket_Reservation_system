#include "campaign_data_handler.h"
#include "log.h"
#include "trains_data_handler.h"

vector<Campaign> read_campaign_data_from_file() {
	// Open the file for reading
	ifstream file(campaign_path);

	if (!file.good()) {
		ofstream newfile(campaign_path);
		newfile.close();
		file.open(campaign_path);
	}

	vector<Campaign> campaigns;

	// Check if the file is open
	if (file.is_open()) {
		string line;
		// Read each line of the file
		while (getline(file, line)) {
			// Create a stringstream from the line
			stringstream ss(line);

			// Parse the CSV data into a Campaign struct
			Campaign c{};
			ss >> c.id;
			ss.ignore();
			ss >> c.assigned_train_id;
			ss.ignore();
			ss >> c.total_seats;
			ss.ignore();
			ss >> c.seats_available;
			ss.ignore();
			ss >> c.departure_time;
			ss.ignore();
			ss >> c.run_duration;
			ss.ignore();
			ss >> c.from;
			ss.ignore();
			ss >> c.to;
			ss.ignore();

			// Read the seat data
			string seat_data;
			getline(ss, seat_data);
			stringstream seat_ss(seat_data);
			vector<Seat> seats;
			while (getline(seat_ss, seat_data, ',')) {
				stringstream seat_data_ss(seat_data);
				Seat s{};
				seat_data_ss >> s.id;
				seat_data_ss.ignore();

				// Convert the column letter to a number
				char col_letter;
				seat_data_ss >> col_letter;
				s.column = col_letter - 'A' + 1;

				seat_data_ss >> s.row;
				seat_data_ss.ignore();
				seat_data_ss >> s.status;
				seats.push_back(s);
			}

			// Assign the vector of seats to the campaign struct
			c.seat = seats;

			// Add the campaign to the vector
			campaigns.push_back(c);
		}

		// Close the file
		file.close();
	}
	else {
		std::cout << "Error: Unable to open file for reading." << endl;
		add_log("[Save Campaign Data] Error: Unable to open file for writing.");
	}

	return campaigns;
}

vector<Campaign> campaigns_by_train(long train_id) {
	vector<Campaign> unsorted_campaigns = read_campaign_data_from_file();
	vector<Campaign> campaigns;

	for (Campaign c : unsorted_campaigns) {
		if (c.assigned_train_id == train_id) {
			campaigns.push_back(c);
		}
	}

	return campaigns;
}


void save_campaign_data_to_csv(const Campaign& new_campaign) {
	// Open the file for appending
	ofstream file(campaign_path, ios::app);

	// Check if the file is open
	if (file.is_open()) {
		// Write the new campaign data to the file
		file << new_campaign.id << ","
			<< new_campaign.assigned_train_id << ","
			<< new_campaign.total_seats << ","
			<< new_campaign.seats_available << ","
			<< new_campaign.departure_time << ","
			<< new_campaign.run_duration << ",";

		// Write the seat data to the file
		for (const Seat& s : new_campaign.seat) {
			file << s.id << "|"
				<< s.row << "|"
				<< s.column << "|"
				<< s.status << ",";
		}

		// Write the end-of-line character to the file
		file << endl;

		// Close the file
		file.close();
	}
	else {
		std::cout << "Error: Unable to open file for writing." << endl;
	}
}

int count_booked_seats(const vector<Campaign>& campaign) {
	int total_booked_seats = 0;
	for (const Campaign& c : campaign) {
		for (const Seat& s : c.seat) {
			if (s.status == 1) {
				total_booked_seats++;
			}
		}
	}
	return total_booked_seats;
}

Campaign find_campaign_by_id(long id) {
	vector<Campaign> campaigns = read_campaign_data_from_file();
	for (const auto& c : campaigns) {
		if (c.id == id) {
			return c;
		}
	}
	// If no campaign with the given ID is found, return a default campaign with ID -1
	return Campaign{ -1, -1, -1, -1, "", "", "", "",vector<Seat>{} };
}

Seat find_seat_by_id(long campaign_id, int seat_id) {
	Campaign campaign = find_campaign_by_id(campaign_id);
	vector<Seat> seats;
	for (const auto& s : seats) {
		if (s.id == seat_id) {
			return s;
		}
	}
	return Seat{ -1, -1, -1, -1 };
}

void update_seat(long seat_id, long campaign_id, int status) {
	Seat seat = find_seat_by_id(campaign_id, seat_id);
	vector<Campaign> campaigns = read_campaign_data_from_file();
	for (auto& c : campaigns) {
		if (c.id == campaign_id) {
			for (auto& s : c.seat) {
				if (s.id == seat_id) {
					s.status = status;
					break;
				}
			}
			save_campaign_data_to_csv(c);
			break;
		}
	}
}


long read_last_campaign_id() {
	vector<Campaign> campaigns = read_campaign_data_from_file();

	// Check if there are any campaigns in the file
	if (campaigns.empty()) {
		return 0;
	}

	// Get the last campaign in the vector
	Campaign last_campaign = campaigns.back();

	// Return the last campaign's id
	return last_campaign.id;
}



void dump_campaign_csv_data(long num_lines) {
	// Get the campaigns from the CSV file
	vector<Campaign> campaigns = read_campaign_data_from_file();

	// Print the specified number of lines
	long lines_printed = 0;
	for (Campaign c : campaigns) {
		// Print the campaign information
		std::cout << "Campaign ID: " << c.id << endl;
		std::cout << "Assigned Train ID: " << c.assigned_train_id << endl;
		std::cout << "Total Seats: " << c.total_seats << endl;
		std::cout << "Seats Available: " << c.seats_available << endl;
		std::cout << "Departure Time: " << c.departure_time << endl;
		std::cout << "Run Duration: " << c.run_duration << endl;
		std::cout << "Seats: ";
		for (Seat s : c.seat) {
			std::cout << "[" << s.id << ", " << s.row << ", " << s.column << ", " << s.status << "] ";
		}
		std::cout << endl;

		// Increment the number of lines printed and check if we've reached the limit
		lines_printed++;
		if (lines_printed >= num_lines) {
			break;
		}
	}
}
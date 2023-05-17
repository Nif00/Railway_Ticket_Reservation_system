#include "Ticket_data_handler.h"
#include "log.h"
#include "campaign_data_handler.h"
#include "Passenger_data_handler.h"

vector<Ticket> read_ticket_data_from_csv() {
	std::ifstream file(ticket_path);
	std::vector<Ticket> tickets;

	if (!file.good()) {
		std::ofstream newfile(ticket_path);
		newfile.close();
		file.open(ticket_path);
	}

	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			std::stringstream ss(line);

			Ticket t{};
			if (ss >> t.id) {
				ss.ignore();
				if (ss >> t.type) {
					ss.ignore();
					if (ss >> t.assigned_campaign_id) {
						ss.ignore();
						if (ss >> t.assigned_passenger_id) {
							ss.ignore();
							if (ss >> t.assigned_seat_id) {
								tickets.push_back(t);
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

	return tickets;
}

void save_ticket_data_to_csv(const Ticket& new_ticket) {
	// Open the file for appending
	ofstream file(ticket_path, ios::app);

	// Check if the file is open
	if (file.is_open()) {
		// Write the new ticket data to the file
		file << new_ticket.id << ","
			<< new_ticket.type << ","
			<< new_ticket.assigned_campaign_id << ","
			<< new_ticket.assigned_passenger_id << ","
			<< new_ticket.assigned_seat_id << ",";

		// Write the end-of-line character to the file
		file << endl;

		// Close the file
		file.close();
	}
	else {
		std::cout << "Error: Unable to open file for writing." << endl;
		add_log("[Save Ticket Data] Error: Unable to open file for writing.");
	}
}

long get_ticket_type(long id) {
	Ticket ticket = find_ticket_by_id(id);
	return ticket.type;
}

Ticket find_ticket_by_id(long id) {
	vector<Ticket> tickets = read_ticket_data_from_csv();
	for (const auto& t : tickets) {
		if (t.id == id) {
			return t;
		}
	}
	// If no ticket with the given ID is found, return a default ticket with ID -1
	return Ticket{ -1, -1, -1, -1, -1 };
}

long read_last_ticket_id() {
	vector<Ticket> tickets = read_ticket_data_from_csv();

	// Check if there are any tickets in the file
	if (tickets.empty()) {
		return 0;
	}

	// Get the last ticket in the vector
	Ticket last_ticket = tickets.back();

	// Return the last ticket's id
	return last_ticket.id;
}

void add_new_ticket() {
	long type, assigned_campaign_id, assigned_passenger_id, assigned_seat_id, new_ticket_id;
	// Get the train id from user
	vector<Seat> seat{};
	assigned_campaign_id = 1;//ui_campaign_selector();
	assigned_passenger_id = 1;// ui_passenger_selector();
	assigned_seat_id = 1;//ui_seat_selector(assigned_campaign_id);
	Passenger passenger = { 1,"sir deez","nuts",1111111,69 };//find_passenger_by_id(assigned_passenger_id);

	if (passenger.age <= 18) type = 2;
	if (passenger.age > 65) type = 3;

	new_ticket_id = read_last_ticket_id() + 1;
	Ticket new_ticket{};
	new_ticket.id = new_ticket_id;
	new_ticket.type = type;
	new_ticket.assigned_campaign_id = assigned_campaign_id;
	new_ticket.assigned_passenger_id = assigned_passenger_id;
	new_ticket.assigned_seat_id = assigned_seat_id;
	save_ticket_data_to_csv(new_ticket);
	add_log("[Add Ticket] " + to_string(new_ticket_id) + ", Type: " + to_string(type) + ", Campaign ID: " + to_string(assigned_campaign_id) + ", Passenger ID: " + to_string(assigned_passenger_id) + ", Seat ID: " + to_string(assigned_seat_id));
}

void dump_ticket_csv_data(long num_lines) {
	// Get the tickets from the CSV file
	vector<Ticket> tickets = read_ticket_data_from_csv();

	// Print the specified number of lines
	long lines_printed = 0;
	for (Ticket t : tickets) {
		// Print the ticket information
		std::cout << "Ticket ID: " << t.id << endl;
		std::cout << "Type: " << t.type << endl;
		std::cout << "Assigned Campaign ID: " << t.assigned_campaign_id << endl;
		std::cout << "Assigned Passenger ID: " << t.assigned_passenger_id << endl;

		// Increment the number of lines printed and check if we've reached the limit
		lines_printed++;
		if (lines_printed >= num_lines) {
			break;
		}
	}
}
#include "utils.h"
#include "campaign_data_handler.h"

vector<Campaign> read_campaign_data_from_csv() {
    // Open the file for reading
    ifstream file("campaign_data.csv");

    if (!file.good()) {
        ofstream newfile("campaign_data.csv");
        newfile.close();
        file.open("campaign_data.csv");
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
            Campaign c;
            ss >> c.id;
            ss.ignore();
            ss >> c.assigned_train_id;
            ss.ignore();
            ss >> c.total_seats;
            ss.ignore();
            ss >> c.seats_available;
            ss.ignore();

            // Read the seat data
            string seat_data;
            getline(ss, seat_data);
            stringstream seat_ss(seat_data);
            vector<Seat> seats;
            while (getline(seat_ss, seat_data, ',')) {
                stringstream seat_data_ss(seat_data);
                Seat s;
                seat_data_ss >> s.id;
                seat_data_ss.ignore();
                seat_data_ss >> s.row;
                seat_data_ss.ignore();
                seat_data_ss >> s.column;
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
        cout << "Error: Unable to open file for reading." << endl;
    }

    return campaigns;
}

void save_campaign_data_to_csv(const Campaign& new_campaign) {
    // Open the file for appending
    ofstream file("campaign_data.csv", ios::app);

    // Check if the file is open
    if (file.is_open()) {
        // Write the new campaign data to the file
        file << new_campaign.id << ","
            << new_campaign.assigned_train_id << ","
            << new_campaign.total_seats << ","
            << new_campaign.seats_available << ",";

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
        cout << "Error: Unable to open file for writing." << endl;
    }
}


void print_csv_lines(int num_lines) {
    if (!debug) {
        cout << "only available in --debug mode";
        return;
    }
    // Get the campaigns from the CSV file
    vector<Campaign> campaigns = read_campaign_data_from_csv();

    // Print the specified number of lines
    int lines_printed = 0;
    for (Campaign c : campaigns) {
        // Print the campaign information
        cout << "Campaign ID: " << c.id << endl;
        cout << "Assigned Train ID: " << c.assigned_train_id << endl;
        cout << "Total Seats: " << c.total_seats << endl;
        cout << "Seats Available: " << c.seats_available << endl;
        cout << "Seats: ";
        for (Seat s : c.seat) {
            cout << "[" << s.id << ", " << s.row << ", " << s.column << ", " << s.status << "] ";
        }
        cout << endl;

        // Increment the number of lines printed and check if we've reached the limit
        lines_printed++;
        if (lines_printed >= num_lines) {
            break;
        }
    }
}

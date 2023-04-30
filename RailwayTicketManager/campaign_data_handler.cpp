#include "utils.h"
#include "campaign_data_handler.h"
#include "trains_data_handler.h"

vector<Campaign> read_campaign_data_from_csv() {
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
    ofstream file(campaign_path, ios::app);

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

int count_booked_seats(const vector<Campaign>& campaigns) {
    int total_booked_seats = 0;
    for (const Campaign& c : campaigns) {
        for (const Seat& s : c.seat) {
            if (s.status == 1) {
                total_booked_seats++;
            }
        }
    }
    return total_booked_seats;
}

Campaign find_campaign_by_id(int id) {
    vector<Campaign> campaigns = read_campaign_data_from_csv();
    for (const auto& c : campaigns) {
        if (c.id == id) {
            return c;
        }
    }
    // If no campaign with the given ID is found, return a default campaign with ID -1
    return Campaign{ -1, -1, -1, -1, vector<Seat>{} };
}

int read_last_id() {
    vector<Campaign> campaigns = read_campaign_data_from_csv();

    // Check if there are any campaigns in the file
    if (campaigns.empty()) {
        return 0;
    }

    // Get the last campaign in the vector
    Campaign last_campaign = campaigns.back();

    // Return the last campaign's id
    return last_campaign.id;
}

void add_new_campaign() {
    int train_id, total_seats, seats_available;
    // Get the train id from user
    train_id = ui_train_selector();
    Train train;
    // Find the train by id
    train = find_train_by_id(train_id);
    total_seats = (train.columns * train.rows) * train.wagonNumber;
    // We are initialising an empty train
    seats_available = total_seats;

    Campaign new_campaign;
    new_campaign.id = read_last_id() + 1;
    new_campaign.assigned_train_id = train.id;
    new_campaign.total_seats = total_seats;
    new_campaign.seats_available = seats_available;
    vector<Seat> seats;
    // Explanation: 
    // This code handles all the necesary seat labeling, depending on the ammount of columns in the train
    // it will create empty seats. It will also create ids based on their row and col. Example output:
    // 1A,1B,1C,1D,2A,2B...
    for (int row = 1; row <= train.rows; row++) {
        for (char col = 'A'; col < ('A' + train.columns); col++) {
            Seat seat;
            seat.id = row * train.columns + (col - 'A') + 1;
            seat.row = row;
            seat.column = col;
            seat.status = 1;
            seats.push_back(seat);
        }
    }
    new_campaign.seat = seats;
    save_campaign_data_to_csv(new_campaign);
}

void dump_campaign_csv_data(int num_lines) {
    if (!debug) return;
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
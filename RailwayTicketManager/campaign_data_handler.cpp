#include "utils.h"
#include "campaign_data_handler.h"

vector<Campaign> read_from_csv() {
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
            while (getline(seat_ss, seat_data, '|')) {
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

void save_to_csv(const Campaign& new_campaign) {
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
/*
string read_campaign_data_file() {
    ifstream file("campaign.csv");

    // Check if the file exists, if not create it
    if (!file.good()) {
        ofstream newfile("./workspace/campaign.csv");
        newfile.close();
        file.open("./workspace/campaign.csv");
    }
    vector<Campaign> campaigns;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id_str, assigned_train_id_str, total_seats_str, seats_available_str;
        getline(ss, id_str, ',');
        getline(ss, assigned_train_id_str, ',');
        getline(ss, total_seats_str, ',');
        getline(ss, seats_available_str, ',');

        int id = stoi(id_str);
        int assigned_train_id = stoi(assigned_train_id_str);
        int total_seats = stoi(total_seats_str);
        int seats_available = stoi(seats_available_str);

        Campaign campaign = { id, assigned_train_id, total_seats, seats_available };

        string seat_id_str, seat_row_str, seat_column_str, seat_status_str;
        while (getline(ss, seat_id_str, ',')) {
            getline(ss, seat_row_str, ',');
            getline(ss, seat_column_str, ',');
            getline(ss, seat_status_str, ',');

            // Convert the string data to integers
            int seat_id = stoi(seat_id_str);
            int seat_row = stoi(seat_row_str);
            int seat_column = stoi(seat_column_str);
            int seat_status = stoi(seat_status_str);

            // Create a new Seat and add it to the Campaign
            Seat seat = { seat_id, seat_row, seat_column, seat_status };
            campaign.seat.push_back(seat);
        }
    campaigns.push_back(campaign);
    }
}
*/
#include "utils.h"
#include "trains_data_handler.h"
/*
// Create a train struct with a unique ID
int createID() {
    // Set up random seed for unique IDs
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    // Create an unordered set to keep track of generated IDs
    unordered_set<int> generated_ids;

    // Generate IDs until a unique one is found
    while (true) {
        int id = 10000 + generator() % 90000; // Generate ID between 10000 and 99999
        if (generated_ids.find(id) == generated_ids.end()) { // Check if ID is unique
            generated_ids.insert(id); // Add ID to set of generated IDs
            return id; // Return unique ID
        }
    }
}

int createWagon() {
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    // Create an unordered set to keep track of generated IDs
    unordered_set<int> generated_wagons;

    // Generate wagonNumber until a unique one is found
    while (true) {
        int wagonNumber = 4 + generator() % 4; // Generate wagonNumber between 4 and 7
        if (generated_wagons.find(wagonNumber) == generated_wagons.end()) { // Check if ID is unique
            generated_wagons.insert(wagonNumber); // Add ID to set of generated IDs
            return wagonNumber; // Return unique ID
        }
    }
}
*/
//


/*
vector <Train> settingTrain(int train_Number) {
    vector <Train> v;
    //creates trains based on count of train_Number
    for (int i = 0; i < train_Number; i++) {
        Train t;
        t.id = createID();
        t.wagonNumber = createWagon();
        cin >> t.selectedWagon >> t.block >> t.seatNumber[i];
        v.push_back(t);
    }
    // Open a file for writing
    ofstream file("train.csv");

    // Write the data rows to the file
    for (const auto& record : v) {
        for(int i = 0; i < train_Number; i++)
            file << record.id << "," << record.wagonNumber << "," << record.selectedWagon << "," << record.block << "," << record.seatNumber[i] << endl;
    }
    // Close the file
    file.close();
} */

vector<Train> read_Train_data_from_csv() {
    // Open the file for reading
    ifstream file(train_path);

    if (!file.good()) {
        ofstream newfile(train_path);
        newfile.close();
        file.open(train_path);
    }

    vector<Train> Trains;

    // Check if the file is open
    if (file.is_open()) {
        string line;
        // Read each line of the file
        while (getline(file, line)) {
            // Create a stringstream from the line
            stringstream ss(line);

            // Parse the CSV data into a Train struct
            Train c;
            ss >> c.id;
            ss.ignore();
            ss >> c.wagonNumber;
            ss.ignore();
            ss >> c.rows;
            ss.ignore();
            ss >> c.columns;
            ss.ignore();
        }

        // Close the file
        file.close();
    }
    else{
        cout << "Error: Unable to open file for reading." << endl;
    }

    return Trains;
}

void save_Train_data_to_csv(const Train & new_Train) {
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
        cout << "Error: Unable to open file for writing." << endl;
    }
}

Train find_Train_by_id(int id) {
    vector<Train> Trains = read_Train_data_from_csv();
    for (const auto& c : Trains) {
        if (c.id == id) {
            return c;
        }
    }
    // If no Train with the given ID is found, return a default Train with ID -1
    return Train{ -1, -1, -1, -1,};
}

int read_last_Train_ID() {
    vector<Train> Trains = read_Train_data_from_csv();

    // Check if there are any Trains in the file
    if (Trains.empty()) {
        return 0;
    }

    // Get the last Train in the vector
    Train last_Train = Trains.back();

    // Return the last Train's id
    return last_Train.id;
}

void add_new_Train() {
    int train_id, total_seats, seats_available;
    // Get the train id from user
    train_id = ui_train_selector();
    Train train;
    // Find the train by id
    train = find_Train_by_id(train_id);
    // We are initialising an empty train
    seats_available = total_seats;

    Train new_Train;
    new_Train.id = read_last_Train_ID() + 1;
    save_Train_data_to_csv(new_Train);
}

void dump_Train_csv_data(int num_lines) {
    if (!debug) return;
    // Get the Trains from the CSV file
    vector<Train> Trains = read_Train_data_from_csv();

    // Print the specified number of lines
    int lines_printed = 0;
    for (Train c : Trains) {
        // Print the Train information
        cout << "Train ID: " << c.id << endl;
        cout << "Wagon Number: " << c.wagonNumber << endl;
        cout << "Rows: " << c.rows << endl;
        cout << "Columns: " << c.columns << endl;
        cout << "Seats: ";
        
        // Increment the number of lines printed and check if we've reached the limit
        lines_printed++;
        if (lines_printed >= num_lines) {
            break;
        }
    }
}

/*vector <Train> readTrain(int train_Number) {

    // Open the file for reading
    ifstream file("train.csv");

    // Read the data rows and store them in a vector of Record objects
    vector <Train> data;
    string line;
    while (getline(file, line)) {
        // Use a stringstream to split the line into columns
        stringstream ss(line);
        string id_str, wagonNum_str;     ////////////////////////////////ADD OTHER VARIABLES
        getline(ss, id_str, ',');
        getline(ss, wagonNum_str, ',');



        // Convert the id and wagonNum column from string to int
        int id = stoi(wagonNum_str);
        int wagonNum = stoi(wagonNum_str);

        // Create a new Record object and add it to the data vector
        data.push_back({ id, wagonNum });
    }

    // Close the file
    file.close();
}*/
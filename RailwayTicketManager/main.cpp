#include "utils.h"
#include "user_interface_backend.h"
#include "Ticket_data_handler.h"
#include "Passenger_data_handler.h"
#include "campaign_data_handler.h"
#include "trains_data_handler.h"

string train_path = "/workspace/train_data.csv";
string ticket_path = "/workspace/ticket_data.csv";
string campaign_path = "/workspace/campaign_data.csv";
string passenger_path = "/workspace/passenger_data.csv";

bool debug = false;
bool admin = false;
bool logging_disabled= false;

void first_time_setup() {
	add_log("Detected first time running program. Running first time setup");

	ofstream campaign_file(campaign_path);
	campaign_file.close();
	add_log("Created campaign_data.csv");

	ofstream train_file(train_path);
	train_file.close();
	add_log("Created train_data.csv");

	ofstream passenger_file(passenger_path);
	passenger_file.close();
	add_log("Created passenger_data.csv");

	ofstream ticket_file(ticket_path);
	ticket_file.close();
	add_log("Created ticket_data.csv");

	add_log("Setup complete. All necessary files created.");
}

int main(int argc, char* argv[]) {
	// Check the args passed by the user while launching. So far there is only --debug and --admin
	for (int i = 1; i < argc; i++) {
		if (string(argv[i]) == "--debug") {
			debug = true;
			break;
		}
	}
	for (int i = 1; i < argc; i++) {
		if (string(argv[i]) == "--admin") {
			admin = true;
			break;
		}
	}
	for (int i = 1; i < argc; i++) {
		if (string(argv[i]) == "--nolog") {
			logging_disabled = true;
			break;
		}
	}
	// Check if we have a log.txt to see if this is the first time we are running the program
	ifstream file("log.txt");
	if (!file.good()) first_time_setup();
	add_log("----------------");
	while (true) {
		ui_main_menu();
	}
}
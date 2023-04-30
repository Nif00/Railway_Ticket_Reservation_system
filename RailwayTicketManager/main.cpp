#include "utils.h"
#include "user_interface_backend.h"

void first_time_setup() {
	Log::add_log("Detected first time running program. Running first time setup");

	ofstream campaign_file(campaign_path);
	campaign_file.close();
	Log::add_log("created campaign_data.csv");

	ofstream train_file(train_path);
	train_file.close();
	Log::add_log("created train_data.csv");

	ofstream passenger_file(passenger_path);
	passenger_file.close();
	Log::add_log("created passenger_data.csv");

	ofstream ticket_file(ticket_path);
	ticket_file.close();
	Log::add_log("created ticket_data.csv");

	Log::add_log("Setup complete. All necessary files created.");
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
	Log::add_log("----------------");




	ui_main_menu();

}
#include "log.h"


void Log::add_log(const string& message) {
	if (logging_disabled) return;

	// Get the current time
	auto now = chrono::system_clock::now();
	time_t current_time = chrono::system_clock::to_time_t(now);

	// Convert the time to a string
	string time_string = ctime(&current_time);
	time_string.erase(time_string.length() - 1);

	// Write the message to the log file
	ofstream log_file("log.txt", ios_base::app);
	log_file << "[" << time_string << "] " << message << endl;
	log_file.close();
}

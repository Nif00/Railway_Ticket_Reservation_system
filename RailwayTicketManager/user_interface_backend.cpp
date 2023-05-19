#include <Windows.h>
#include "user_interface_backend.h"


void color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y)
{
	COORD c{};
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

long ui_campaign_selector(vector<Campaign> campaigns)
{
	int Set[] = { 7,7,7 }; //7 is 
	long counter = 2;
	char key;
	std::cout << "Please choose a campaign" << endl;
	for (long i = 0;;)
	{
		for (Campaign c : campaigns)
		{
			gotoxy(10, c.id + 5);
			color(Set[c.id == counter]);
			std::cout << c.id;
		}
		key = _getch();
		if (key == 72 && (counter >= 1 && counter <= campaigns.size()))
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= campaigns.size()))
		{
			counter++;

		}
		if (key == '\r')
		{
			for (Campaign c : campaigns)
			{
				if (counter == c.id)
				{
					return c.id;
				}
			}
		}
	}
}

long ui_train_selector(vector<Train> trains)
{
	int Set[] = { 7,7,7 };
	long counter = 2;
	char key;
	std::cout << "Please choose a train: \n" << endl;
	for (long i = 0;;)
	{
		for (Train t : trains)
		{
			gotoxy(10, t.id + 5);
			color(Set[t.id == counter]);
			std::cout << t.id;
		}
		key = _getch();
		if (key == 72 && (counter >= 1 && counter <= trains.size()))
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= trains.size()))
		{
			counter++;

		}
		if (key == '\r')
		{
			for (Train t : trains)
			{
				if (counter == t.id)
				{
					return t.id;
				}
			}
		}
	}
}


long ui_ticket_selector(vector<Ticket> tickets)
{
	int Set[] = { 7,7,7 };
	long counter = 2;
	char key;
	std::cout << "Please choose a train: \n" << endl;
	for (long i = 0;;)
	{
		for (Ticket t : tickets)
		{
			gotoxy(10, t.id + 5);
			color(Set[t.id == counter]);
			std::cout << t.id;
		}
		key = _getch();
		if (key == 72 && (counter >= 1 && counter <= tickets.size()))
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= tickets.size()))
		{
			counter++;

		}
		if (key == '\r')
		{
			for (Ticket t : tickets)
			{
				if (counter == t.id)
				{
					return t.id;
				}
			}
		}
	}
}

long ui_passenger_selector()
{
	long passenger_id;
	string name, surname;
	std::cout << "Enter your Passeneger ID, If you do not know your Passenger ID enter -1";
	std::cin >> passenger_id;
	if (passenger_id == -1) {
		std::cout << "Enter your name";
		std::cin >> name;
		std::cout << "Enter your surname";
		std::cin >> surname;
		Passenger selected_passenger = find_passenger_by_name(name, surname);
		return selected_passenger.id;
	}
	else return passenger_id;
}
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
void seperator() {
	string a0 = "Please enter the seat that you wish to buy (e.g. A01)";
	string h(2 * a0.length(), '\xdb');
	color(12);
cout <<"\n\n" << h;	cout << endl << endl;

	color(7);
}
void display_seat() {
	system("cls");
	vector<Campaign> campaigns = read_from_csv();
	//Write Logic here to select campaign
	for (Campaign c : campaigns)
	{
	seperator();
		std::cout << "   Campaign ID: " << c.id << endl;
		std::cout << "   Assigned Train ID: " << c.assigned_train_id << endl;
		std::cout << "   Total Seats: " << c.total_seats << endl;
		std::cout << "   Seats Available: " << c.seats_available;
		seperator();
		color(12);
		cout << "\t\t\t\tSeats:" << endl<<endl;
		color(7);

		int k = 0;
		if (k == 0)
		{
			color(12);
			std::cout <<"\t";
			color(7);
		}
		for (Seat s : c.seat)
		{
			k++;
			char seatColumn = 't';
			switch (s.column)
			{
			case 0:
				seatColumn = 'A';
				break;
			case 1:
				seatColumn = 'B';
				break;
			case 2:
				seatColumn = 'C';
				break;
			case 3:
				seatColumn = 'D';
				break;
			default:
				break;
			}
			std::cout << "\t";
			if (s.status == 1)
			{
				if (s.row < 9)
				{
					std::cout << "\xdb" << seatColumn << "0" << s.row + 1 << "\xdb ";
				}
				else
				{
					std::cout << "\xdb" << seatColumn << s.row + 1 << "\xdb ";
				}
			}
			else if (s.status == 3)
			{
				color(14);
				std::cout << "\xdb\xb2\xb2\xb2\xdb ";
				color(7);
			}
			if (k % 2 == 0)
			{
				if (k % 4 == 0)
				{
					switch (s.row)
					{
					case 1:
						color(12);
						std::cout << "\t\t\x1e";
						break;
						color(7);
					case 2:
						color(12);
						std::cout << "\t\t\xba\   Direction";
						color(7);
						color(14);
						cout << "\t \xdb\xb2\xb2\xb2\xdb ";
						color(7);
						cout << " = Occupied";
						break;
					case 3:
						color(12);
						std::cout << "\t\t\xba";
						color(7);
						break;
					default:
						break;
					}

				}
				std::cout << "\t";
			}
			if (k % 4 == 0 && k < c.seats_available)
			{
				color(12);
				std::cout << endl << endl << "\t";
				color(7);
			}
		}
		if (k % 5 == 0)
		{
			std::cout << "\t";
		}
	}

}


void selectSeat() {
	system("cls");
	vector<Campaign> campaigns = read_from_csv();
	int Set[] = { 7,7,7,7 };   //Default colors, White
	int counter = 3;
	for (Campaign c : campaigns) {
		char inpN; int inpS; int inpSN, seatNoID = 4; bool valid_seat_request = false; bool seat_occupied = false; string a0 = "Please enter the seat that you wish to buy (e.g. A01)";
		string h(2 * a0.length(), '\xdb');
		while (!valid_seat_request)
		{
			bool reselect = false;
			while (!reselect)
			{
				bool seat_occupied = false;
				display_seat();
				seperator();
				cout << "\tPlease enter the seat that you wish to buy (e.g. A01)" << endl;
				color(8);
				cout <<endl<< "\t\t(Scroll up to view available seats)";
				color(7);
				seperator();
				std::cin >> inpN >> inpS;
				switch (inpN)
				{
				case 'A':
					inpSN = 0;
					break;
				case 'B':
					inpSN = 1;
					break;
				case 'C':
					inpSN = 2;
					break;
				case 'D':
					inpSN = 3;
					break;
				case 'a':
					inpSN = 0;
					break;
				case 'b':
					inpSN = 1;
					break;
				case 'c':
					inpSN = 2;
					break;
				case 'd':
					inpSN = 3;
					break;
				default:
					inpSN = 4;
				}
				int selectedSeat[3];
				for (Seat s : c.seat)

				{
					if (s.column == inpSN && s.row + 1 == inpS && s.status == 1) {
						selectedSeat[0] = inpSN;
						selectedSeat[1] = inpS;
						selectedSeat[2] = seatNoID;
					}
					if (s.column == inpSN && s.row + 1 == inpS && s.status == 3) {
						seat_occupied = true;
					}
				}
				if (inpSN > 3 || inpS * 4 > c.total_seats || seat_occupied || inpS<1)

				{
					system("cls");
					seperator();
					cout << "\tSeat couldn't be found or the seat is occupied, please try again";
					color(12);
					cout << endl<< "\n\t\tPress any button to countinue";
					color(7);
					seperator();
					_getch();
					inpSN = 4;
				}
				else
				{
					reselect = true;
				}
			}
			//cout << "reselect: " << reselect << "seat occupied: " << seat_occupied<< endl;
			int wish_to_proceed;
			system("cls");
			seperator();
			cout << endl << "\tIf you want to reselect your seat enter 1 if not enter anything else" << endl;
			seperator();
			std::cin >> wish_to_proceed;
			if (wish_to_proceed == 1)
			{
				//cout << "reselect: " << reselect << "seat occupied: " << seat_occupied << endl;
				valid_seat_request = false;
				continue;
			}
			else
			{
				system("cls");
				seperator();
				cout << "\tYour seat will be displayed as: ";
				color(12);
			cout << "\xdb" << "XXX" << "\xdb ";
			color(7);
			color(12);
			cout << endl <<endl<< "\t\t\tPress any button to countinue";
			color(7);
			seperator();
				_getch();
				system("cls");
				for (Campaign c : campaigns)
				{
					system("cls");
					seperator();
					color(12);
					cout << "\t\t\t\tSeats:" << endl << endl;
					color(7);
					int k = 0;
					if (k == 0)
					{
						color(12);
						cout <<"\t";
						color(7);

					}
					for (Seat s : c.seat)
					{
						k++;
						char seatColumn = 't';
						switch (s.column)
						{
						case 0:
							seatColumn = 'A';
							break;
						case 1:
							seatColumn = 'B';
							break;
						case 2:
							seatColumn = 'C';
							break;
						case 3:
							seatColumn = 'D';
							break;
						default:
							break;
						}
						cout << "\t";
						if (s.column == inpSN && s.row + 1 == inpS && s.status == 1) {
							color(12);
							cout << "\xdb" << "XXX" << "\xdb ";
							color(7);
						}
						else if (s.status == 1)
						{
							if (s.row < 9)
							{
								cout << "\xdb" << seatColumn << "0" << s.row + 1 << "\xdb ";
							}
							else
							{
								cout << "\xdb" << seatColumn << s.row + 1 << "\xdb ";
							}
						}
						else if (s.status == 3)
						{
							color(14);
							cout << "\xdb\xb2\xb2\xb2\xdb ";
							color(7);
						}
						if (k % 2 == 0)
						{
							if (k % 4 == 0)
							{
								switch (s.row)
								{
								case 0:
									color(12);
									cout << "\t\t\xdbXXX\xdb";
									color(7);
									cout<< " = Selected Seat";
								case 1:
									color(12);
									cout << "\t\t\x1e";
									color(7);
									break;
								case 2:
									color(12);
									cout << "\t\t\xba   Direction";
									color(7);
									break;
								case 3:
									color(12);
									cout << "\t\t\xba";
									color(7);
									break;
								default:
									break;
								}

							}
							cout << "\t";
						}
						if (k % 4 == 0 && k < c.seats_available)
						{
							color(12);
							cout << endl << endl << "\t";
							color(7);

						}
					}
					if (k % 5 == 0)
					{
						cout << "\t";
					}
				}
			}
			seperator();
			cout  <<endl << "\tYour seat has been successfully reserved" << endl;
			//Need to add function for Reserved Seat to be saved to campaign_data.csv
			valid_seat_request = true;


		}

	}
	color(12);
	cout << endl << "\t\tPress any button to countinue" << endl;
	color(7);
	seperator();
	_getch();
	system("cls");
}

void display_seats(Campaign campaign) {
	int i{ 0 };
	vector<Seat> seats = campaign.seat;
	for (i = 0; i <= campaign.total_seats; i++) {
		while (true) {
			int hop{ 0 }, skip{ 0 };

		}
	}
}

void display_campaign(Campaign c) {
	system("cls");
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
	std::cout << endl << "Press any key to return to main menu";
	_getch();
	return;
}

void display_train(Train t) {
	std::cout << "Train ID: " << t.id << endl;
	gotoxy(10, 15);
	std::cout << "Train ID: " << t.id;
	gotoxy(10, 16);
	std::cout << "No. of Wagons: " << t.wagonNumber;
	gotoxy(10, 17);
	std::cout << "Total seats: " << t.rows * t.columns * t.wagonNumber;
	gotoxy(10, 18);
	std::cout << "Rows: " << t.rows;
	gotoxy(10, 19);
	std::cout << "Columns: " << t.columns << endl;
	gotoxy(6, 21);
	std::cout << "Press any key to return to main menu";
	_getch();
	ui_main_menu();
}

void display_ticket(Ticket t) {
	string type;
	switch (t.type) {
	case 1:
		type = "Standart";
		break;
	case 2:
		type = "Student";
		break;
	case 3:
		type = "Free";
		break;
	default:
		add_log("[Display Ticket] incorrect ticket type passed");
		type = "Error";
		break;
	}
	system("cls");
	std::cout << "Ticket ID: " << t.id << endl;
	std::cout << "Type: " << type << endl;
	std::cout << "Assigned Campaign:  " << t.assigned_campaign_id << endl;
	std::cout << "Assigned Passenger:  " << t.assigned_passenger_id << endl;
	std::cout << "Assigned Seat:  " << t.assigned_seat_id << endl;
	std::cout << endl << "Press any key to return to main menu";
	_getch();
	return;
}

void display_passenger(Passenger p) {
	system("cls");
	std::cout << "Passenger ID: " << p.id << endl;
	std::cout << "Passenger name and surname: " << p.name + " " + p.surname << endl;
	std::cout << "Passenger TCKN:  " << p.tckn << endl;
	std::cout << "Passenger Age:  " << p.age << endl;
	std::cout << endl << "Press any key to return to main menu";
	_getch();
	return;
}

void view_campaign_by_id() {
	int train_id;
	std::cout << "\n \n      Enter Train ID: ";
	std::cin >> train_id;

	vector<Campaign> campaigns = campaigns_by_train(train_id);
	Campaign selected_campaign = find_campaign_by_id(ui_campaign_selector(campaigns));
	display_campaign(selected_campaign);
}

void view_campaign_by_train() {
	int train_id = ui_train_selector(read_train_data_from_csv());
	vector<Campaign> campaigns = campaigns_by_train(train_id);
	Campaign selected_campaign = find_campaign_by_id(ui_campaign_selector(campaigns));
	display_campaign(selected_campaign);
}

void add_new_campaign() {
	long train_id, total_seats, seats_available, new_campaign_id;
	// Get the train id from user
	train_id = ui_train_selector(read_train_data_from_csv());
	Train train;
	// Find the train by id
	train = find_train_by_id(train_id);
	total_seats = (train.columns * train.rows) * train.wagonNumber;
	// We are initialising an empty train
	seats_available = total_seats;

	string departure_time, run_duration, from, to;
	std::cout << "enter departure time: ";
	std::cin >> departure_time;
	std::cout << "enter run duration: ";
	std::cin >> run_duration;
	std::cout << "enter the starting city: ";
	std::cin >> from;
	std::cout << "enter the arrival city: ";
	std::cin >> to;
	new_campaign_id = read_last_campaign_id() + 1;
	Campaign new_campaign;
	new_campaign.id = new_campaign_id;
	new_campaign.assigned_train_id = train.id;
	new_campaign.total_seats = total_seats;
	new_campaign.seats_available = seats_available;
	new_campaign.departure_time = departure_time;
	new_campaign.run_duration = run_duration;
	new_campaign.from = from;
	new_campaign.to = to;
	vector<Seat> seats;
	// Explanation: 
	// This code handles all the necessary seat labeling, depending on the amount of columns in the train
	// it will create empty seats. It will also create ids based on their row and col. Example output:
	// 1A,1B,1C,1D,2A,2B...
	for (int row = 1; row <= train.rows; row++) {
		for (char col = 'A'; col < ('A' + train.columns); col++) {
			Seat seat{};
			seat.id = row * train.columns + (col - 'A') + 1;
			seat.row = row;
			seat.column = col;
			seat.status = 1; // 1 means empty and available seat
			seats.push_back(seat);
		}
	}
	new_campaign.seat = seats;
	save_campaign_data_to_csv(new_campaign);

	// Log the new campaign information
	add_log("[Add Campaign] ID: " + to_string(new_campaign_id) + ", Assigned Train ID: " + to_string(train_id) + ", Total Seats: " + to_string(total_seats) + ", Seats Available: " + to_string(seats_available) + ", Departure Time: " + departure_time + ", Run Duration: " + run_duration + ", From: " + from + ", To: " + to);
}

void select_to_buy() {

	system("cls");
	seperator();
	cout << "\t\t\t\t  ** Work In Progress **\n\n";
	cout << "\t\t\t--Input screen to select campaign and train--";
	color(12);
	cout << endl << "\n\t\t\t       Press any button to countinue";
	color(7);
	seperator();
	_getch();

}
void buy_ticket() {
		system("cls");
		int Set[] = { 7,7,7};   //Default colors
		int counter = 3;
		char key;

		for (int i = 0;;)
		{
			gotoxy(10, 5);
			color(Set[0]);
			std::cout << "1. Reserve a Seat";

			gotoxy(10, 6);
			color(Set[1]);
			std::cout << "2. Show Reserved Tickets";

			gotoxy(10, 7);
			color(Set[2]);
			std::cout << "Go back to main menu";

			key = _getch();

			if (key == 72 && (counter >= 2 && counter <= 4))   //72 = up arrow key
			{
				counter--;
			}
			if (key == 80 && (counter >= 1 && counter <= 3))   //80 = down arrow key
			{
				counter++;
			}
			if (key == '\r')   //carriage return = enter key
			{
				if (counter == 1)
				{
					select_to_buy();
					selectSeat();
				}
				if (counter == 2)
				{
					system("cls");
					cout << "\n\n\t\tWIP";
				}
				if (counter == 3)
				{
					ui_main_menu();
				}
			}
			Set[0] = 7;
			Set[1] = 7;
			Set[2] = 7;

			if (counter == 1)
			{
				Set[0] = 12;
			}
			if (counter == 2)
			{
				Set[1] = 12;   //12 is red
			}
			if (counter == 3)
			{
				Set[2] = 12;
			}
		}
		return;
	}



void view_ticket_by_id() {
	long id;
	std::cout << "\n \n      Enter Ticket ID: ";
	cin >> id;
	Ticket selected_ticket = find_ticket_by_id(id);
	display_ticket(selected_ticket);
	system("cls");
}

void ui_ticket_menu() {
	if (admin) {
		system("cls");
		int Set[] = { 7,7,7 };
		int counter = 3;
		char key = 0;
		{

			for (int i = 0;;)
			{
				gotoxy(10, 5);
				color(Set[0]);
				std::cout << "1. View Ticket ID";

				color(Set[1]);
				color(Set[2]);
				std::cout << "3. Delete Ticket (In progress!!!)";

				gotoxy(10, 8);
				color(Set[3]);
				std::cout << "4. Return to Main Menu";


			}
			if (key == 80 && (counter >= 1 && counter <= 3))   //80 = down arrow key
			{
				counter++;
			}
			if (key == '\r')   //carriage return = enter key
			{
				{
					if (counter == 2)
					{
						gotoxy(10, 11);
						add_new_ticket();
					}
					if (counter == 3)
						gotoxy(10, 11);
					{
						gotoxy(10, 11);
						ui_main_menu();
					}
				}
				Set[0] = 7;
				Set[1] = 7;
				Set[3] = 7;

				if (counter == 1)
				{
					Set[0] = 12;
				}
				if (counter == 4)
				{
					Set[3] = 12;
				}
			}
		}
	}
	else buy_ticket();
}
void ui_campaign_menu() {
	system("cls");
	int Set[] = { 7,7,7,7,7 };   //Default colors
	int counter = 3;
	char key;

	for (int i = 0;;)
	{
		gotoxy(10, 5);
		color(Set[0]);
		std::cout << "1. View campaign by id";

		gotoxy(10, 6);
		color(Set[1]);
		std::cout << "2. View campaign by train";

		gotoxy(10, 7);
		color(Set[2]);
		std::cout << "3. Add campaign";

		gotoxy(10, 8);
		color(Set[3]);
		std::cout << "4. Reserved";

		gotoxy(10, 9);
		color(Set[4]);
		std::cout << "Go back to main menu";

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 4))   //72 = up arrow key
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 3))   //80 = down arrow key
		{
			counter++;
		}
		if (key == '\r')   //carriage return = enter key
		{
			if (counter == 1)
			{
				view_campaign_by_id();
			}
			if (counter == 2)
			{
				view_campaign_by_train();
			}
			if (counter == 3)
			{
				add_new_campaign();
			}
			if (counter == 4)
			{
				std::cout << " //reserved for future usage";
			}
			if (counter == 5)
			{
				ui_main_menu();
			}
		}
		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;
		Set[3] = 7;

		if (counter == 1)
		{
			Set[0] = 12;
		}
		if (counter == 2)
		{
			Set[1] = 12;   //12 is red
		}
		if (counter == 3)
		{
			Set[2] = 12;
		}
		if (counter == 4)
		{
			Set[3] = 12;
		}
	}
	return;
}

void view_train_by_id() {
	long train_id;
	std::cout << "\n \n      Enter Train ID: ";
	std::cin >> train_id;
	display_train(find_train_by_id(train_id));
}


void train_list() {
	long f_line, n_lines;
	cout << "Enter the train count interval you want to see:\nFrom: ";
	std::cin >> f_line;
	cout << "To: ";
	std::cin >> n_lines;
	cout << "To: \n\n";
	dump_train_csv_data(f_line);

	cout << "\n\nPress any key to return to main menu";
	_getch();
	ui_main_menu();
}

void ui_train_menu() {
	system("cls");
	int Set[] = { 7,7,7,7,7 };   //Default colors
	int counter = 3;
	char key;

	for (int i = 0;;)
	{
		gotoxy(10, 5);
		color(Set[0]);
		std::cout << "1. View Train by Train ID";

		gotoxy(10, 6);
		color(Set[1]);
		std::cout << "2. Add a new Train";

		gotoxy(10, 7);
		color(Set[2]);
		std::cout << "3. Delete Train by ID";

		gotoxy(10, 8);
		color(Set[3]);
		std::cout << "4. Train List";

		gotoxy(10, 9);
		color(Set[4]);
		std::cout << "5. Return to Main Menu";

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 5))   //72 = up arrow key
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 4))   //80 = down arrow key
		{
			counter++;
		}
		if (key == '\r')   //carriage return = enter key
		{
			if (counter == 1)
			{
				gotoxy(10, 11);
				view_train_by_id();
			}
			if (counter == 2)
			{
				gotoxy(10, 11);
				add_new_train();
			}
			if (counter == 3)
			{
				gotoxy(10, 11);
				cout << " delete_train_data()   WIP!";//delete
			}
			if (counter == 4)
			{
				gotoxy(10, 11);
				train_list();
			}
			if (counter == 5)
			{
				gotoxy(10, 12);
				ui_main_menu();
			}
		}
		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;
		Set[3] = 7;
		Set[4] = 7;

		if (counter == 1)
		{
			Set[0] = 12;
		}
		if (counter == 2)
		{
			Set[1] = 12;   //12 is red
		}
		if (counter == 3)
		{
			Set[2] = 12;
		}
		if (counter == 4)
		{
			Set[3] = 12;
		}
		if (counter == 5)
		{
			Set[4] = 12;
		}
	}
	return;
}

void ui_main_menu() {
	system("cls");

	std::cout << "             **                                           " << std::endl;
	std::cout << "            ****     *          *****  ***      *     *  *   *              " << std::endl;
	std::cout << "           *****    * *           *    *  *    * *    *  **  *    " << std::endl;
	std::cout << "           ***     *****   ***    *    ***    *****   *  * * *              " << std::endl;
	std::cout << "          **      *     *         *    *  *  *     *  *  *  **          " << std::endl;
	std::cout << "        *                 " << std::endl;
	std::cout << "      *                 " << std::endl;
	std::cout << "     *                              " << std::endl;
	std::cout << "    ___  _____________              " << std::endl;
	std::cout << "    _|____|____|____|_    __________    __________    __________    __________               " << std::endl;
	std::cout << "  _| |_| |_| |_| |_| |    | |    | |    |   ||   |    | |    | |    |   ||   |     " << std::endl;
	std::cout << "  |__________________|----|_|_||_|_|----|___||___|----|_|_||_|_|----|___||___|               " << std::endl;
	std::cout << "    (@)(@)      (@)(@)      @@  @@        @@  @@        @@  @@        @@  @@       " << std::endl;

	int Set[] = { 7,7,7,7,7 };   //Default colors, White
	int counter = 3;
	char key;

	for (int i = 0;;)
	{
		gotoxy(10, 17);
		color(Set[0]);
		std::cout << "1. Campaign";

		gotoxy(10, 18);
		color(Set[1]);
		std::cout << "2. Train";

		gotoxy(10, 19);
		color(Set[2]);
		std::cout << "3. Ticket";

		gotoxy(10, 20);
		color(Set[3]);
		std::cout << "4. Passenger";

		gotoxy(10, 21);
		color(Set[4]);
		std::cout << "5. Reserve a Seat";

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 5))   //72 = up arrow key
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 4))   //80 = down arrow key
		{
			counter++;
		}
		if (key == '\r')   //carriage return = enter key
		{
			if (counter == 1)
			{
				ui_campaign_menu();
			}
			if (counter == 2)
			{
				ui_train_menu();
			}
			if (counter == 3)
			{
				ui_ticket_menu();
			}
			if (counter == 4)
			{
				system("clr");
				display_seat();
			}
			if (counter == 5)
			{
				buy_ticket();
			}
		}
		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;
		Set[3] = 7;
		Set[4] = 7;

		if (counter == 1)
		{
			Set[0] = 12;
		}
		if (counter == 2)
		{
			Set[1] = 12;   //12 is red
		}
		if (counter == 3)
		{
			Set[2] = 12;
		}
		if (counter == 4)
		{
			Set[3] = 12;
		}		
		if (counter == 5)
		{
			Set[4] = 12;
		}
	}
	return;
}
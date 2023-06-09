#pragma once
#include "utils.h"

extern string ticket_path;

struct Ticket {
    long id;
    long type; //1 Normal, 2 Student, 3 Free
    long assigned_campaign_id;
    long assigned_passenger_id;
    long assigned_seat_id;
};

vector<Ticket> read_ticket_data_from_csv();
void save_ticket_data_to_csv(const Ticket& new_ticket);
long get_ticket_type(long id);
Ticket find_ticket_by_id(long id);
long read_last_ticket_id();
void add_new_ticket();
void dump_ticket_csv_data(long num_lines);
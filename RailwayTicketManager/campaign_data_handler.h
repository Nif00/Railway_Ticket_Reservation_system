#pragma once
#include "utils.h"

extern string campaign_path;

struct Seat {
    long id;
    long column;
    long row;
    long status; //1 free, 2 reserved, 3 occupied, 4 blocked 
};
struct Campaign {
    long id;
    long assigned_train_id;
    long total_seats;
    long seats_available;
    string departure_time;
    string run_duration;
    string from;
    string to;
    vector<Seat> seat;
};

vector<Campaign> read_campaign_data_from_file();
vector<Campaign> campaigns_by_train(long train_id);
long count_booked_seats(const vector<Campaign>& campaigns);
Campaign find_campaign_by_id(long id);
long read_last_campaign_id();
void add_new_campaign();
void dump_campaign_csv_data(long num_lines);
void update_seat(long seat_id, long campaign_id, long status);
#pragma once
#include "utils.h"
struct Seat {
    int id;
    int column;
    int row;
    int status; //1 free, 2 reserved, 3 occupied, 4 blocked 
};
struct Campaign {
public:
    int id;
    int assigned_train_id;
    int total_seats;
    int seats_available;
    string departure_time;
    string run_duration;
    vector<Seat> seat;
};
vector<Campaign> read_campaign_data_from_csv();
void save_campaign_data_to_csv(const Campaign& new_campaign);
int count_booked_seats(const vector<Campaign>& campaigns);
Campaign find_campaign_by_id(int id);
int read_last_campaign_id();
void add_new_campaign();
void dump_campaign_csv_data(int num_lines);
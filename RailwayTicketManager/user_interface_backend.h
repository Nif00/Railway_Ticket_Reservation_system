#pragma once
#include "utils.h"
#include "campaign_data_handler.h"
#include "Passenger_data_handler.h"
#include "trains_data_handler.h"

extern bool admin;
extern bool debug;
long ui_campaign_selector(vector<Campaign> campaigns);
void save_campaign_data_to_csv(const Campaign& new_campaign);
//long ui_train_selector(vector<Train> trains);
long ui_passenger_selector();
void ui_main_menu();

#pragma once
#include "utils.h"

extern string train_path;

struct Train {
    long id;
    long wagonNumber;
    long rows;
    long columns;
};

vector<Train> read_train_data_from_csv();
void save_train_data_to_csv(const Train& new_Train);
Train find_train_by_id(long id);
long read_last_train_ID();
void add_new_train();
void dump_train_csv_data(long num_lines);
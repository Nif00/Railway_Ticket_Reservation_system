#pragma once
#include "utils.h"

extern string train_path;

struct Train {
    long id;
    int wagonNumber;
    int rows;
    int columns;
};

vector<Train> read_train_data_from_csv();
void save_train_data_to_csv(const Train& new_Train);
Train find_train_by_id(long id);
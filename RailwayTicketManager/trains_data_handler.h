#pragma once
#include "utils.h"
struct Train {
    int id;
    int wagonNumber;
    int rows;
    char columns;
};

//int createID();
//int createWagon();
//vector <Train> settingTrain(int);
//vector <Train> readTrain(int);

vector<Train> read_Train_data_from_csv();
void save_Train_data_to_csv(const Train& new_Train);
#pragma once
#include "utils.h"
struct Train {
    int id;
    int wagon;
    string block;
    int seatNumber[20];

};
int createID();
int createWagon();
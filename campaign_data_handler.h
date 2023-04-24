#pragma once
#include "utils.h"
struct Seat{
    int id;
    int column;
    int row;
    int status; //1 free, 2 reserved, 3 occupied, 4 blocked 
};
struct campaign{
    public:
    int id;
    int assigned_train_id;
    int total_seats;
    int seats_available;
    Seat seat;
};

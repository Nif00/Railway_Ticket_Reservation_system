#include "utils.h"
struct campaign{
    int id;
    int assigned_train_id;
    int total_seats;
    int seats_available;
    struct seat{
        int id;
        int column;
        int row;
        int status; //1 free, 2 reserved, 3 occupied, 4 blocked 
    };
};

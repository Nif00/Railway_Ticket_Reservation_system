#include "utils.h"
#include "trains_data_handler.h"

// Create a train struct with a unique ID
int createID() {
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> ID(100000, 999999);

    
    return ID(generator);
}
int createWagon() {
    auto seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);
    uniform_int_distribution<int> wagonNumber(0, 7);

    return wagonNumber(generator);
}

void settingTrain() {
    Train t;

    t.id = createID();
    t.wagon = createWagon();
    vector <Train> v;


}

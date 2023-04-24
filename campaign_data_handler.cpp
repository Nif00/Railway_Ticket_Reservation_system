#include "utils.h"
#include "campaign_data_handler.h"
std::string write_campaign_data_file(campaign to_write) {
    std::string data_to_write = (std::to_string(to_write.id) + "," +
                              std::to_string(to_write.assigned_train_id) + "," +
                              std::to_string(to_write.total_seats) + "," +
                              std::to_string(to_write.seats_available) + "," +
                              std::to_string(to_write.seat.id) + "," +
                              std::to_string(to_write.seat.column) + "," +
                              std::to_string(to_write.seat.row) + "," +
                              std::to_string(to_write.seat.status)+"\n");
    write_to_file("campaign_data.csv", data_to_write);
}


std::string read_campaign_data_file(){
    std::string raw_data = read_from_file("campaign_data.csv");

}
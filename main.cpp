#include <iostream>
#include "data_io.h"

int main() {

    clock_t t;
    t = clock();
    string file_name = "../2nd/flight_sheet.csv";
    FlightList flight_table;
    read_flight(file_name, flight_table);
//    flight_table.display_info();

    BanRuleList rule_list;
    read_ban_rule("../2nd/ban_list.csv", rule_list);
//    rule_list.display();

    Typhoon typhoon;
    read_typhoon("../2nd/typhoon.csv", typhoon);
//    typhoon.display();


    TravelTimeTable travel_time_table;
    read_travel_time("../2nd/travel_time.csv", travel_time_table);
//    travel_time_table.display();

    ClosedTimeTable closed_time_table;
    read_closed_time("../2nd/airport_time_window.csv", closed_time_table);
//    closed_time_table.display();

    float read_data_time = (float) (clock() - t) / CLOCKS_PER_SEC;
    cout << "读取数据时间：" << read_data_time << endl;


    return 0;
}
#include <iostream>
#include "data_io.h"

int main() {

    clock_t t;
    t = clock();
    string file_name = "../2nd/航班.csv";
    FlightList flight_table;
    read_flight(file_name, flight_table);
//    flight_table.display_info();
    cout << "航班总数" << flight_table.Schedule.size() << endl;

    BanRuleSet rule_list;
    read_ban_rule("../2nd/航线-飞机限制.csv", rule_list);
//    rule_list.display();
    cout << "航线-飞机限制总数" << rule_list.RuleSet.size() << endl;
//
    Typhoon typhoon;
    read_typhoon("../2nd/台风场景.csv", typhoon);
//    typhoon.display();
//
//
    TravelTimeTable travel_time_table;
    read_travel_time("../2nd/飞行时间.csv", travel_time_table);
//    travel_time_table.display();
    cout << "飞行时间表总数" << travel_time_table.TimeTable.size() << endl;
//
    TransferTable transfer_table;
    read_transfer_info("../2nd/中转时间限制.csv", transfer_table);
    cout << "转机表总数" << transfer_table.Table.size() << endl;
//    transfer_table.display();
//

    AirportList airport_list;
    read_airport_info("../2nd/机场.csv", airport_list);
    cout << "机场总数" << airport_list.airport_list.size() << endl;
//    airport_list.display();
//    float read_data_time = (float) (clock() - t) / CLOCKS_PER_SEC;
//    cout << "读取数据时间：" << read_data_time << endl;


    return 0;
}
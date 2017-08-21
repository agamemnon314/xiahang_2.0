//
// Created by agamemnon on 17-8-8.
//

#ifndef XH_2ND_DATA_IO_H
#define XH_2ND_DATA_IO_H

#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <locale>
#include <iomanip>
#include "flight.h"

using namespace std;

bool read_flight(const string &file_name, FlightList &flight_table) {
    //  打开文件
    ifstream infile;
    infile.open(file_name);
    unsigned long ind;
    if (infile) {
        string str, s;
        std::istringstream ss;
        while (getline(infile, str)) {
            Flight flight;
//            航班ID
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            flight.FlightID = stoi(s);
//            日期
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
//            国际 / 国内
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            flight.IsDomestic = s == "国内";
//            航班号
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            flight.FlightNo = stoi(s);
//            起飞机场
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            flight.From = stoi(s);
//            降落机场
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            flight.To = stoi(s);
//            起飞时间
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            tm t_dep = {};
            ss.str(s);
            ss >> std::get_time(&t_dep, "%Y-%m-%d %H:%M:%S");
            flight.DepartureTime = mktime(&t_dep);
            ss.clear();
//            降落时间
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            ss.str(s);
            tm t_arr = {};
            ss >> std::get_time(&t_arr, "%Y-%m-%d %H:%M:%S");
            flight.ArrivalTime = mktime(&t_arr);
            ss.clear();
//            飞机ID
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            flight.PlaneID = stoi(s);
//            机型
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            flight.PlaneType = stoi(s);
//            乘客数
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            flight.PassengerNumber = stoi(s);
//            联机乘客数
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            flight.ConnectedPassengerNumber = stoi(s);
//            座位数
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            flight.SeatNumber = stoi(s);
//            重要系数
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            flight.Weight = stod(s);
            flight_table.Schedule.emplace_back(flight);
        }

        return true;
    }

    return false;

}

bool read_ban_rule(const string &file_name, BanRuleSet &rule_list) {
    //  打开文件
    ifstream infile;
    infile.open(file_name);
    unsigned long ind;
    if (infile) {
        string str, s;
        while (getline(infile, str)) {
            BanRule rule;
//            起飞机场
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            rule.From = stoi(s);
//            降落机场
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            rule.To = stoi(s);
//            飞机ID
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            rule.PlaneID = stoi(s);

            rule_list.RuleSet.insert(rule);
        }
        return true;
    }

    return false;

}

bool read_typhoon(const string &file_name, Typhoon &typhoon) {
    //  打开文件
    ifstream infile;
    infile.open(file_name);
    unsigned long ind;
    if (infile) {
        string str, s;
        std::istringstream ss;
        while (getline(infile, str)) {
            TyphoonTimeWindow time_window;
            string influence_type;
            int airport_id;
//            开始时间
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            ss.str(s);
            tm t_s = {};
            ss >> std::get_time(&t_s, "%Y-%m-%d %H:%M:%S");
            time_window.s = mktime(&t_s);
            ss.clear();
//            结束时间
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            ss.str(s);
            tm t_t = {};
            ss >> std::get_time(&t_t, "%Y-%m-%d %H:%M:%S");
            time_window.t = mktime(&t_t);
            ss.clear();
//            影响类型
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            influence_type = s;
//            机场
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            airport_id = stoi(s);
            if (influence_type == "起飞") {
                typhoon.DepartureTimeWindow[airport_id] = time_window;
            }
            if (influence_type == "降落") {
                typhoon.ArrivalTimeWindow[airport_id] = time_window;
            }
            if (influence_type == "停机") {
                time_window.tol = stoi(str);
                typhoon.StayTimeWindow[airport_id] = time_window;
            }
        }
        return true;
    }

    return false;

}

bool read_travel_time(const string &file_name, TravelTimeTable &travel_time_table) {
    //  打开文件
    ifstream infile;
    infile.open(file_name);
    unsigned long ind;
    if (infile) {
        string str, s;
        std::istringstream ss;
        while (getline(infile, str)) {
            FlightRoute route;
//            飞机机型
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            route.PlaneType = stoi(s);
//            起飞机场
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            route.From = stoi(s);
//            降落机场
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            route.To = stoi(s);
//            飞行时间
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            travel_time_table.TimeTable[route] = stoi(s);
        }
        return true;
    }

    return false;

}

bool read_transfer_info(const string &file_name, TransferTable &transfer_table) {
    //  打开文件
    ifstream infile;
    infile.open(file_name);
    unsigned long ind;
    if (infile) {
        string str, s;
        std::istringstream ss;
        while (getline(infile, str)) {
            Transfer transfer;
            tm t{0};
            time_t tt;
//          进港航班ID
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            transfer.InFlightID = stoi(s);
//          出港航班ID
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            transfer.OutFlightID = stoi(s);
//          最短转机时限（分钟）
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            transfer.TransferTime = stoi(s);
//          中转旅客人数
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            transfer.PassengerNumber = stoi(s);

            transfer_table.Table.push_back(transfer);
        }
        return true;
    }

    return false;
}

bool read_airport_info(const string &file_name, AirportList &airport_list) {
    //  打开文件
    ifstream infile;
    infile.open(file_name);
    unsigned long ind;
    if (infile) {
        string str, s;
        std::istringstream ss;
        while (getline(infile, str)) {
            Airport airport;
            tm t{0};
            time_t tt;
//          进港航班ID
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            airport.airport_id = stoi(s);
//          出港航班ID
            ind = str.find(',');
            s = str.substr(0, ind);
            str = str.substr(ind + 1);
            airport.is_domestic = stoi(s);


            airport_list.airport_list.emplace_back(airport);
        }
        return true;
    }

    return false;
}

#endif //XH_2ND_DATA_IO_H

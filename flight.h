//
// Created by agamemnon on 17-8-8.
//

#ifndef XH_2ND_FLIGHT_H
#define XH_2ND_FLIGHT_H

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <ctime>
#include <locale>
#include <iomanip>
#include <fstream>

using namespace std;
struct Endorsement {
    int NewFlightID = -1;
    int PassengerNumber = 0;
};

struct Flight {
    int FlightID = -1;
    bool IsDomestic = false;
    int FlightNo = -1;
    int From = -1;
    int To = -1;
    time_t DepartureTime = 0;
    time_t ArrivalTime = 0;
    int PlaneID = -1;
    int PlaneType = -1;
    int PassengerNumber = 0;
    int ConnectedPassengerNumber = 0;
    int SeatNumber = 0;
    int Cancel = 0;
    int DropStopOver = 0;
    int Adjust = 0;
    double Weight = 0.0;
    vector<Endorsement> Endorse;

    void display_info() const {
        tm t_dep = {}, t_arr = {};
        t_dep = *localtime(&DepartureTime);
        t_arr = *localtime(&ArrivalTime);
        cout << FlightID << ",";
        cout << put_time(&t_dep, "%F") << ",";
        cout << IsDomestic << ",";
        cout << FlightNo << ",";
        cout << From << ",";
        cout << To << ",";
        cout << put_time(&t_dep, "%F %T") << ",";
        cout << put_time(&t_arr, "%F %T") << ",";
        cout << PlaneID << ",";
        cout << PlaneType << ",";
        cout << PassengerNumber << ",";
        cout << ConnectedPassengerNumber << ",";
        cout << SeatNumber << ",";
        cout << Weight << endl;

    }

    void display_ans() const {
        tm t_dep = {}, t_arr = {};
        t_dep = *localtime(&DepartureTime);
        t_arr = *localtime(&ArrivalTime);
        cout << FlightID << ",";
        cout << put_time(&t_dep, "%F") << ",";
        cout << IsDomestic << ",";
        cout << FlightNo << ",";
        cout << From << ",";
        cout << To << ",";
        cout << put_time(&t_dep, "%F %T") << ",";
        cout << put_time(&t_arr, "%F %T") << ",";
        cout << PlaneID << ",";
        cout << PlaneType << ",";
        cout << Weight << ",";
        cout << Cancel << ",";
        cout << DropStopOver << ",";
        cout << Adjust << endl;
    }

    void write(ofstream &outfile) const {
        tm t_dep = {}, t_arr = {};
        t_dep = *localtime(&DepartureTime);
        t_arr = *localtime(&ArrivalTime);
        outfile << FlightID << ",";
        outfile << From << ",";
        outfile << To << ",";
        outfile << put_time(&t_dep, "%Y/%m/%d %R") << ",";
        outfile << put_time(&t_arr, "%Y/%m/%d %R") << ",";
        outfile << PlaneID << ",";
        outfile << Cancel << ",";
        outfile << DropStopOver << ",";
        outfile << Adjust << endl;
    }

    bool operator<(const Flight &that) const {
        return DepartureTime < that.DepartureTime;
    }

    bool operator==(const Flight &that) const {
        return FlightID == that.FlightID;
    }
};

struct FlightList {
    list <Flight> Schedule;

    void display_info() {
        for (auto &flight:Schedule) {
            flight.display_info();
        }
    }

    void display_ans() {
        for (auto &flight:Schedule) {
            flight.display_ans();
        }
    }

    void sort_by_departure_time() {
        Schedule.sort();
    }
};

struct BanRule {
    int From = 0;
    int To = 0;
    int PlaneID = 0;

    void display() const {
        cout << From << ", ";
        cout << To << ", ";
        cout << PlaneID << endl;
    }

    bool operator<(const BanRule &that) const {
        int a = 1000 * (1000 * From + To) + PlaneID;
        int b = 1000 * (1000 * that.From + that.To) + that.PlaneID;
        return a < b;
    }
};

struct BanRuleSet {
    set<BanRule> RuleSet;

    void display() const {
        for (auto &rule:RuleSet) {
            rule.display();
        }
    }
};

struct TyphoonTimeWindow {
    time_t s = 0;
    time_t t = 0;
    int tol = 0;
};

struct Typhoon {
    map<int, TyphoonTimeWindow> DepartureTimeWindow;
    map<int, TyphoonTimeWindow> ArrivalTimeWindow;
    map<int, TyphoonTimeWindow> StayTimeWindow;

    bool check_departure_time(const int airport_id, time_t &t_dep) const {
        if (DepartureTimeWindow.find(airport_id) ==
            DepartureTimeWindow.end()) {
            return false;
        }
        time_t t1, t2;
        t1 = DepartureTimeWindow.at(airport_id).s;
        t2 = DepartureTimeWindow.at(airport_id).t;
        return (t1 < t_dep) && (t_dep < t2);
    }

    bool check_arrival_time(const int airport_id, time_t &t_arr) const {
        if (ArrivalTimeWindow.find(airport_id) ==
            ArrivalTimeWindow.end()) {
            return false;
        }
        time_t t1, t2;
        t1 = ArrivalTimeWindow.at(airport_id).s;
        t2 = ArrivalTimeWindow.at(airport_id).t;
        return (t1 < t_arr) && (t_arr < t2);
    }

    bool check_stay_zone(const int airport_id, time_t &t_pre, time_t &t) const {
        if (StayTimeWindow.find(airport_id) ==
            StayTimeWindow.end()) {
            return false;
        }
        time_t t1, t2;
        t1 = StayTimeWindow.at(airport_id).s;
        t2 = StayTimeWindow.at(airport_id).t;

        return !(t_pre >= t2 || t <= t1);
    }

    bool check_stay_zone(const int airport_id, time_t &t) const {
        if (StayTimeWindow.find(airport_id) ==
            StayTimeWindow.end()) {
            return false;
        }
        time_t t1;
        t1 = StayTimeWindow.at(airport_id).s;
        return t > t1;
    }

    void display() {
        cout << "出发" << endl;
        for (auto &x:DepartureTimeWindow) {
            cout << x.first << ",";
            tm ss = {}, tt = {};
            ss = *localtime(&x.second.s);
            tt = *localtime(&x.second.t);
            cout << put_time(&ss, "%F %T") << ",";
            cout << put_time(&tt, "%F %T") << endl;
        }
        cout << "降落" << endl;
        for (auto &x:ArrivalTimeWindow) {
            cout << x.first << ",";
            tm ss = {}, tt = {};
            ss = *localtime(&x.second.s);
            tt = *localtime(&x.second.t);
            cout << put_time(&ss, "%F %T") << ",";
            cout << put_time(&tt, "%F %T") << endl;
        }
        cout << "停机" << endl;
        for (auto &x:StayTimeWindow) {
            cout << x.first << ",";
            tm ss = {}, tt = {};
            ss = *localtime(&x.second.s);
            tt = *localtime(&x.second.t);
            cout << put_time(&ss, "%F %T") << ",";
            cout << put_time(&tt, "%F %T") << ",";
            cout << x.second.tol << endl;
        }
    }
};

struct FlightRoute {
    int PlaneType = -1;
    int From = -1;
    int To = -1;

    bool operator<(const FlightRoute &that) const {
        int a = 1000 * (1000 * From + To) + PlaneType;
        int b = 1000 * (1000 * that.From + that.To) + that.PlaneType;
        return a < b;
    }

};

struct TravelTimeTable {
    map<FlightRoute, int> TimeTable;

    void display() {
        for (auto &x:TimeTable) {
            cout << x.first.PlaneType << ",";
            cout << x.first.From << ",";
            cout << x.first.To << ",";
            cout << x.second << endl;
        }
    }

};

struct Transfer {
    int InFlightID = -1;
    int OutFlightID = -1;
    int TransferTime = -1;
    int PassengerNumber = -1;

    void display() {
        cout << InFlightID << ",";
        cout << OutFlightID << ",";
        cout << TransferTime << ",";
        cout << PassengerNumber << endl;
    }
};

struct TransferTable {
    list <Transfer> Table;

    void display() {
        for (auto &x:Table) {
            x.display();
        }
    }
};

struct Airport {
    int airport_id = -1;
    bool is_domestic = false;

    void display() {
        cout << airport_id << ",";
        cout << is_domestic << endl;
    }
};

struct AirportList {
    vector<Airport> airport_list;

    void display() {
        for (auto &x:airport_list) {
            x.display();
        }
    }
};


#endif //XH_2ND_FLIGHT_H

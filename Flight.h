#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Flight {
private:
    string origin, destination, flight_number, departure_time;
    double price;
    int seats_available, seats_total;
    vector<bool> seat_map;
public:
    Flight(string o, string d, string fn, string t, double p, int sa, int st);
    void showInfo() const;
    bool reserveSeat();
    string get_flightNumber() const;
    void show_seats() const;
};
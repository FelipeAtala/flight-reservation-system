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
    Flight(string o, string d, string fn, string t, double p, int s);
    void showInfo() const;
    bool reserveSeat(int index);
    string get_flightNumber() const;
    void show_seats() const;
    double get_price() const;
    int get_available_seats() const;
    int get_total_seats() const;
    string get_origin() const;
    string get_destination() const;
    string get_departure_time() const;
    void set_price(double p);
    void set_departure_time(string t);
};

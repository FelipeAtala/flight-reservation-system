#pragma once
#include <string>
using namespace std;

class Reservation {
    private:
    string flight_number, reservation_id, passenger_id;
    int seat_number;

public:
    Reservation(string f_numb, string r_id, string p_id, int s);
    void show() const;
    string getID() const;
    string get_flightNumber() const;
    int get_seat() const;

};
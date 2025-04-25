#pragma once
#include <string>
using namespace std;

class Reservation {
private:
    string flight_number;
    int reservation_id, passenger_id;
public:
    Reservation(string fn, int rid, int pid);
    void show() const;
};
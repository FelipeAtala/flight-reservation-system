#include "Reservation.h"
#include <iostream>
using namespace std;

Reservation::Reservation(string fn, int rid, int pid) : flight_number(fn), reservation_id(rid), passenger_id(pid) {}

void Reservation::show() const {
    cout << "Reservation ID: " << reservation_id << " | Passenger ID: " << passenger_id << " | Flight number: " << flight_number << endl;
}
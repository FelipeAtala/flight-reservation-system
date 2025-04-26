#include "Reservation.h"
#include <iostream>
using namespace std;

Reservation::Reservation(string fn, string rid, string pid, int seat)
    : flight_number(fn), reservation_id(rid), passenger_id(pid), seat_number(seat) {}

void Reservation::show() const {
    cout << "ID rezerwacji: " << reservation_id
         << " | ID pasażera: " << passenger_id
         << " | Numer lotu: " << flight_number
         << " | Miejsce: " << seat_number << endl;
}

int Reservation::get_seat() const {
    return seat_number;
}

string Reservation::getID() const {
    return passenger_id;
}

string Reservation::get_flightNumber() const {
    return flight_number;
}

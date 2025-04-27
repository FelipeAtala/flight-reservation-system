#include "Reservation.h"
#include <iostream>
using namespace std;

Reservation::Reservation(string f_numb, string r_id, string p_id, int s)
    : flight_number(f_numb), reservation_id(r_id), passenger_id(p_id), seat_number(s) {}

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

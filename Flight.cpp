#include "Flight.h"
#include <iostream>
using namespace std;

Flight::Flight(string o, string d, string fn, string t, double p, int sa, int st) : origin(o), destination(d), flight_number(fn), departure_time(t), price(p), seats_available(sa),
seats_total(st) {}

void Flight::showInfo() const {
    cout << flight_number << ": " << origin << " - > " << destination << " | " << time << " | " << "Price: " << price << "PLN | Seats available: " << seats_available << endl;
}

bool Flight::reserveSeat() {
    if(seats_available > 0) {
        seats_available--;
        return true;
    }
    return false;
}

string Flight::get_flightNumber() const { return flight_number; }

void Flight::show_seats() const {
    cout << "Mapa miejsc: " << endl;
    for(size_t i = 0; i < seat_map.size(); i++) {
        if(seat_map[i]) { cout << "[ ]"; }
        else { cout << "[X]"; }
        if((i + 1) % 6 == 0) cout << "\n";
    }
}
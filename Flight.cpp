#include "Flight.h"
#include <iostream>
using namespace std;

Flight::Flight(string o, string d, string fn, string t, double p, int s) : origin(o), destination(d), flight_number(fn), departure_time(t), price(p), seats_available(s),
seats_total(s) {
    seat_map.resize(s, true);
}
void Flight::showInfo() const {
    cout << flight_number << ": " << origin << " - > " << destination << " | " << departure_time << " | " << "Price: " << price << "PLN | Seats available: " << seats_available << endl;
}
bool Flight::reserveSeat(int index) {
    if (index >= 0 && index < seat_map.size() && seat_map[index]) {
        seat_map[index] = false;
        seats_available--;
        return true;
    }
    return false;    
}
string Flight::get_flightNumber() const { return flight_number; }
void Flight::show_seats() const {
    cout << "Seat map: " << endl;
    for(size_t i = 0; i < seat_map.size(); i++) {
        if(seat_map[i]) { cout << "[" << i << "]"; }
        else { cout << "[X]"; }
        if((i + 1) % 6 == 0) cout << "\n";
    }
    cout << "\n";
}
double Flight::get_price() const { return price; }
int Flight::get_available_seats() const { return seats_available; }
int Flight::get_total_seats() const { return seats_total; }
string Flight::get_origin() const { return origin; }
string Flight::get_destination() const { return destination; }
string Flight::get_departure_time() const { return departure_time; }
void Flight::set_price(double p) { price = p; }
void Flight::set_departure_time(string t) { departure_time = t; }


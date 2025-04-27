#include "Passenger.h"

Passenger::Passenger(string n, string sn, string i) : name(n), surname(sn), passenger_id(i){}

string Passenger::getID() const{ return passenger_id; }

string Passenger::get_full_name() const { return name + " " + surname; }


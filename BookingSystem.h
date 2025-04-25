#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include "Flight.h"
#include "Reservation.h"
#include "Passenger.h"
using namespace std;

class BookingSystem {
private:
    vector<Flight> flights;
    vector<Reservation> reservations;
    vector<Passenger> passengers;
public:
    BookingSystem();
    void add_flight();
    void add_passenger();
    void make_reservation();
    void show_flightInfo();
    void show_reservation();
};
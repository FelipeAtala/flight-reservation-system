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
    int passenger_counter = 1;
public:
    BookingSystem();
    void add_flight();
    void add_passenger();
    void make_reservation();
    void show_flightInfo();
    void show_reservation();
    void cancel_reservation();
    void save_data() const;
    void load_data();
};

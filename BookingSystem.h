#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include "Flight.h"
#include "Reservation.h"
#include "Passenger.h"
#include <algorithm>
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
    void modify_flight();
    void remove_flight();
    void show_passengers() const;
    void modify_passenger();
    void remove_passenger();
    void modify_reservation();
    void filter_by_destination() const;
    void sort_flights_by_price();
};

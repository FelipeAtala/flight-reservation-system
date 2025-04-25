#include "BookingSystem.h"

BookingSystem::BookingSystem() {}

void BookingSystem::add_flight() {
    string flight_number, from, to, departure_time;
    int seats_total;
    double price;
    cout << "Flight number: "; cin >> flight_number; 
    cout << "From: "; cin >> from;
    cout << "To :"; cin >> to;
    cout << "Departure time: "; cin >> departure_time;
    cout << "Price: "; cin >> price;
    flights.emplace_back(flight_number, from, to, departure_time, price);
}

void BookingSystem::add_passenger() {
    string name, surname;
    int passenger_id;
    cout << "Name: "; cin >> name;
    cout << "Surname: "; cin >> surname;
    cout << "Passenger ID: "; cin >> passenger_id;
    passengers.emplace_back(name, surname, passenger_id);
}

void BookingSystem::make_reservation() {
    string flight_number;
    int passenger_id;
    for(auto& x: flights) {
        if(x.get_flightNumber() == flight_number) {
            if(x.reserveSeat()) {
                
            }
        }
    }
}

void BookingSystem::show_flightInfo() {
    for(auto& x: flights) x.showInfo();
}

void BookingSystem::show_reservation() {
    for(auto& x: reservations) x.show();
}


#include "BookingSystem.h"

BookingSystem::BookingSystem() {}

void BookingSystem::add_flight() {
    string flight_number, from, to, departure_time;
    int seats_total;
    double price;
    cout << "Numer lotu: "; cin >> flight_number; 
    cout << "Miasto wylotu: "; cin >> from;
    cout << "Miasto docelowe: "; cin >> to;
    cout << "Godzina odlotu: "; cin >> departure_time;
    cout << "Liczba miejsc: "; cin >> seats_total;
    cout << "Cena biletu: "; cin >> price;
    flights.emplace_back(from, to, flight_number, departure_time, price, seats_total);
}

void BookingSystem::add_passenger() {
    string name, surname, passenger_id;
    cout << "Imię pasażera: "; cin >> name;
    cout << "Nazwisko pasażera: "; cin >> surname;
    passenger_id = "P" + to_string(passenger_counter++);
    passengers.emplace_back(name, surname, passenger_id);

    save_passengers_only();
}

void BookingSystem::make_reservation() {
    string flight_number, passenger_id;
    cout << "ID pasażera: "; cin >> passenger_id;
    cout << "Numer lotu: "; cin >> flight_number;
    for (auto& x : flights) {
        if (x.get_flightNumber() == flight_number) {
            x.show_seats();
            int seat;
            cout << "Wybierz miejsce: "; cin >> seat;
            if (x.reserveSeat(seat)) {
                string resID = "R" + to_string(reservations.size() + 1);
                reservations.emplace_back(flight_number, resID, passenger_id, seat);
                cout << "Rezerwacja zakończona sukcesem! ID rezerwacji: " << resID << ", miejsce: " << seat << endl;

                save_reservations_only();
                return;
            } else {
                cout << "Nie udało się zarezerwować miejsca." << endl;
                return;
            }
        }
    }
    cout << "Nie znaleziono lotu o podanym numerze." << endl;
}

void BookingSystem::show_flightInfo() {
    for (auto& x : flights) {
        x.showInfo();
    }
}

void BookingSystem::show_reservation() {
    string p_id;
    cout << "Podaj ID pasażera: "; cin >> p_id;
    bool found = false;
    for (auto& x : reservations) {
        if (x.getID() == p_id) {
            x.show();
            found = true;
        }
    }
    if (!found) {
        cout << "Brak rezerwacji dla podanego pasażera." << endl;
    }
}

void BookingSystem::cancel_reservation() {
    string p_id, f_numb;
    cout << "Podaj ID pasażera: "; cin >> p_id;
    cout << "Podaj numer lotu: "; cin >> f_numb;

    for (auto it = reservations.begin(); it != reservations.end(); ++it) {
        if (it->getID() == p_id && it->get_flightNumber() == f_numb) {
            reservations.erase(it);
            cout << "Rezerwacja została anulowana." << endl;
            save_reservations_only();
            return;
        }
    }
    cout << "Nie znaleziono takiej rezerwacji." << endl;
}

void BookingSystem::save_data() const {
    ofstream fOut("flights.txt"), pOut("passengers.txt"), rOut("reservations.txt");

    for (const auto& x : flights) {
        fOut << x.get_flightNumber() << " "
             << x.get_origin() << " "
             << x.get_destination() << " "
             << x.get_departure_time() << " "
             << x.get_total_seats() << " "
             << x.get_price() << "\n";
    }

    for (const auto& x : passengers) {
        pOut << x.get_full_name() << " " << x.getID() << "\n";
    }

    for (const auto& x : reservations) {
        rOut << x.getID() << " " << x.get_flightNumber() << " " << x.get_seat() << "\n";
    }
}

void BookingSystem::save_reservations_only() const {
    ofstream rOut("reservations.txt");

    if (!rOut) {
        cout << "[BŁĄD] Nie można otworzyć pliku reservations.txt do zapisu!" << endl;
        return;
    }

    for (const auto& x : reservations) {
        rOut << x.getID() << " " << x.get_flightNumber() << " " << x.get_seat() << "\n";
    }

    cout << "[INFO] Plik reservations.txt został zaktualizowany." << endl;
}

void BookingSystem::save_passengers_only() const {
    ofstream pOut("passengers.txt");

    if (!pOut) {
        cout << "[BŁĄD] Nie można otworzyć pliku passengers.txt do zapisu!" << endl;
        return;
    }

    for (const auto& x : passengers) {
        pOut << x.get_full_name() << " " << x.getID() << "\n";
    }

    cout << "[INFO] Plik passengers.txt został zaktualizowany." << endl;
}

void BookingSystem::load_data() {
    ifstream flightIn("flights.txt"), passengerIn("passengers.txt"), reservationIn("reservations.txt");

    if (!flightIn || !passengerIn || !reservationIn) {
        cout << "[BŁĄD] Nie można otworzyć plików danych!" << endl;
        return;
    }

    flights.clear();
    passengers.clear();
    reservations.clear();
    passenger_counter = 1;

    string flightNumber, origin, destination, departureTime;
    string firstName, lastName, passengerID, loadedFlightID;
    int totalSeats, seatNumber;
    double price;

    while (flightIn >> flightNumber >> origin >> destination >> departureTime >> totalSeats >> price) {
        flights.emplace_back(origin, destination, flightNumber, departureTime, price, totalSeats);
    }

    while (passengerIn >> firstName >> lastName >> passengerID) {
        passengers.emplace_back(firstName, lastName, passengerID);
        if (passengerID[0] == 'P') {
            int number = stoi(passengerID.substr(1));
            if (number >= passenger_counter) {
                passenger_counter = number + 1;
            }
        }
    }

    int reservationCount = 1;
    while (reservationIn >> passengerID >> loadedFlightID >> seatNumber) {
        reservations.emplace_back(loadedFlightID, "R" + to_string(reservationCount++), passengerID, seatNumber);
    }
}


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
    cout << "Total seats: "; cin >> seats_total;
    cout << "Price: "; cin >> price;
    flights.emplace_back(from, to, flight_number, departure_time, price, seats_total);
}

void BookingSystem::add_passenger() {
    string name, surname, passenger_id;
    cout << "First name: "; cin >> name;
    cout << "Second name: "; cin >> surname;
    cout << "Passenger ID: "; cin >> passenger_id;
    passengers.emplace_back(name, surname, passenger_id);

    save_passengers_only(); // <--- OD RAZU zapisujemy po dodaniu pasażera
}

void BookingSystem::make_reservation() {
    string flight_number, passenger_id;
    cout << "Passenger ID: "; cin >> passenger_id;
    cout << "Flight number: "; cin >> flight_number;
    for (auto& x : flights) {
        if (x.get_flightNumber() == flight_number) {
            x.show_seats();
            int seat;
            cout << "Choose your seat: "; cin >> seat;
            if (x.reserveSeat(seat)) {
                string resID = "R" + to_string(reservations.size() + 1);
                reservations.emplace_back(flight_number, resID, passenger_id, seat);
                cout << "Reservation ID: " << resID << ", seat: " << seat << endl;

                save_reservations_only(); // <--- OD RAZU zapisujemy po rezerwacji

                return;
            } else {
                cout << "You can't reserve that seat." << endl;
                return;
            }
        }
    }
    cout << "No such flight." << endl;
}

void BookingSystem::show_flightInfo() {
    for (auto& x : flights) {
        x.showInfo();
    }
}

void BookingSystem::show_reservation() {
    string p_id;
    cout << "Passenger ID: "; cin >> p_id;
    for (auto& x : reservations) {
        if (x.getID() == p_id) {
            x.show();
        }
    }
}

void BookingSystem::cancel_reservation() {
    string p_id, f_numb;
    cout << "Passenger ID: "; cin >> p_id;
    cout << "Which flight do you want to cancel: "; cin >> f_numb;

    for (auto it = reservations.begin(); it != reservations.end(); ++it) {
        if (it->getID() == p_id && it->get_flightNumber() == f_numb) {
            reservations.erase(it);
            cout << "[DEBUG] Rezerwacja usunięta z RAM." << endl;
            save_reservations_only(); // <--- OD RAZU zapisujemy po anulowaniu
            return;
        }
    }
    cout << "No such reservation." << endl;
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
        cout << "[ERROR] Nie można otworzyć reservations.txt do zapisu!" << endl;
        return;
    }

    for (const auto& x : reservations) {
        rOut << x.getID() << " " << x.get_flightNumber() << " " << x.get_seat() << "\n";
    }

    cout << "[INFO] Reservations updated." << endl;
}

void BookingSystem::save_passengers_only() const {
    ofstream pOut("passengers.txt");

    if (!pOut) {
        cout << "[ERROR] Nie można otworzyć passengers.txt do zapisu!" << endl;
        return;
    }

    for (const auto& x : passengers) {
        pOut << x.get_full_name() << " " << x.getID() << "\n";
    }

    cout << "[INFO] Passengers updated." << endl;
}

void BookingSystem::load_data() {
    ifstream fIn("flights.txt"), pIn("passengers.txt"), rIn("reservations.txt");

    if (!fIn || !pIn || !rIn) {
        cout << "[ERROR] Nie można otworzyć plików danych!" << endl;
        return;
    }

    flights.clear();
    passengers.clear();
    reservations.clear();

    string f_numb, origin, destin, time, f_name, s_name, p_id, f_id;
    int seats;
    double price;

    while (fIn >> f_numb >> origin >> destin >> time >> seats >> price) {
        flights.emplace_back(origin, destin, f_numb, time, price, seats);
    }

    while (pIn >> f_name >> s_name >> p_id) {
        passengers.emplace_back(f_name, s_name, p_id);
    }

    int r_count = 1, seat;
    while (rIn >> p_id >> f_id >> seat) {
        reservations.emplace_back(f_id, "R" + to_string(r_count++), p_id, seat);
    }
}

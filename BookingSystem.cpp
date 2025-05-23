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
    string firstName, lastName;
    cout << "Imię pasażera: "; cin >> firstName;
    cout << "Nazwisko pasażera: "; cin >> lastName;
    string passengerID = "P" + to_string(passenger_counter++);
    passengers.emplace_back(firstName, lastName, passengerID);
    cout << "Dodano pasażera z ID: " << passengerID << endl;
}


void BookingSystem::make_reservation() {
    string flight_number, passenger_id;
    cout << "ID pasażera: "; cin >> passenger_id;
    bool passenger_found = false;
    for (const auto& p : passengers) {
        if (p.getID() == passenger_id) {
            passenger_found = true;
            break;
        }
    }
    if (!passenger_found) {
        cout << "Nie znaleziono pasażera o ID: " << passenger_id << ".\n";
        return;
    }

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
                return;
            } else {
                cout << "Nie udało się zarezerwować miejsca (zajęte lub nieprawidłowe).\n";
                return;
            }
        }
    }
    cout << "Nie znaleziono lotu o podanym numerze.\n";
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

void BookingSystem::load_data() {
    ifstream fIn("flights.txt"), pIn("passengers.txt"), rIn("reservations.txt");
    if (!fIn || !pIn || !rIn) {
        cout << "Nie można otworzyć plików danych!" << endl;
        return;
    }
    flights.clear();
    passengers.clear();
    reservations.clear();
    passenger_counter = 1;
    string f_numb, origin, destin, time, f_name, s_name, p_id, f_id;
    int seats;
    double price;
    while (fIn >> f_numb >> origin >> destin >> time >> seats >> price) {
        flights.emplace_back(origin, destin, f_numb, time, price, seats);
    }
    while (pIn >> f_name >> s_name >> p_id) {
        passengers.emplace_back(f_name, s_name, p_id);
        int num = 0;
        for(size_t i = 1; i < p_id.size(); i++){
            num = num * 10 + (p_id[i] - '0');
        }
        if (num >= passenger_counter)
        passenger_counter = num + 1;
    }
    int r_count = 1, seat;
    while (rIn >> p_id >> f_id >> seat) {
        for (auto& f : flights) {
            if (f.get_flightNumber() == f_id) {
            f.reserveSeat(seat);
            reservations.emplace_back(f_id, "R" + to_string(r_count++), p_id, seat);
            break;
            }
        }
    }
}

void BookingSystem::modify_flight() {
    string flight_number;
    cout << "Podaj numer lotu do modyfikacji: ";
    cin >> flight_number;
    for (auto& f : flights) {
        if (f.get_flightNumber() == flight_number) {
            double new_price;
            string new_time;
            cout << "Nowa cena: "; cin >> new_price;
            cout << "Nowa godzina odlotu: "; cin >> new_time;
            f.set_price(new_price);
            f.set_departure_time(new_time);
            cout << "Zmieniono dane lotu.\n";
            return;
        }
    }
    cout << "Nie znaleziono lotu.\n";
}

void BookingSystem::remove_flight() {
    string flight_number;
    cout << "Podaj numer lotu do usunięcia: ";
    cin >> flight_number;
    for (auto it = flights.begin(); it != flights.end(); ++it) {
        if (it->get_flightNumber() == flight_number) {
            flights.erase(it);
            cout << "Lot usunięty.\n";
            return;
        }
    }
    cout << "Nie znaleziono lotu.\n";
}

void BookingSystem::show_passengers() const {
    for (const auto& p : passengers) {
        cout << p.get_full_name() << " | ID: " << p.getID() << endl;
    }
}

void BookingSystem::modify_passenger() {
    string id;
    cout << "Podaj ID pasażera: ";
    cin >> id;
    for (auto& p : passengers) {
        if (p.getID() == id) {
            string n, s;
            cout << "Nowe imię: "; cin >> n;
            cout << "Nowe nazwisko: "; cin >> s;
            p.set_name(n);
            p.set_surname(s);
            cout << "Zmieniono dane pasażera.\n";
            return;
        }
    }
    cout << "Nie znaleziono pasażera.\n";
}

void BookingSystem::remove_passenger() {
    string id;
    cout << "Podaj ID pasażera do usunięcia: ";
    cin >> id;
    for (auto it = passengers.begin(); it != passengers.end(); ++it) {
        if (it->getID() == id) {
            passengers.erase(it);
            cout << "Usunięto pasażera.\n";
            return;
        }
    }
    cout << "Nie znaleziono pasażera.\n";
}

void BookingSystem::modify_reservation() {
    string p_id, f_numb;
    cout << "Podaj ID pasażera: "; cin >> p_id;
    cout << "Numer lotu: "; cin >> f_numb;

    for (auto& r : reservations) {
        if (r.getID() == p_id && r.get_flightNumber() == f_numb) {
            for (auto& f : flights) {
                if (f.get_flightNumber() == f_numb) {
                    int new_seat;
                    f.show_seats();
                    cout << "Nowe miejsce: "; cin >> new_seat;
                    if (f.reserveSeat(new_seat)) {
                        r.set_seat(new_seat);
                        cout << "Zmieniono miejsce na " << new_seat << ".\n";
                        return;
                    } else {
                        cout << "To miejsce jest już zajęte lub nieprawidłowe. Spróbuj inne.\n";
                        return;
                    }
                }
            }
        }
    }
    cout << "Nie znaleziono rezerwacji.\n";
}


void BookingSystem::filter_by_destination() const {
    string dest;
    cout << "Podaj miasto docelowe: ";
    cin >> dest;
    bool found = false;
    for (const auto& f : flights) {
        if (f.get_destination() == dest) {
            f.showInfo();
            found = true;
        }
    }
    if (!found) {
        cout << "Brak lotów do " << dest << ".\n";
    }
}

void BookingSystem::sort_flights_by_price() {
    sort(flights.begin(), flights.end(), [](const Flight& a, const Flight& b) {
        return a.get_price() < b.get_price();
    });
    cout << "Loty posortowane po cenie (rosnąco):\n";
    show_flightInfo();
}


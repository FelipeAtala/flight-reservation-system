#include <iostream>
#include <windows.h>
#include "BookingSystem.h"
using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    BookingSystem system;
    system.load_data();

    int choice;
    do {
        cout << "\n=== SYSTEM REZERWACJI LOTÓW ===\n";
        cout << "1. Pokaż loty\n";
        cout << "2. Dodaj pasażera\n";
        cout << "3. Zarezerwuj lot\n";
        cout << "4. Pokaż rezerwacje pasażera\n";
        cout << "5. Anuluj rezerwację\n";
        cout << "6. Wyjście\n";
        cout << "Wybór: ";
        cin >> choice;
        if (choice == 1) system.show_flightInfo();
        else if (choice == 2) system.add_passenger();
        else if (choice == 3) system.make_reservation();
        else if (choice == 4) system.show_reservation();
        else if (choice == 5) system.cancel_reservation();
    } while (choice != 6);
    system.save_data();
    return 0;
}

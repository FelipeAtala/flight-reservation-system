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
        cout << "2. Dodaj lot\n";
        cout << "3. Dodaj pasażera\n";
        cout << "4. Zarezerwuj lot\n";
        cout << "5. Pokaż rezerwacje pasażera\n";
        cout << "6. Anuluj rezerwację\n";
        cout << "7. Filtruj loty po mieście docelowym\n";
        cout << "8. Sortuj loty po cenie\n";
        cout << "9. Modyfikuj lot\n";
        cout << "10. Usuń lot\n";
        cout << "11. Pokaż pasażerów\n";
        cout << "12. Modyfikuj pasażera\n";
        cout << "13. Usuń pasażera\n";
        cout << "14. Modyfikuj rezerwację\n";
        cout << "15. Wyjście\n";
        cout << "Wybór: ";
        cin >> choice;
        if (choice == 1) system.show_flightInfo();
        else if (choice == 2) system.add_flight();
        else if (choice == 3) system.add_passenger();
        else if (choice == 4) system.make_reservation();
        else if (choice == 5) system.show_reservation();
        else if (choice == 6) system.cancel_reservation();
        else if (choice == 7) system.filter_by_destination();
        else if (choice == 8) system.sort_flights_by_price();
        else if (choice == 9) system.modify_flight();
        else if (choice == 10) system.remove_flight();
        else if (choice == 11) system.show_passengers();
        else if (choice == 12) system.modify_passenger();
        else if (choice == 13) system.remove_passenger();
        else if (choice == 14) system.modify_reservation();
    } while (choice != 15);
    system.save_data();
    return 0;
}

#pragma once
#include <string>
using namespace std;

class Passenger {
private:
    string name, surname, passenger_id;
public:
    Passenger(string n, string sn, string i);
    string getID() const;
    string get_full_name() const;
};
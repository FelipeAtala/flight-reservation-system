#pragma once
#include <string>
using namespace std;

class Passenger {
private:
    string name, surname;
    int passanger_id;
public:
    Passenger(string n, string sn, int i);
};
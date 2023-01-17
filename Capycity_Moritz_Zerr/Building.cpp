


#include <string>
#include "Building.h"

using namespace std;


Building::Building() {};

Building::Building(string l, int gp, int leist) :label(l), grundpreis(gp), leistung(leist) {
    gesamtpreisGebaeude = berechnePreis();
}

// Einzelpreis eines Gebäudes berechnen Grundpreis + Preise der Materialien
int Building::berechnePreis() {
    int p = 0;

    for (auto iter = matMap.begin(); iter != matMap.end(); iter++) {
        p += iter->first->preis * iter->second;
    }

    return p + grundpreis;
}

// Materialien und Preis des Gebäudes auflisten -> string erstellen
string Building::auflisten() {
    string liste = "Materialien: ";

    for (auto iter = matMap.begin(); iter != matMap.end(); iter++) {
        liste += iter->first->materialtyp + ", ";
    }

    liste += "Einzelpreis Gebaeude: ";
    liste += to_string(berechnePreis());
    return liste;
}

bool Building::operator!=(const Building b) {
    return b.label != label;
}


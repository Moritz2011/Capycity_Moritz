


#include <string>
#include "Building.h"

using namespace std;


Building::Building() {};
Building::Building(string l, int gp, vector<Material> ma) :label(l), grundpreis(gp), matVec(ma) {
    gesamtpreisGebaeude = berechnePreis();
}

// Einzelpreis eines Gebäudes berechnen Grundpreis + Preise der Materialien
int Building::berechnePreis() {
    int p = 0;
    for (int i = 0; i < matVec.size(); i++)
        p += matVec[i].preis;
    return p + grundpreis;
}

// Materialien und Preis des Gebäudes auflisten -> string erstellen
string Building::auflisten() {
    string liste = "Materialien: ";
    for (int i = 0; i < matVec.size(); i++) {
        liste += matVec[i].materialtyp;
        liste += ", ";
    }
    liste += "Einzelpreis Gebaeude: ";
    liste += to_string(berechnePreis());
    return liste;
}

bool Building::operator!=(const Building b) {
    return b.label != label;
}


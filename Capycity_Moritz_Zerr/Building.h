#pragma once
/*
    Moritz Zerr
    14.1.2023 Kapitel 3

    Map als Attribut innerhalb der Klasse -> Carlas Idee, da
    es für mich einfach viel logischer erscheint die Verwaltung der Materialien
    gleich direkt in der jeweiligen Klasse zu definieren als in einer extra Klasse.
*/


#include <string>
#include "Material.h"
#include <vector>
#include <map>

using namespace std;

class Building {
public:
    int grundpreis;
    int gesamtpreisGebaeude;
    string label;
    int leistung;
    map<Material*, int> matMap; // Material* "besser" da wenn nur Material man < überladen müsste

    Building();
    Building(string l, int gp, int leist);

    int berechnePreis();

    string auflisten();

    int getLeistung() {
        return leistung;
    }

    bool operator!=(const Building b);

};
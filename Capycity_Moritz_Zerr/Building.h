#pragma once



#include <string>
#include "Material.h"
#include <vector>

using namespace std;

class Building {
public:
    int grundpreis;
    int gesamtpreisGebaeude;
    string label;
    vector<Material> matVec;

    Building();
    Building(string l, int gp, vector<Material> ma);

    int berechnePreis();

    string auflisten();

    bool operator!=(const Building b);

};
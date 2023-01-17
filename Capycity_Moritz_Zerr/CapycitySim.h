#pragma once


#include <iostream>
#include <vector>
#include <map>
#include "Building.h"

class CapycitySim {
private:
    vector<vector<Building> >* baubereich; // wird im Konstruktor erstellt
    int rows, columns;
public:
    CapycitySim(int rows, int columns);

    void start();
    void printBaubereich();

};
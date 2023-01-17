#pragma once

#include "Building.h"
#include <vector>

using namespace std;

class Blueprint {
public:
	vector<vector<Building> >* baubereich; // wird im Konstruktor erstellt
	int rows, columns;
	double kennzahl;

	Blueprint(int rows, int columns);

	double berechneKennzahl();

	void printBaubereich();

	void setzeGebaeude(Building a, int startRow, int startColumn, int breite, int hoehe);

	// Funktor zur Überprüfung, ob zwei Pläne geich sind
	bool operator() (Blueprint b);

	// Hilfsmethode zum reset
	void resetPlan(int r, int c);

};
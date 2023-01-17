/*
    Moritz Zerr
    13.1.2023 Kapitel 1
    13.1.2023 und 14.1.2023 Kapitel 2
    14.1.2023 Kapitel 3
*/

#include <iostream>
#include <vector>
#include <map>
#include "CapycitySim.h"

using namespace std;

int main() {

    int rows, columns;

    // Eingabe der Größe des Feldes
    cout << "Bitte Zeilen des Baubereichs eingeben: ";
    cin >> rows;
    cout << endl << "Bitte Spalten des Baubereichs eingeben: ";
    cin >> columns;
    cout << endl;

    CapycitySim* game = new CapycitySim(rows, columns);
    game->start();

    return 0;
}
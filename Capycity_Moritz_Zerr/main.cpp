

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
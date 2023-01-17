

#include "CapycitySim.h"
#include <iostream>
#include "Leer.h"
#include "Wasserkraftwerk.h"
#include "Windkraftwerk.h"
#include "Solarpanele.h"
#include "Blueprint.h"
#include <algorithm>

using namespace std;

// Konstruktor
CapycitySim::CapycitySim() {}

// Enth�llt die eigentliche Spiellogik
void CapycitySim::start() {
    // n�tige Variablen
    int hoehe, breite, startRow, startColumn;
    int auswahlMenu, auswahlGeb;
    bool running = true;
    bool beenden = false;
    bool enthalten;

    int rows, columns;
    // Eingabe der Gr��e des Feldes
    cout << "Bitte Zeilen des Baubereichs eingeben: ";
    cin >> rows;
    cout << "Bitte Spalten des Baubereichs eingeben: ";
    cin >> columns;
    cout << endl;

    Blueprint bp(rows, columns);

    bp.printBaubereich(); // Baubereich am Anfang ausgeben

    // Men�
    while (running == true) {

        cout << "Bitte waehle den naechsten Schritt:" << endl;
        cout << "1. Gebaeude setzen" << endl;
        cout << "2. Bereich loeschen" << endl;
        cout << "3. Ausgabe des aktuellen Bauplans" << endl;
        cout << "4. Erstellung eines neuen Plans" << endl;
        cout << "5. Ausgabe aller Plaene" << endl;
        cout << "6. Beenden des Programms" << endl << endl;

        cin >> auswahlMenu; // Eingabe vom Nutzer f�r die Men�auswahl

        switch (auswahlMenu) {
            //--------------- Auswahl Geb�ude setzen -----------------------
        case 1: {
            Building geb = Leer(); // ist quasi das Geb�ude, dass gesetzt werden soll
            beenden = false;
            cout << "Gebaeudeart waehlen" << endl;
            cout << "1. Wasserkraftwerk" << endl;
            cout << "2. Windkraftwerk" << endl;
            cout << "3. Solarpanel\n" << endl;
            cin >> auswahlGeb; // Eingabe vom Nutzer f�r die Geb�udeauswahl

            switch (auswahlGeb) {
            case 1:
                geb = Wasserkraftwerk();
                break;
            case 2:
                geb = Windkraftwerk();
                break;
            case 3:
                geb = Solarpanele();
            }

            // Gr��e und Position abfragen ( hoehe,breite, startRow, startColumn)
            cout << "Startzeile (von oben beginnend bei 0) eingeben\n";
            cin >> startRow;

            cout << "Startspalte (von links beginnend bei 0) eingben\n";
            cin >> startColumn;

            cout << "Breite (Spaltenanzahl) des Geb�udes eingben\n";
            cin >> breite;

            cout << "Hoehe (Zeilenanzahl) des Geb�udes eingeben\n";
            cin >> hoehe;

            // �berpr�fen, ob das m�gliche Werte sind
            // Liegt der Start �berhaupt in meinem Baubereich?
            if (startRow >= rows || startRow < 0 || startColumn < 0 || startColumn >= columns) {
                beenden = true;
                cout << "Gebaeudegroesse ist unpassend\n";
            }
            // Wenn oben erf�llt, liegt es auch inkl. der L�nge und Breite immernoch in meinem Baubereich?
            if (beenden != true && (startRow + hoehe) > rows || (startColumn + breite) > columns) {
                beenden = true;
                cout << "Gebaeudegroesse ist unpassend\n";
            }
            // wenn beenden noch false ist dann hat Geb�ude passende Gr��e
            if (beenden == false) {
                // pr�fen ob Kollisonen mit anderen Geb�uden vorliegen
                for (int i = startRow; i < startRow + hoehe; i++) {
                    for (int j = startColumn; j < startColumn + breite; j++) {
                        if (bp.baubereich->at(i).at(j) != Leer()) {
                            cout << "Obacht Kollision mit anderem Gebaeude, Abbruch!\n";
                            beenden = true;
                            break;
                        }
                    }
                    if (beenden == true)    // wenn true beenden, da Kollision vorliegt
                        break;
                }
            }
            if (beenden == true) {
                cout << "Gebaeude setzen nicht moeglich, da Kollision!\n";
                break; // beendet also case 1
            }

            // sonst Geb�ude setzen
            bp.setzeGebaeude(geb, startRow, startColumn, breite, hoehe);

            beenden = false; // zur�cksetzen von beenden
            break;
        }
              //--------------- Auswahl Bereich l�schen -----------------------
        case 2:
            cout << "Startzeile (von oben beginnend bei 0) eingeben\n";
            cin >> startRow;

            cout << "Startspalte (von links beginnend bei 0) eingben\n";
            cin >> startColumn;

            cout << "Breite (Spaltenanzahl) des zu loeschenden Bereichs eingben\n";
            cin >> breite;

            cout << "Hoehe (Zeilenanzahl) des zu loeschenden Bereichs eingeben\n";
            cin >> hoehe;

            // Bereich pr�fen
            if (startRow >= rows || startRow < 0 || startColumn < 0 || startColumn >= columns) {
                beenden = true;
                cout << "Ungueltiger Bereich\n";
            }
            // Wenn oben erf�llt, liegt es auch inkl. der L�nge und Breite immernoch in meinem Baubereich?
            if (beenden != true && (rows - hoehe) < 0 || (columns - breite) < 0) {
                beenden = true;
                cout << "Groe�e ist unpassend\n";
            }

            // Falls Bereich passt, dann zur�cksetzen dieser Felder
            if (beenden != true)
                bp.setzeGebaeude(Leer(), startRow, startColumn, breite, hoehe);

            beenden = false; // zur�cksetzen von beenden
            break;

            //--------------- Auswahl Ausgabe des Bauplans-----------------------
        case 3:
            // Ausgabe des Baubereichs
            bp.printBaubereich();
            break;

            //--------------- Auswahl Erstellung eines neuen Plans-----------------------
        case 4:
            enthalten = false;
            // pr�fen ob aktueller Plan schon vorhanden ist
            for (int i = 0; i < plaene.size(); i++) {
                if (bp(plaene[i]) == true) {
                    cout << "Aktueller Plan ist bereits vorhanden, aktueller Plan wird verworfen!\n\n";
                    enthalten = true;
                    break;
                }
            }

            // falls false, muss aktueller Plan im Vector gespeichert werden, ansonsten nicht
            if (enthalten == false)
                plaene.push_back(bp);

            // erneute Eingabe der Gr��e des Feldes
            cout << "Bitte Zeilen des Baubereichs eingeben: ";
            cin >> rows;
            cout << "Bitte Spalten des Baubereichs eingeben: ";
            cin >> columns;
            cout << endl;

            // Hier resetten und wieder auf Leer setzen alles
            bp.resetPlan(rows, columns);

            bp.printBaubereich(); // Baubereich am Anfang ausgeben

            break;

            //--------------- Auswahl alle Pl�ne drucken-----------------------
        case 5:
            printAll();
            break;

            //--------------- Auswahl Programm beenden -----------------------
        case 6:
            cout << "Programm beendet\n" << endl;
            running = false;
            break;
        } // ende Switch

    } // ende while loop
}

// Ausdrucken aller Pl�ne
void CapycitySim::printAll() {

    // Lambda Funktion zur absteigenden Sortierung anhand der Kennzahlen
    //auto sortierLambda = [](Blueprint a, Blueprint b)->bool {
      //  return a.kennzahl > b.kennzahl;
    //};

    sort(plaene.begin(), plaene.end(), [](Blueprint a, Blueprint b)->bool {
        return a.kennzahl > b.kennzahl;
        });

    for (int i = 0; i < plaene.size(); i++) {
        plaene[i].printBaubereich();
    }
}


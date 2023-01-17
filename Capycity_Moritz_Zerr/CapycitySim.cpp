

#include "CapycitySim.h"
#include <iostream>
#include "Leer.h"
#include "Wasserkraftwerk.h"
#include "Windkraftwerk.h"
#include "Solarpanele.h"


using namespace std;

// Konstruktor, in dem der Baubereich gleich initialisiert wird
CapycitySim::CapycitySim(int r, int c) {
    rows = r;
    columns = c;
    baubereich = new vector<vector<Building> >(rows);
    // Initialisierung des Baubereichs, zu Beginn alles auf Leer
    for (int x = 0; x < rows; x++) {
        baubereich->at(x) = vector<Building>(columns);
        for (int y = 0; y < columns; y++) {
            baubereich->at(x).at(y) = Leer();
        }
    }
}

// print den Baubereich
void CapycitySim::printBaubereich() {
    // Ausdrucken des Plans mit Labels
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << baubereich->at(i).at(j).label << "\t\t";
        }
        cout << "\n\n";
    }
    int gesamtpreisGebaeude = 0;
    // Ausrucken der Liste von Gebäuden mit ihren Materialien+Einzelpreis
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (baubereich->at(i).at(j) != Leer()) {
                cout << baubereich->at(i).at(j).label << ": " << baubereich->at(i).at(j).auflisten() << endl;
                gesamtpreisGebaeude += baubereich->at(i).at(j).berechnePreis();
            }
        }
    }
    // Ausdrucken des Gesamtpreises
    cout << "Gesamtpreis aller Gebaeude: " << gesamtpreisGebaeude << endl;
}

// Enthällt die eigentliche Spiellogik
void CapycitySim::start() {
    // nötige Variablen
    int hoehe, breite, startRow, startColumn;
    int auswahlMenu, auswahlGeb;
    bool running = true;
    bool beenden = false;

    printBaubereich(); // Baubereich am Anfang ausgeben

    // Menü
    while (running == true) {

        cout << "Bitte waehle den naechsten Schritt:\n" << endl;
        cout << "1. Gebaeude setzen" << endl;
        cout << "2. Bereich loeschen" << endl;
        cout << "3. Ausgabe des aktuellen Bauplans" << endl;
        cout << "4. Beenden des Programms\n" << endl;

        cin >> auswahlMenu; // Eingabe vom Nutzer für die Menüauswahl

        switch (auswahlMenu) {
            //--------------- Auswahl Gebäude setzen -----------------------
        case 1: {
            Building geb = Leer(); // ist quasi das Gebäude, dass gesetzt werden soll
            beenden = false;
            cout << "Gebaeudeart waehlen" << endl;
            cout << "1. Wasserkraftwerk" << endl;
            cout << "2. Windkraftwerk" << endl;
            cout << "3. Solarpanel\n" << endl;
            cin >> auswahlGeb; // Eingabe vom Nutzer für die Gebäudeauswahl

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

            // Größe und Position abfragen ( hoehe,breite, startRow, startColumn)
            cout << "Startzeile (von oben beginnend bei 0) eingeben\n";
            cin >> startRow;

            cout << "Startspalte (von links beginnend bei 0) eingben\n";
            cin >> startColumn;

            cout << "Breite (Spaltenanzahl) des Gebäudes eingben\n";
            cin >> breite;

            cout << "Hoehe (Zeilenanzahl) des Gebäudes eingeben\n";
            cin >> hoehe;

            // Überprüfen, ob das mögliche Werte sind
            // Liegt der Start überhaupt in meinem Baubereich?
            if (startRow >= rows || startRow < 0 || startColumn < 0 || startColumn >= columns) {
                beenden = true;
                cout << "Gebaeudegroeße ist unpassend\n";
            }
            // Wenn oben erfüllt, liegt es auch inkl. der Länge und Breite immernoch in meinem Baubereich?
            if (beenden != true && (rows - hoehe) < 0 || (columns - breite) < 0) {
                beenden = true;
                cout << "Gebaeudegroeße ist unpassend\n";
            }
            // wenn beenden noch false ist dann hat Gebäude passende Größe
            if (beenden == false) {
                // prüfen ob Kollisonen mit anderen Gebäuden vorliegen
                for (int i = startColumn; i < startColumn + hoehe; i++) {
                    for (int j = startRow; j < startRow + breite; j++) {
                        if (baubereich->at(i).at(j) != Leer()) {
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

            // sonst Gebäude setzen
            for (int i = startColumn; i < startColumn + hoehe; i++)
                for (int j = startRow; j < startRow + breite; j++)
                    baubereich->at(i).at(j) = geb;

            beenden = false; // zurücksetzen von beenden
            break;
        }
              //--------------- Auswahl Bereich löschen -----------------------
        case 2:
            cout << "Startzeile (von oben beginnend bei 0) eingeben\n";
            cin >> startRow;

            cout << "Startspalte (von links beginnend bei 0) eingben\n";
            cin >> startColumn;

            cout << "Breite (Spaltenanzahl) des zu loeschenden Bereichs eingben\n";
            cin >> breite;

            cout << "Hoehe (Zeilenanzahl) des zu loeschenden Bereichs eingeben\n";
            cin >> hoehe;

            // Bereich prüfen
            if (startRow >= rows || startRow < 0 || startColumn < 0 || startColumn >= columns) {
                beenden = true;
                cout << "Ungueltiger Bereich\n";
            }
            // Wenn oben erfüllt, liegt es auch inkl. der Länge und Breite immernoch in meinem Baubereich?
            if (beenden != true && (rows - hoehe) < 0 || (columns - breite) < 0) {
                beenden = true;
                cout << "Groeße ist unpassend\n";
            }

            // Falls Bereich passt, dann zurücksetzen dieser Felder
            if (beenden != true) {
                for (int i = startColumn; i < startColumn + hoehe; i++)
                    for (int j = startRow; j < startRow + breite; j++)
                        baubereich->at(i).at(j) = Leer();
            }
            beenden = false; // zurücksetzen von beenden
            break;

            //--------------- Auswahl Ausgabe des Bauplans-----------------------
        case 3:
            // Ausgabe des Baubereichs
            printBaubereich();
            break;

            //--------------- Auswahl Programm beenden -----------------------
        case 4:
            cout << "Programm beendet\n" << endl;
            running = false;
            break;
        } // ende Switch

    } // ende while loop
}
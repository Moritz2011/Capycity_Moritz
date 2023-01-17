

#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum Gebaeude { Wasserkraftwerk, Windkraftwerk, Solarpanele, Leer };

int main() {

    // Map um printen leichter zu ermöglichen, Alternative vllt als Funktion
    map<Gebaeude, string> gebaeude_map{
            {Gebaeude::Leer, "leer"},
            {Gebaeude::Wasserkraftwerk, "Wasserkraftwerk"},
            {Gebaeude::Windkraftwerk, "Windkraftwerk"},
            {Gebaeude::Solarpanele, "Solarpanel"}

    };

    // nötige Variablen
    int rows, columns;
    int hoehe, breite, startRow, startColumn;
    int auswahlMenu, auswahlGeb;
    bool running = true;
    bool beenden = false;

    cout << "Bitte Zeilen des Baubereichs eingeben: ";
    cin >> rows;
    cout << endl << "Bitte Spalten des Baubereichs eingeben: ";
    cin >> columns;
    cout << endl;


    //  vector<vector<Gebaeude> >baubereich(laenge, vector<Gebaeude>(breite, Leer)); // als Einzeiler ohne Schleifen

    vector<vector<Gebaeude> >baubereich(rows);

    // Initialisierung des Baubereichs, zu Beginn alles auf Leer
    for (int x = 0; x < rows; x++) {
        baubereich.at(x) = vector<Gebaeude>(columns);
        for (int y = 0; y < columns; y++) {
            baubereich.at(x).at(y) = Leer;
        }
    }

    // Ausgabe des Baubereichs zu Beginn
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << gebaeude_map[baubereich[i][j]] << "\t\t";
        }
        cout << "\n\n";
    }

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
        case 1:
            Gebaeude geb; // ist quasi das Gebäude, dass gesetzt werden soll
            beenden = false;
            cout << "Gebaeudeart waehlen" << endl;
            cout << "1. Wasserkraftwerk" << endl;
            cout << "2. Windkraftwerk" << endl;
            cout << "3. Solarpanel\n" << endl;
            cin >> auswahlGeb; // Eingabe vom Nutzer für die Gebäudeauswahl

            switch (auswahlGeb) {
            case 1:
                geb = Wasserkraftwerk;
                break;
            case 2:
                geb = Windkraftwerk;
                break;
            case 3:
                geb = Solarpanele;
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
                        if (baubereich[i][j] != Leer) {
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
                    baubereich[i][j] = geb;

            beenden = false; // zurücksetzen von beenden
            break;

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
                        baubereich[i][j] = Leer;
            }
            beenden = false; // zurücksetzen von beenden
            break;

            //--------------- Auswahl Ausgabe des Bauplans-----------------------
        case 3:
            // Ausgabe des Baubereichs
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    cout << gebaeude_map[baubereich[i][j]]; cout << "\t\t";
                }
                cout << "\n\n";
            }
            break;

            //--------------- Auswahl Programm beenden -----------------------
        case 4:
            cout << "Programm beendet\n" << endl;
            running = false;
            break;
        } // ende Switch

    } // ende while loop


    return 0;
}
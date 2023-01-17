

#include <iostream>
#include <vector>
#include <map>

using namespace std;

enum Gebaeude { Wasserkraftwerk, Windkraftwerk, Solarpanele, Leer };

int main() {

    // Map um printen leichter zu erm�glichen, Alternative vllt als Funktion
    map<Gebaeude, string> gebaeude_map{
            {Gebaeude::Leer, "leer"},
            {Gebaeude::Wasserkraftwerk, "Wasserkraftwerk"},
            {Gebaeude::Windkraftwerk, "Windkraftwerk"},
            {Gebaeude::Solarpanele, "Solarpanel"}

    };

    // n�tige Variablen
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

    // Men�
    while (running == true) {

        cout << "Bitte waehle den naechsten Schritt:\n" << endl;
        cout << "1. Gebaeude setzen" << endl;
        cout << "2. Bereich loeschen" << endl;
        cout << "3. Ausgabe des aktuellen Bauplans" << endl;
        cout << "4. Beenden des Programms\n" << endl;

        cin >> auswahlMenu; // Eingabe vom Nutzer f�r die Men�auswahl

        switch (auswahlMenu) {
            //--------------- Auswahl Geb�ude setzen -----------------------
        case 1:
            Gebaeude geb; // ist quasi das Geb�ude, dass gesetzt werden soll
            beenden = false;
            cout << "Gebaeudeart waehlen" << endl;
            cout << "1. Wasserkraftwerk" << endl;
            cout << "2. Windkraftwerk" << endl;
            cout << "3. Solarpanel\n" << endl;
            cin >> auswahlGeb; // Eingabe vom Nutzer f�r die Geb�udeauswahl

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
                cout << "Gebaeudegroe�e ist unpassend\n";
            }
            // Wenn oben erf�llt, liegt es auch inkl. der L�nge und Breite immernoch in meinem Baubereich?
            if (beenden != true && (rows - hoehe) < 0 || (columns - breite) < 0) {
                beenden = true;
                cout << "Gebaeudegroe�e ist unpassend\n";
            }
            // wenn beenden noch false ist dann hat Geb�ude passende Gr��e
            if (beenden == false) {
                // pr�fen ob Kollisonen mit anderen Geb�uden vorliegen
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

            // sonst Geb�ude setzen
            for (int i = startColumn; i < startColumn + hoehe; i++)
                for (int j = startRow; j < startRow + breite; j++)
                    baubereich[i][j] = geb;

            beenden = false; // zur�cksetzen von beenden
            break;

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
            if (beenden != true) {
                for (int i = startColumn; i < startColumn + hoehe; i++)
                    for (int j = startRow; j < startRow + breite; j++)
                        baubereich[i][j] = Leer;
            }
            beenden = false; // zur�cksetzen von beenden
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
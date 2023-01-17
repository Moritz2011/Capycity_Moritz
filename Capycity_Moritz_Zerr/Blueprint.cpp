#include "Blueprint.h"
#include <iostream>
#include "Leer.h"
#include "Wasserkraftwerk.h"
#include "Windkraftwerk.h"
#include "Solarpanele.h"
#include <iomanip>

Blueprint::Blueprint(int r, int c) {
    kennzahl = 0;
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

// Kennzahl berechnen und zurückgeben
double Blueprint::berechneKennzahl() {
    double gesamtLeistung = 0; // um die Summe jeweils zu bekommen
    double gessamtPreis = 0;
    double gesamtFlaeche = 0;
    kennzahl = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            gesamtLeistung += baubereich->at(i).at(j).leistung;
            gessamtPreis += baubereich->at(i).at(j).gesamtpreisGebaeude;
            if (baubereich->at(i).at(j) != Leer())
                gesamtFlaeche += 1;
        }
    }
    if (gesamtFlaeche == 0.0)
        return kennzahl; // ist standardmäßg 0 wenn nichts gebaut ist
    else
        kennzahl = gesamtLeistung / (gessamtPreis * gesamtFlaeche);
    return kennzahl;
}

// print den Baubereich
void Blueprint::printBaubereich() {
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
    // Ausdrucken der Kennzahl
    cout << "Kennzahl des Plans: " << fixed << setprecision(4) << berechneKennzahl() << endl << endl;
}

// Gebaeude setzen
void Blueprint::setzeGebaeude(Building a, int startRow, int startColumn, int breite, int hoehe) {
    for (int i = startRow; i < startRow + hoehe; i++)
        for (int j = startColumn; j < startColumn + breite; j++)
            baubereich->at(i).at(j) = a;
}

// Funktor zur Überprüfung, ob zwei Pläne geich sind
bool Blueprint::operator() (Blueprint b) {

    // wenn Größe schon anders ist, dann sind sie ungleich
    if (rows != b.rows || columns != b.columns) {
        return false;
    }

    // Jedes Element des Bauplans überprüfen
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            if (baubereich->at(i).at(j) != b.baubereich->at(i).at(j)) {
                return false;
                break;
            }
    }
    return true;;
}

void Blueprint::resetPlan(int r, int c) {
    kennzahl = 0;
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


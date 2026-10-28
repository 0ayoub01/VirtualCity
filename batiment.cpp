#include "batiment.h"

Batiment::Batiment() {
    id = 0;
    nom = "";
    type = "";
    consommationEau = 0.0;
    consommationElectricite = 0.0;
    effetSatisfaction = 0;
    coutConstruction = 0.0;
}

Batiment::Batiment(int i, string n, string t, double eau, double elec, int sat, double cout) {
    id = i;
    nom = n;
    type = t;
    consommationEau = eau;
    consommationElectricite = elec;
    effetSatisfaction = sat;
    coutConstruction = cout;
}

void Batiment::afficherDetails() {
    cout << "=== Batiment ===" << endl;
    cout << "ID: " << id << endl;
    cout << "Nom: " << nom << endl;
    cout << "Type: " << type << endl;
    cout << "Consommation Eau: " << consommationEau << " L/cycle" << endl;
    cout << "Consommation Electricite: " << consommationElectricite << " kWh/cycle" << endl;
    cout << "Effet Satisfaction: " << effetSatisfaction << endl;
    cout << "Cout Construction: " << coutConstruction << " $" << endl;
}

void Batiment::calculerImpactRessources(double& eau, double& electricite) {
    eau = eau - consommationEau;
    electricite = electricite - consommationElectricite;
}

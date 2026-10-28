#include "usine.h"

Usine::Usine() : Batiment() {
    productionRessources = 0.0;
    pollution = 0.0;
}

Usine::Usine(int id, string nom)
    : Batiment(id, nom, "Ressource", 20.0, 50.0, -5, 100000.0) {
    productionRessources = 100.0;
    pollution = 15.0;
}

void Usine::afficherDetails() {
    Batiment::afficherDetails();
    cout << "Production Ressources: " << productionRessources << endl;
    cout << "Pollution: " << pollution << endl;
}

double Usine::produireRessources() {
    return productionRessources;
}

double Usine::calculerPollution() {
    return pollution;
}

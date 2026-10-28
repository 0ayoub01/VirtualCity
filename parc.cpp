#include "parc.h"

Parc::Parc() : Batiment() {
    surface = 0.0;
    effetBienEtre = 0;
}

Parc::Parc(int id, string nom, double surf)
    : Batiment(id, nom, "Service", 5.0, 2.0, 10, 30000.0) {
    surface = surf;
    effetBienEtre = 10;
}

int Parc::ameliorerBienEtre() {
    int amelioration = (int)(surface / 100.0) + effetBienEtre;
    return amelioration;
}

void Parc::afficherDetails() {
    Batiment::afficherDetails();
    cout << "Surface: " << surface << " m2" << endl;
    cout << "Effet Bien-Etre: " << effetBienEtre << endl;
}

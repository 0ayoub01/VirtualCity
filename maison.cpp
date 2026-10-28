#include "maison.h"

Maison::Maison() : Batiment() {
    capaciteHabitants = 0;
    habitantsActuels = 0;
}

Maison::Maison(int id, string nom, int capacite)
    : Batiment(id, nom, "Habitation", 10.0, 15.0, 5, 50000.0) {
    capaciteHabitants = capacite;
    habitantsActuels = 0;
}

bool Maison::ajouterHabitants(int nb) {
    if (habitantsActuels + nb <= capaciteHabitants) {
        habitantsActuels = habitantsActuels + nb;
        return true;
    }
    return false;
}

bool Maison::retirerHabitants(int nb) {
    if (habitantsActuels >= nb) {
        habitantsActuels = habitantsActuels - nb;
        return true;
    }
    return false;
}

void Maison::afficherDetails() {
    Batiment::afficherDetails();
    cout << "Capacite Habitants: " << capaciteHabitants << endl;
    cout << "Habitants Actuels: " << habitantsActuels << endl;

}

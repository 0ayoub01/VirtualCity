#ifndef MAISON_H
#define MAISON_H

#include "batiment.h"

class Maison : public Batiment
{
private:
    int capaciteHabitants;
    int habitantsActuels;

public:
    Maison();
    Maison(int id, string nom, int capacite);

    bool ajouterHabitants(int nb);
    bool retirerHabitants(int nb);
    void afficherDetails();

    int getCapaciteHabitants() { return capaciteHabitants; }
    int getHabitantsActuels() { return habitantsActuels; }
    void setHabitantsActuels(int nb) { habitantsActuels = nb; }
    void setCapaciteHabitants(int c) { capaciteHabitants = c; }
};

#endif

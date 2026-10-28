#ifndef SIMULATION_H
#define SIMULATION_H

#include "ville.h"
#include <string>
#include <vector>
using namespace std;

struct Evenement {
    string nom;
    string description;
    int impactSatisfaction;
    double impactEau;
    double impactElectricite;
    double impactPollution;
};

class Simulation
{
private:
    int cycleActuel;
    Ville* ville;
    vector<Evenement> evenements;

    void initialiserEvenements();

public:
    Simulation();
    Simulation(Ville* v);

    void demarrerCycle();
    void terminerCycle();
    Evenement declencherEvenement();
    Evenement getDernierEvenement();

    int getCycleActuel() { return cycleActuel; }
    Ville* getVille() { return ville; }
    void setCycleActuel(int c) { cycleActuel = c; }
    void setVille(Ville* v) { ville = v; }
};

#endif

#ifndef USINE_H
#define USINE_H

#include "batiment.h"

class Usine : public Batiment
{
private:
    double productionRessources;
    double pollution;

public:
    Usine();
    Usine(int id, string nom);

    double produireRessources();
    double calculerPollution();
    void afficherDetails();

    double getProductionRessources() { return productionRessources; }
    double getPollution() { return pollution; }
};

#endif

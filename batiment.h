#ifndef BATIMENT_H
#define BATIMENT_H

#include <string>
#include <iostream>
using namespace std;

class Batiment
{
protected:
    int id;
    string nom;
    string type;
    double consommationEau;
    double consommationElectricite;
    int effetSatisfaction;
    double coutConstruction;

public:
    Batiment();
    Batiment(int id, string nom, string type, double eau, double elec, int satisfaction, double cout);
    virtual ~Batiment() {}

    virtual void afficherDetails();
    virtual void calculerImpactRessources(double& eau, double& electricite);

    int getId() { return id; }
    string getNom() { return nom; }
    string getType() { return type; }
    double getConsommationEau() { return consommationEau; }
    double getConsommationElectricite() { return consommationElectricite; }
    int getEffetSatisfaction() { return effetSatisfaction; }
    double getCoutConstruction() { return coutConstruction; }

    void setNom(string n) { nom = n; }
};

#endif

#ifndef PARC_H
#define PARC_H

#include "batiment.h"

class Parc : public Batiment
{
private:
    double surface;
    int effetBienEtre;

public:
    Parc();
    Parc(int id, string nom, double surf);

    int ameliorerBienEtre();
    void afficherDetails();

    double getSurface() { return surface; }
    int getEffetBienEtre() { return effetBienEtre; }
    void setSurface(double s) { surface = s; }
};

#endif

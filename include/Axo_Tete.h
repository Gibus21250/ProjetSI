#ifndef AXO_TETE_H
#define AXO_TETE_H

#include "Drawable.h"

class Axo_Tete : public Drawable
{
public:
    Axo_Tete(const float size, const float r, const float g, const float b);
    Axo_Tete(const float size);
    Axo_Tete();

    void draw();

    void tirerLangue();

private:
    float Rtete;
    float Rmuseau;
    float Ryeux;
    float Rpupille;

    float size;

    int frames;
    bool direction;

    float hBranchies;
    float lBranchies;

    float Rsourir;

    //pour la langue qui sort
    float Ll;
    float Hl;
    float ll;

    void modBranchies();

    float r, g, b;    //couleur générale
    float ry, gy, by; //couleur yeux

};

#endif // AXO_TETE_H

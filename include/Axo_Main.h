#ifndef AXO_MAIN_H
#define AXO_MAIN_H

#include "Drawable.h"

class Axo_Main : public Drawable
{
public:
    Axo_Main(const float size, const bool cinqDoigts);
    Axo_Main();
    void draw();

private:
    //Rayon de la main
    float Rmain;
    //Rayon des doigts
    float Rdoigt;
    //Couleurs de la main
    float r, g, b;
    //Permettra de dessiner, ou non un 5eme doigt (suivant la nature du membre (main -> 4, pied -> 5)
    bool cinqDoigts;

};

#endif// AXO_MAIN_H

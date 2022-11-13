#ifndef AXO_PATE_H
#define AXO_PATE_H

#include "Axo_Main.h"

class Axo_Pate : public Drawable
{
public:
    Axo_Pate(const float size, const float rot, const float rotM, const bool type_pied, const float r, const float g, const float b);
    Axo_Pate();
    //Permet de changer la rotation entre l'avant bras et le bras
    void setRotationCoude(float rot);
    void draw();

protected:

private:

    //Instance de la main
    Axo_Main main;

    //Longueur du bras, rayon du coude, rayon du bras
    float LBras, Rcoude, RBras;
    //Couleur du bras
    float r, g, b;
    //Angle de plie du coude (0 = bras et avant bras droit)
    float rotation_coude;
    //Rotation de la main
    float rotation_main;

    //Permet de préciser si c'est une pate arrière (utilisé pour l'instance Main)
    bool pata_arriere;
};

#endif // AXO_PATE_H

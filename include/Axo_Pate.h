#ifndef AXO_PATE_H
#define AXO_PATE_H

#include "Axo_Main.h"

class Axo_Pate : public Drawable
{
public:
    Axo_Pate(const float size, const float rot, const float rotM, const bool type_pied);
    Axo_Pate();
    void setRotationCoude(float rot);
    void draw();

protected:

private:

    Axo_Main main;

    float LBras, Rcoude, RBras;
    float r, g, b;
    float rotation_coude;
    float rotation_main;

    bool pata_arriere;
};

#endif // AXO_PATE_H

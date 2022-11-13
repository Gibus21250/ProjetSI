#ifndef AXO_QUEUE_H
#define AXO_QUEUE_H

#include "Drawable.h"

class Axo_Queue : public Drawable
{
public:
    Axo_Queue(const float size, const float r, const float g, const float b);
    Axo_Queue();

    void draw();

private:
    //Couleur de la queue
    float r, g, b;
    //facteur de taille pour le queue
    float size;
    //Rayon queue, hauteur queue, largeur flagele, longueur flagele
    float rQueue, hQueue, rFlagele, hFlagele;
    //Permet de dessiner la queue
    void modeliser();
    //Permet de dessiner les flageles
    void flagelemMod();
};

#endif // AXO_QUEUE_H


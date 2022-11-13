#ifndef AXOLOTL_H
#define AXOLOTL_H

#include "Axo_Tete.h"
#include "Axo_Corp.h"
#include "Axo_Pate.h"
#include "Axo_Queue.h"

#include "Drawable.h"

class Axolotl : public Drawable
{
    public:

        Axolotl(const float size, const float r, const float g, const float b);
        Axolotl(const float size);
        Axolotl();

        void draw();

        void setPosition(const float x, const float y, const float z);
        void tirerLaLangue();

    private:

        /* Couleur */
        float r, g, b;

        //Longueur du corp, hauteur du corps
        float lCorp, hCorp;

        //Facteur de taille
        float size;

        /* Position de l'axolotl*/
        float px, py, pz;

        Axo_Tete tete;
        Axo_Corp corp;
        Axo_Pate md, mg, pg, pd; //main droite, main gauche, pied gauche, pied droit
        Axo_Queue queue;
};

#endif // AXOLOTL_H

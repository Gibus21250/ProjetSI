#ifndef AXOLOTL_H
#define AXOLOTL_H

#include "Axo_Tete.h"
#include "Axo_Corp.h"
#include "Axo_Pate.h"
#include "Axo_Queue.h"


class Axolotl : public Drawable
{
    public:
        Axolotl(const float size);
        Axolotl();
        void draw();
        ~Axolotl();

    private:

        float lCorp, hCorp;
        float size;

        Axo_Tete tete;
        Axo_Corp* corp;
        Axo_Pate md, mg, pg, pd;
        Axo_Queue queue;
};

#endif // AXOLOTL_H

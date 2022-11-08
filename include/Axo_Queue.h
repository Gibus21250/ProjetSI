#ifndef AXO_QUEUE_H
#define AXO_QUEUE_H

#include "Drawable.h"

class Axo_Queue : public Drawable
{
public:
    Axo_Queue(const float size);
    Axo_Queue();

    void draw();

private:
    float r, g, b;
    float size;
    float rQueue, hQueue, rFlagele, hFlagele;
    void modeliser();
    void flagelemMod();
};

#endif // AXO_QUEUE_H


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
    float Rmain;
    float Rdoigt;

    float r, g, b;

    bool cinqDoigts;

};

#endif// AXO_MAIN_H

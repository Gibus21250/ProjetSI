
#include "GL/freeglut.h"

#include "../include/Axo_Pate.h"
#include "../include/Axo_Main.h"

Axo_Pate::Axo_Pate(const float size, const float rot, const float rotM, const bool pate)
{
    this->LBras = size*0.3;
    this->RBras = size*0.08;
    this->Rcoude = size*0.095;

    setRotationCoude(rot);

    this->pata_arriere = pate;

    this->r = 243 / 255.;
    this->g = 196 / 255.;
    this->b = 207 / 255.;

    this->rotation_main = rotM;
    this->main = Axo_Main(size, pate);

}

Axo_Pate::Axo_Pate()
{
    //Axo_Pate(1.0f, 0.0f, 0.0f, false);
}

void Axo_Pate::setRotationCoude(float rot)
{
    if (rot <= 60 && rot >= 0) {
        this->rotation_coude = rot;
    }
    else
    {
        this->rotation_coude = 0;
    }
}

void Axo_Pate::draw()
{
    /*  Bras  */
    glPushMatrix();
        glColor3f(r, g, b);
        glRotatef(90, 0, 1, 0);
        glutSolidCylinder(RBras, LBras, 20, 20);
    glPopMatrix();

    glPushMatrix();

        glTranslatef(LBras + 1 / 2. * Rcoude, 0, 0);
        glRotatef(this->rotation_coude, 0, 1, 0);
        glTranslatef(-(LBras + 1 / 2. * Rcoude), 0, 0);
        /*  Coude  */
        glPushMatrix();
            glColor3f(r, g, b);
            glTranslatef(LBras + 1 / 2. * Rcoude, 0, 0);
            glutSolidSphere(Rcoude, 20, 20);
        glPopMatrix();

        /*  Avant Bras  */
        glPushMatrix();
            glColor3f(r, g, b);
            glTranslatef(LBras + Rcoude, 0, 0);
            glRotatef(90, 0, 1, 0);
            glutSolidCylinder(RBras, LBras, 20, 20);
        glPopMatrix();

        /*  Main  */
        glPushMatrix();
            glTranslatef(2 * LBras + 2 * Rcoude, 0, 0);
            glRotatef(rotation_main, 1, 0, 0);
            this->main.draw();
        glPopMatrix();
    glPopMatrix();
}

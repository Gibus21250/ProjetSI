#include <GL/glut.h>

#include "../include/Axo_Main.h"

Axo_Main::Axo_Main(const float size, const bool cinqDoigts, const float r_, const float g_, const float b_)//constructeur
{
    this->Rdoigt = size*0.05;
    this->Rmain = size*0.2;
    this->r = r_;
    this->g = g_;
    this->b = b_;
    this->cinqDoigts = cinqDoigts;
}

Axo_Main::Axo_Main() : Axo_Main(1.0f, false, 243 / 255., 196 / 255., 207 / 255.) {}

void Axo_Main::draw()
{
    /*  La main  */
    glPushMatrix();
        glScalef(1, 0.5, 1);
        glColor3f(r, g, b);
        glutSolidSphere(Rmain, 20, 20);
    glPopMatrix();

    //TODO peut être réaliser la suite dans une unique boucle for

    for(int i = 0; i < 4; i++)
    {
        glPushMatrix();
            glColor3f(r, g, b);
            glRotatef(60 - (40*i), 0, 1, 0);
            glTranslatef(Rmain, 0, 0);
            glScalef(2, 0.5, 1);
            glutSolidSphere(Rdoigt, 20, 20);
        glPopMatrix();
    }

    /*  Cinquième doigts, si la main est une main de pate arrière  */
    if (this->cinqDoigts)
    {
        glPushMatrix();
        glColor3f(r, g, b);
        glRotatef(-90, 0, 1, 0);
        glTranslatef(Rmain, 0, 0);
        glScalef(2, 0.5, 1);
        glutSolidSphere(Rdoigt, 20, 20);
        glPopMatrix();
    }

    glColor3f(1.0f, 1.0f, 1.0f);

}

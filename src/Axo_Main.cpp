#include "Axo_Main.h"

#include <GL/glut.h>

Axo_Main::Axo_Main(const float size, const bool cinqDoigts)//constructeur
{
    this->Rdoigt = size*0.05;
    this->Rmain = size*0.2;
    this->r = 243 / 255.;
    this->g = 196 / 255.;
    this->b = 207 / 255.;
    this->cinqDoigts = cinqDoigts;
}

Axo_Main::Axo_Main()
{
    Axo_Main(1.0f, false);
}

void Axo_Main::draw()
{
    /*  La main  */
    glPushMatrix();
        glScalef(1, 0.5, 1);
        glColor3f(r, g, b);
        glutSolidSphere(Rmain, 20, 20);
    glPopMatrix();

    //TODO peut être réaliser la suite dans une unique boucle for
    /*  Premier doigt  */
    glPushMatrix();
        glColor3f(r, g, b);
        glRotatef(60, 0, 1, 0);
        glTranslatef(Rmain, 0, 0);
        glScalef(2, 0.5, 1);
        glutSolidSphere(Rdoigt, 20, 20);
    glPopMatrix();

    /*  Deuxième doigt  */
    glPushMatrix();
        glColor3f(r, g, b);
        glRotatef(20, 0, 1, 0);
        glTranslatef(Rmain, 0, 0);
        glScalef(2, 0.5, 1);
        glutSolidSphere(Rdoigt, 20, 20);
    glPopMatrix();

    /*  Troisème doigt  */
    glPushMatrix();
        glColor3f(r, g, b);
        glRotatef(-20, 0, 1, 0);
        glTranslatef(Rmain, 0, 0);
        glScalef(2, 0.5, 1);
        glutSolidSphere(Rdoigt, 20, 20);
    glPopMatrix();

    /*  Quatrième doigt  */
    glPushMatrix();
        glColor3f(r, g, b);
        glRotatef(-60, 0, 1, 0);
        glTranslatef(Rmain, 0, 0);
        glScalef(2, 0.5, 1);
        glutSolidSphere(Rdoigt, 20, 20);
    glPopMatrix();

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

}

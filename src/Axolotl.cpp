#include "Axolotl.h"

#include <GL/freeglut.h>

Axolotl::Axolotl(const float size)
{
    this->size = size;

    this->lCorp = size*1.8f;
    this->hCorp = size*0.45;

    this->tete = Axo_Tete(size);
    this->corp = new Axo_Corp(size);
    this->md = Axo_Pate(size, 0.0f, -20.0f, false);
    this->mg = Axo_Pate(size, 60.0f, 0.0f, false);
    this->pd = Axo_Pate(size, 20.0f, 0.0f, true);
    this->pg = Axo_Pate(size, 20.0f, 0.0f, true);
    this->queue = Axo_Queue(size);
}

Axolotl::Axolotl()
{
    Axolotl(1.0f);
}

void Axolotl::draw()
{
    /*  Modelisation et placement de la main droite*/
    glPushMatrix();
        glTranslatef(0.8 * lCorp, -hCorp*0.40, hCorp * 0.8);
        glRotatef(20, 0, 0, 1);
        glRotatef(-130, 0, 1, 0);
        md.draw();
    glPopMatrix();

    /*  Modelisation et placement de la main gauche*/
    glPushMatrix();
        glTranslatef(0.8 * lCorp, -hCorp*0.40, -hCorp * 0.8);
        glRotatef(130, 0, 1, 0);
        glRotatef(180, 1, 0, 0);
        glRotatef(20, 0, 0, 1);
        mg.draw();
    glPopMatrix();

    /*  Modelisation et placement du pied droit*/
    glPushMatrix();
        glTranslatef(0.1 * lCorp, -hCorp*0.40, hCorp * 0.8);
        glRotatef(-100, 0, 1, 0);
        glRotatef(180, 1, 0, 0);
        glRotatef(20, 0, 0, 1);
        pd.draw();
    glPopMatrix();

    /*  Modelisation et placement du pied gauche*/
    glPushMatrix();
        glTranslatef(0.1 * hCorp, -hCorp*0.40, -hCorp * 0.8);
        glRotatef(20, 0, 0, 1);
        glRotatef(140, 0, 1, 0);
        pg.draw();
    glPopMatrix();

    /*  Modelisation et placement de la tete*/
    glPushMatrix();
        glTranslatef(lCorp, 0, 0);
        glScalef(0.4, 0.4, 0.4);
        tete.draw();
    glPopMatrix();

    corp->draw();


    queue.draw();
}

Axolotl::~Axolotl()
{
    delete corp;
}




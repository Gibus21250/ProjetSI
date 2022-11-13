#include "Axolotl.h"

#include <GL/freeglut.h>
#include <iostream>

#include <time.h>

//verifier les constructeur cascade
Axolotl::Axolotl() : Axolotl(1.0f){}

Axolotl::Axolotl(const float size) : Axolotl{size, 243 / 255.f, 196 / 255.f, 207 / 255.f} {}

Axolotl::Axolotl(const float size, const float r_, const float g_, const float b_)
{
    this->r = r_;
    this->g = g_;
    this->b = b_;

    this->px = 0.0;
    this->py = 0.0;
    this->pz = 0.0;

    this->size = size;

    this->lCorp = size*1.8f;
    this->hCorp = size*0.45;
    this->setPosition(0, 0, 0);

    this->tete = Axo_Tete(size, r, g, b);
    this->corp = Axo_Corp(size, r, g, b);
    this->md = Axo_Pate(size, 0.0f, -20.0f, false, r, g, b);
    this->mg = Axo_Pate(size, 60.0f, 0.0f, false, r, g, b);
    this->pd = Axo_Pate(size, 20.0f, 0.0f, true, r, g, b);
    this->pg = Axo_Pate(size, 20.0f, 0.0f, true, r, g, b);
    this->queue = Axo_Queue(size, r, g, b);
}

void Axolotl::setPosition(const float x, const float y, const float z)
{
    this->px = x;
    this->py = y+hCorp;
    this->pz = z;
}

void Axolotl::tirerLaLangue()
{
    tete.tirerLangue();
}

void Axolotl::draw()
{
    glPushMatrix();
        glTranslatef(px, py, pz);
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
            glTranslatef(0.1 * lCorp, -hCorp*0.25, hCorp * 0.8);
            glRotatef(-100, 0, 1, 0);
            glRotatef(180, 1, 0, 0);
            glRotatef(20, 0, 0, 1);
            pd.draw();
        glPopMatrix();

        /*  Modelisation et placement du pied gauche*/
        glPushMatrix();
            glTranslatef(0.1 * hCorp, -hCorp*0.25, -hCorp * 0.8);
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

        corp.draw();

        queue.draw();
    glPopMatrix();
}




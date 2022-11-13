#include "GL/glut.h"
#include <math.h>

#include "../include/Axo_Tete.h"

#include <iostream>

#define DURATION 500.0f

Axo_Tete::Axo_Tete(const float size) : Axo_Tete{size, 243 / 255., 196 / 255., 207 / 255.} {}

Axo_Tete::Axo_Tete(){}

Axo_Tete::Axo_Tete(const float size, const float r_, const float g_, const float b_)
{

    this->Rtete = size*1.0;
    this->Rmuseau = size*1.0;
    this->Ryeux = size*0.2;
    this->Rpupille = size*0.13;

    this->size = size;

    this->r = r_;
    this->g = g_;
    this->b = b_;

    this->hBranchies = 1;
    this->lBranchies = 1 / 4.;

    this->Rsourir = size*0.6;

    this->frames = 0;
    this->direction = false;

    //pour la langue qui sort
    this->Ll = size*1;
    this->Hl = size*0.1;
    this->ll = size*0.6;

    this->ry = 0;
    this->gy = 125 / 255.;
    this->by = 1;
}

void Axo_Tete::tirerLangue()
{
    this->frames = 0;
    this->direction = true;
}

void Axo_Tete::draw()
{
    //tete
    glPushMatrix();
        glColor3f(r, g, b);
        glutSolidSphere(Rtete, 40, 40);
    glPopMatrix();

    //museau
    glPushMatrix();
        glColor3f(r, g, b);
        glTranslatef(Rtete / 2., -Rtete / 3., 0);
        glScalef(1, 0.7, 0.9);
        glutSolidSphere(Rmuseau, 40, 40);
    glPopMatrix();

    glPushMatrix();
        glRotatef(-180 / 6., 0, 1.0, 0);
        glRotatef(180 / 16., 0, 0, 1.0);
        glTranslatef(Rtete * 0.9, 0, 0);

        //oeil gauche
        glPushMatrix();
            glColor3f(ry, gy, by);
            glutSolidSphere(Ryeux, 20, 20);
        glPopMatrix();

        //pupille gauche
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glRotatef(180 / 12, 0, 1, 0.0);
            glTranslatef(Ryeux / 2., 0, 0);
            glutSolidSphere(Rpupille, 20, 20);
        glPopMatrix();

    glPopMatrix();

        glPushMatrix();
        glRotatef(180 / 6., 0, 1.0, 0);
        glRotatef(180 / 16., 0, 0, 1.0);
        glTranslatef(Rtete * 0.9, 0, 0);

        //oeil droit
        glPushMatrix();
            glColor3f(ry, gy, by);
            glutSolidSphere(Ryeux, 20, 20);
        glPopMatrix();

        //pupille droite
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glRotatef(-180 / 12., 0, 1.0, 0);
            glTranslatef(Ryeux / 2., 0, 0);
            glutSolidSphere(Rpupille, 20, 20);
        glPopMatrix();

    glPopMatrix();

    //branchies droites
    glPushMatrix();
        glScalef(size, size, size);
        modBranchies();
        //branchies gauches
        glPushMatrix();
            glRotatef(90, 1, 0, 0);
            modBranchies();
        glPopMatrix();
        glPopMatrix();

    //-----sourir-----//
    glPushMatrix();
        glColor3f(r - 0.2, g - 0.2, b);
        glRotatef(-45, 0, 0, 1);
        glScalef(1, 0.1, 1);
        glTranslatef(Rtete * 0.1 + 0.8 * Rmuseau, 5.5 * Rtete, 0);
        glutSolidSphere(Rsourir, 20, 20);
     glPopMatrix();

    //-----Langue-----//
    glPushMatrix();
    float tx = (frames/(DURATION)) * Rmuseau*0.6;
        glTranslatef(Rtete/4 + tx, -0.6 * Rtete, 0);
        //faire sortie la langue entre x=Rtete/2 + Rmuseau*0.7 (sortie) et x=Rtete/2+Rmuseau/8(rentrée)

        glPushMatrix();
            glColor3f(1, 0.3, 0.3);
            glTranslatef(Ll * 0.5, 0, 0);
            glScalef(2.2, 0.2, 1);
            glutSolidSphere(Rsourir / 2, 20, 20);
        glPopMatrix();

    //Si la langue se pousse
    if(direction && frames < DURATION){
        ++frames;
        if(frames == DURATION) direction = false;
    }else if (frames > 0 && !direction){
    --frames;
    }

    glPopMatrix();
}

void Axo_Tete::modBranchies()
{
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    //Grande
    glPushMatrix();
    glTranslatef(0.95 * 1 / 2., 0.95 * sqrt(3) / 2., 0);
    glRotatef(-10, 0, 0, 1);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);

    glColor3f(r, g - 0.2, b);
    glVertex2f(lBranchies / 2, 0);

    glColor3f(r, g - 0.2, b);
    glVertex2f(-lBranchies / 2., 0);

    glColor3f(r - 0.2, g - 0.2, b);
    glVertex2f(0, hBranchies);

    glEnd();
    glPopMatrix();

    //Moins Grande
    glPushMatrix();
    glTranslatef(0.95 * sqrt(2) / 2., 0.95 * sqrt(2) / 2., 0);
    glRotatef(-45, 0, 0, 1);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(r, g - 0.2, b);
    glVertex2f(-lBranchies / 2, 0);

    glColor3f(r, g - 0.2, b);
    glVertex2f(lBranchies / 2, 0);

    glColor3f(r - 0.2, g - 0.2, b);
    glVertex2f(0, hBranchies);

    glEnd();
    glPopMatrix();

    //Moins Grande ++
    glPushMatrix();
        glTranslatef(0.95 * sqrt(3) / 2., 0.95 * 1 / 2., 0);
        glRotatef(-80, 0, 0, 1);
        glNormal3f(1.0f, 0.0f, 0.0f);

        glBegin(GL_TRIANGLES);
            glColor3f(r, g - 0.2, b);
            glVertex2f(-lBranchies / 2, 0);

            glColor3f(r, g - 0.2, b);
            glVertex2f(0, hBranchies);
            glVertex2f(lBranchies / 2, 0);

            glColor3f(r - 0.2, g - 0.2, b);
            glVertex2f(lBranchies / 2, 0);
            //TODO corriger bug lumière bronchies
        glEnd();
        glPopMatrix();
    glPopMatrix();

}

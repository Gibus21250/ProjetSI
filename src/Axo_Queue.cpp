#include <GL/freeglut.h>

#include "../include/Axo_Queue.h"
#include "../include/Drawable.h"

Axo_Queue::Axo_Queue(const float size)
{
    //---Attributs---//
    this->r = 243 / 255.;
    this->g = 196 / 255.;
    this->b = 207 / 255.;

    this->size = size;

    this->rQueue = size*0.45;
    this->hQueue = size*1.5;

    this->rFlagele = size*0.5;
    this->hFlagele = size*1.6;

}

Axo_Queue::Axo_Queue()
{
    //Axo_Queue(1.0f);
}

void Axo_Queue::draw()
{
    modeliser();
    flagelemMod();

    glColor3f(1.0f, 1.0f, 1.0f);
}

void Axo_Queue::modeliser()
{
    glPushMatrix();
        glColor3f(r, g, b);
        glRotatef(-90, 0, 1, 0);
        glScalef(1, 0.8, 1);
        glutSolidCone(rQueue, hQueue, 100, 100);
    glPopMatrix();
}

void Axo_Queue::flagelemMod()
{

    glPushMatrix();
        glBegin(GL_TRIANGLES);

            glColor3f(r, g - 0.2, b);   //bout queue
            glVertex3f(-hQueue*1.2, 0.0, 0.0);

            glColor3f(r, g - 0.2, b);       //haut queue
            glVertex3f(0.0, rQueue*1.1, 0.0);

            glColor3f(r, g - 0.2, b);       //bas queue
            glVertex3f(0.0, -rQueue*1.1, 0.0);
        glEnd();
    glPopMatrix();
}

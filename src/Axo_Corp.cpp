#include <GL/freeglut.h>

#include "../include/Axo_Corp.h"
#include "../include/Axo_Pate.h"
#include "../include/Axo_Tete.h"

Axo_Corp::Axo_Corp(const float size)
{
    //---Attributs---//
    this->r = 243 / 255.f;
    this->g = 196 / 255.f;
    this->b = 207 / 255.f;

    this->size = size;

    this->rCyl = size * 0.45;
    this->hCyl = size * 1.8;

    generateCyl();
}

Axo_Corp::Axo_Corp() : Axo_Corp (1.0f) {}

void Axo_Corp::generateCyl()      //genere un cylindre de nbFaces
{
    for (int i = 0; i < NBFACE; i++)
    {
        //base
        pCyl[i][0] = rCyl * cos(i * 2 * M_PI / NBFACE);  //coordonnées x
        pCyl[i][1] = 0;                           //coordonnées y
        pCyl[i][2] = rCyl * sin(i * 2 * M_PI / NBFACE);  //coordonnées z

        //couvercle
        pCyl[i + NBFACE][0] = rCyl * cos(i * 2 * M_PI / NBFACE);//coordonnées x
        pCyl[i + NBFACE][1] = hCyl;                      //coordonnées y
        pCyl[i + NBFACE][2] = rCyl * sin(i * 2 * M_PI / NBFACE);//coordonnées z

    }

    //point milieu base
    pCyl[NBFACE * 2][0] = 0;//coordonnées x
    pCyl[NBFACE * 2][1] = 0;//coordonnées y
    pCyl[NBFACE * 2][2] = 0;//coordonnées z

    //point milieu couvercle
    pCyl[2 * NBFACE + 1][0] = 0;   //coordonnées x
    pCyl[2 * NBFACE + 1][1] = hCyl;//coordonnées y
    pCyl[2 * NBFACE + 1][2] = 0;   //coordonnées z

    //-----Faces-----//
    for (int i = 0; i < NBFACE; i++)
    {
        //il y en a 4 car il y a 4 coordonnées dans un rectangle(=une face)
        fCyl[i][0] = i;
        fCyl[i][1] = (i + 1) % NBFACE;
        fCyl[i][2] = ((i + 1) % NBFACE) + NBFACE;
        fCyl[i][3] = i + NBFACE;
    }

    for (int i = 0; i < NBFACE; i++)
    {
        //Vecteur AB
        Point ab{
            pCyl[fCyl[i][1]][0] - pCyl[fCyl[i][0]][0],
            pCyl[fCyl[i][1]][1] - pCyl[fCyl[i][0]][1],
            pCyl[fCyl[i][1]][2] - pCyl[fCyl[i][0]][2],
        };
        Point ac{
            pCyl[fCyl[i][2]][0] - pCyl[fCyl[i][0]][0],
            pCyl[fCyl[i][2]][1] - pCyl[fCyl[i][0]][1],
            pCyl[fCyl[i][2]][2] - pCyl[fCyl[i][0]][2],
        };

        Point normal = Point::p_vectoriel(ac, ab);
        nCyl[i] = Point::normaliser(normal);
    }
}

void Axo_Corp::draw()
{
    /*--------------------construction, mise en couleur du cylindre--------------------*/

    //-----Dessin de la base du corp-----//

    //Notre cylindre étant orienté sur l'axe Z, nous pivotons notre espace pour l'orienter sur l'axe x de notre scène
    glPushMatrix();
        glRotated(-90, 0, 0, 1);
        glScalef(0.8, 1, 1);

        glColor3f(r, g, b);
        glNormal3f(0.0f, -1.0f, 0.0f);
        glBegin(GL_POLYGON);

            //-----Dessin de la base du cylindre-----//
            for (int i = 0; i < NBFACE; i++)
            {
                glVertex3f(pCyl[i][0], pCyl[i][1], pCyl[i][2]);
            }
        glEnd();

        //-----Dessin du couvercle du cylindre-----//

        glNormal3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(r, g, b);
            for (int i = 0; i < NBFACE; i++)
            {
                glVertex3f(pCyl[i + NBFACE][0], pCyl[i + NBFACE][1], pCyl[i + NBFACE][2]);
            }
        glEnd();

        glColor3f(r, g, b);
        for (int i = 0; i < NBFACE; i++)
        {
            glNormal3f(nCyl[i].x, nCyl[i].y, nCyl[i].z);
            glBegin(GL_POLYGON);
                //glTexCoord2f(0.0,0.5);
                glVertex3f(pCyl[fCyl[i][0]][0], pCyl[fCyl[i][0]][1], pCyl[fCyl[i][0]][2]);
                //glTexCoord2f(0.5,0.5);
                glVertex3f(pCyl[fCyl[i][1]][0], pCyl[fCyl[i][1]][1], pCyl[fCyl[i][1]][2]);
                //glTexCoord2f(0.5,0.0);
                glVertex3f(pCyl[fCyl[i][2]][0], pCyl[fCyl[i][2]][1], pCyl[fCyl[i][2]][2]);
                //glTexCoord2f(0.0,0.0);
                glVertex3f(pCyl[fCyl[i][3]][0], pCyl[fCyl[i][3]][1], pCyl[fCyl[i][3]][2]);
            glEnd();
        }

    glPopMatrix();

    flageleMod();

    //queue.draw();

}

void Axo_Corp::flageleMod()
{
    //flagele rectangle un peu moins long que le corp = 0.8
    glPushMatrix();

        glNormal3b(0.0f, 0.0f, 0.2f);
        glBegin(GL_POLYGON);
            glColor3f(r, g - 0.2, b);
            glVertex3f(0, rCyl*1.1, 0);     //coin en haut à gauche

            glColor3f(r, g - 0.2, b);
            glVertex3f(0, 0, 0);  //coin en bas à gauche

            glColor3f(r, g, b);
            glVertex3f(0.72 * hCyl, 0, 0);     //coin en bas à droite

            glColor3f(r, g, b);
            glVertex3f(0.72 * hCyl, rCyl * 1.1, 0);     //coin en haut à droite

        glEnd();

    glPopMatrix();

    //flagele triangle cou
    glPushMatrix();

        glBegin(GL_POLYGON);
            glColor3f(r, g, b);
            glVertex3f(0.72*hCyl, rCyl*1.1, 0);     //coin en haut à gauche

            glColor3f(r, g, b);
            glVertex3f(0.72*hCyl, 0, 0);    //coin en bas à gauche

            glColor3f(r, g, b);
            glVertex3f(hCyl, 0, 0);     //coin en bas à droite

            glColor3f(r, g, b);
            glVertex3f(hCyl, rCyl*0.6, 0);      //coin en haut à droite

        glEnd();

    glPopMatrix();

        //flagele triangle bassin
    glPushMatrix();

        glBegin(GL_TRIANGLES);
            glColor3f(r, g - 0.2, b);
            glVertex3f(0, -rCyl*1.1, 0);

            glColor3f(r, g - 0.2, b);
            glVertex3f(0, 0, 0);

            glColor3f(r, g, b);
            glVertex3f((1-0.72)*hCyl, -0.72*rCyl, 0);

        glEnd();

    glPopMatrix();

}

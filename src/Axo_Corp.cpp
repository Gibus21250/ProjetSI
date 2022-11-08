#include "Axo_Corp.h"

#include <GL/freeglut.h>

#include "Axo_Pate.h"
#include "Axo_Tete.h"


Axo_Corp::Axo_Corp(const float size)
{
    //---Attributs---//
    this->r = 243 / 255.f;
    this->g = 196 / 255.f;
    this->b = 207 / 255.f;

    this->size = size;

    this->rCyl = size * 0.45;
    this->hCyl = size * 1.8;
    this->nbFaces = 100;
    this->pCyl = new float* [2 * nbFaces + 2];

    for (int i = 0; i < 2 * nbFaces + 2; i++)
    {
        pCyl[i] = new float[3];
    }

    this->fCyl = new unsigned* [nbFaces];
    this->nCyl = new Point[nbFaces];

    for (int i = 0; i < nbFaces; i++)
    {
        fCyl[i] = new unsigned[4];
    }

    this->tete = Axo_Tete(size);
    this->md = Axo_Pate(size, 0.0f, false);
    this->mg = Axo_Pate(size, 60.0f, false);
    this->pd = Axo_Pate(size, 20.0f, true);
    this->pg = Axo_Pate(size, 20.0f, true);
    this->queue = Axo_Queue(size);

    this->material = m_material_infos{
        {r, g, b, 1.0f},   //ambiant
        {0.8f, 0.8f, 0.8f, 1.0f},   //diffuse
        {0.0f, 0.0f, 0.0f, 0.0f},   //specular
        0.0f,   //shininess
        {0.0f, 0.0f, 0.0f, 0.0f}    //emission
    };

    generateCyl();
}

void Axo_Corp::generateCyl()      //genere un cylindre de nbFaces
{
    for (int i = 0; i < nbFaces; i++)
    {   
        //base
        pCyl[i][0] = rCyl * cos(i * 2 * M_PI / nbFaces);  //coordonnées x
        pCyl[i][1] = 0;                           //coordonnées y
        pCyl[i][2] = rCyl * sin(i * 2 * M_PI / nbFaces);  //coordonnées z

        //couvercle
        pCyl[i + nbFaces][0] = rCyl * cos(i * 2 * M_PI / nbFaces);//coordonnées x
        pCyl[i + nbFaces][1] = hCyl;                      //coordonnées y
        pCyl[i + nbFaces][2] = rCyl * sin(i * 2 * M_PI / nbFaces);//coordonnées z

    }

    //point milieu base
    pCyl[nbFaces * 2][0] = 0;//coordonnées x
    pCyl[nbFaces * 2][1] = 0;//coordonnées y
    pCyl[nbFaces * 2][2] = 0;//coordonnées z

    //point milieu couvercle
    pCyl[2 * nbFaces + 1][0] = 0;   //coordonnées x
    pCyl[2 * nbFaces + 1][1] = hCyl;//coordonnées y
    pCyl[2 * nbFaces + 1][2] = 0;   //coordonnées z

    //-----Faces-----//
    for (int i = 0; i < nbFaces; i++)
    {
        //il y en a 4 car il y a 4 coordonnées dans un rectangle(=une face)
        fCyl[i][0] = i;
        fCyl[i][1] = (i + 1) % nbFaces;
        fCyl[i][2] = ((i + 1) % nbFaces) + nbFaces;
        fCyl[i][3] = i + nbFaces;
    }

    for (int i = 0; i < nbFaces; i++)
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

    /*  Modelisation et placement de la main droite*/
    glPushMatrix();
        glTranslatef(0.9 * hCyl, 0, rCyl * 0.9);
        glRotatef(-130, 0, 1, 0);
        md.draw();
    glPopMatrix();

    /*  Modelisation et placement de la main gauche*/
    glPushMatrix();
        glTranslatef(0.9 * hCyl, 0, -rCyl * 0.9);
        glRotatef(130, 0, 1, 0);
        glRotatef(180, 1, 0, 0);
        mg.draw();
    glPopMatrix();

    /*  Modelisation et placement du pied droit*/
    glPushMatrix();
        glTranslatef(0.1 * hCyl, 0, rCyl * 0.9);
        glRotatef(-100, 0, 1, 0);
        glRotatef(180, 1, 0, 0);
        pd.draw();
    glPopMatrix();

    /*  Modelisation et placement du pied gauche*/
    glPushMatrix();
        glTranslatef(0.1 * hCyl, 0, -rCyl * 0.9);
        glRotatef(140, 0, 1, 0);
        pg.draw();
    glPopMatrix();

    /*  Modelisation et placement de la tete*/
    glPushMatrix();
        glTranslatef(hCyl, 0, 0);
        glScalef(0.4, 0.4, 0.4);
        tete.draw();
    glPopMatrix();

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
            for (int i = 0; i < nbFaces; i++)
            {
                glVertex3f(pCyl[i][0], pCyl[i][1], pCyl[i][2]);
            }
        glEnd();

        //-----Dessin du couvercle du cylindre-----//

        glNormal3f(0.0f, 1.0f, 0.0f);
        glBegin(GL_POLYGON);
            glColor3f(r, g, b);
            for (int i = 0; i < nbFaces; i++)
            {
                glVertex3f(pCyl[i + nbFaces][0], pCyl[i + nbFaces][1], pCyl[i + nbFaces][2]);
            }
        glEnd();

        glColor3f(r, g, b);
        for (int i = 0; i < nbFaces; i++)
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

    glPushMatrix();
        flageleMod();
    glPopMatrix();
    queue.draw();

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
            glVertex3f(0, -rCyl*1.1, 0);  //coin en bas à gauche

            glColor3f(r, g, b);
            glVertex3f(0.72 * hCyl, -rCyl * 1.1, 0);     //coin en bas à droite

            glColor3f(r, g, b);
            glVertex3f(0.72 * hCyl, rCyl * 1.1, 0);     //coin en haut à droite

        glEnd();

    glPopMatrix();

    //flagele rect-triangle
    glPushMatrix();

        glBegin(GL_POLYGON);
            glColor3f(r, g, b);
            glVertex3f(0.72*hCyl, rCyl*1.1, 0);     //coin en haut à gauche

            glColor3f(r, g, b);
            glVertex3f(0.72*hCyl, -rCyl*1.1, 0);    //coin en bas à gauche

            glColor3f(r, g, b);
            glVertex3f(hCyl, -rCyl*0.6, 0);     //coin en bas à droite

            glColor3f(r, g, b);
            glVertex3f(hCyl, rCyl*0.6, 0);      //coin en haut à droite

        glEnd();

    glPopMatrix();

}

Axo_Corp::~Axo_Corp()
{

    for (int i = 0; i < 2 * nbFaces + 2; i++)
    {
        delete pCyl[i];
    }
    delete pCyl;

    for (int i = 0; i < nbFaces; i++)
    {
        delete fCyl[i];
    }
    delete fCyl;
    delete nCyl;
}
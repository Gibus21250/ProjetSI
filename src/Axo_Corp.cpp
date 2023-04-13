#include <GL/freeglut.h>
#include <cstdlib>
#include <stdio.h>
#include <jpeglib.h>

#define M_PI 3.141592653589793

#include <math.h>

#include "../include/Axo_Corp.h"
#include "../include/Axo_Pate.h"
#include "../include/Axo_Tete.h"

Axo_Corp::Axo_Corp(const float size, const float r_, const float g_, const float b_)
{
    //---Attributs---//
    this->r = r_;
    this->g = g_;
    this->b = b_;

    this->size = size;

    this->rCyl = size * 0.45;
    this->hCyl = size * 1.8;

    generateCyl();
    loadJpegImage((char*)"./Axo_TextureStriesInverses.jpg");
}

Axo_Corp::Axo_Corp() : Axo_Corp (1.0f, 243 / 255.f, 196 / 255.f, 207 / 255.f) {}

void Axo_Corp::generateCyl()      //genere un cylindre de nbFaces
{
    for (int i = 0; i < NBFACE; i++)
    {
        //base
        pCyl[i][0] = rCyl * cos(i * 2 * M_PI / NBFACE);  //coordonn�es x
        pCyl[i][1] = 0;                           //coordonn�es y
        pCyl[i][2] = rCyl * sin(i * 2 * M_PI / NBFACE);  //coordonn�es z

        //couvercle
        pCyl[i + NBFACE][0] = rCyl * cos(i * 2 * M_PI / NBFACE);//coordonn�es x
        pCyl[i + NBFACE][1] = hCyl;                      //coordonn�es y
        pCyl[i + NBFACE][2] = rCyl * sin(i * 2 * M_PI / NBFACE);//coordonn�es z

    }

    //point milieu base
    pCyl[NBFACE * 2][0] = 0;//coordonn�es x
    pCyl[NBFACE * 2][1] = 0;//coordonn�es y
    pCyl[NBFACE * 2][2] = 0;//coordonn�es z

    //point milieu couvercle
    pCyl[2 * NBFACE + 1][0] = 0;   //coordonn�es x
    pCyl[2 * NBFACE + 1][1] = hCyl;//coordonn�es y
    pCyl[2 * NBFACE + 1][2] = 0;   //coordonn�es z

    //-----Faces-----//
    for (int i = 0; i < NBFACE; i++)
    {
        //il y en a 4 car il y a 4 coordonn�es dans un rectangle(=une face)
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

    //Notre cylindre �tant orient� sur l'axe Z, nous pivotons notre espace pour l'orienter sur l'axe x de notre sc�ne
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
        //Dessin des faces du corp
        glEnable(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,512,512,0,GL_RGB,GL_UNSIGNED_BYTE,texture);
        glColor3f(r, g, b);
        for (int i = 0; i < NBFACE; i++)
        {
            glNormal3f(nCyl[i].x, nCyl[i].y, nCyl[i].z);
            glBegin(GL_POLYGON);
                glTexCoord2f(i/(double)NBFACE,1.0);
                glNormal3f(nCyl[i].x, nCyl[i].y, nCyl[i].z);
                glVertex3f(pCyl[fCyl[i][0]][0], pCyl[fCyl[i][0]][1], pCyl[fCyl[i][0]][2]);
                glTexCoord2f((i+1)/(double)NBFACE,1.0);
                glNormal3f(nCyl[i].x, nCyl[i].y, nCyl[i].z);
                glVertex3f(pCyl[fCyl[i][1]][0], pCyl[fCyl[i][1]][1], pCyl[fCyl[i][1]][2]);
                glTexCoord2f((i+1)/(double)NBFACE,0.0);
                glNormal3f(nCyl[i].x, nCyl[i].y, nCyl[i].z);
                glVertex3f(pCyl[fCyl[i][2]][0], pCyl[fCyl[i][2]][1], pCyl[fCyl[i][2]][2]);
                glTexCoord2f(i/(double)NBFACE,0.0);
                glNormal3f(nCyl[i].x, nCyl[i].y, nCyl[i].z);
                glVertex3f(pCyl[fCyl[i][3]][0], pCyl[fCyl[i][3]][1], pCyl[fCyl[i][3]][2]);
            glEnd();
        }
        glDisable(GL_TEXTURE_2D);

    glPopMatrix();

    flageleMod();

    glColor3f(1.0f, 1.0f, 1.0f);
}

void Axo_Corp::loadJpegImage(char *fichier)
{
    unsigned char* image = (unsigned char*) (malloc(sizeof(char) * 3 * 512 * 512));

    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *file;
    unsigned char *ligne;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    #ifdef _WIN32
    if (fopen_s(&file, fichier, "rb") != 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
      exit(1);
    }
    #elif __GNUC__
    if ((file = fopen(fichier,"rb")) == 0)
    {
        fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
        exit(1);
    }
    #endif
    jpeg_stdio_src(&cinfo, file);
    jpeg_read_header(&cinfo, TRUE);

    if ((cinfo.image_width != 512)||(cinfo.image_height != 512)) {
        fprintf(stdout,"Erreur : l'image doit etre de taille 512x512\n");
        exit(1);
    }
    if (cinfo.jpeg_color_space==JCS_GRAYSCALE) {
        fprintf(stdout,"Erreur : l'image doit etre de type RGB\n");
        exit(1);
    }

    jpeg_start_decompress(&cinfo);
    ligne=image;
    while (cinfo.output_scanline<cinfo.output_height)
    {
        ligne=image+3*512*cinfo.output_scanline;
        jpeg_read_scanlines(&cinfo,&ligne,1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    //boucle qui permet de faire la texture
    for(int i = 0; i<512 ; i++)
    {
        for(int j = 0; j<512; j++)
        {
            texture[i][j][0] = image[i*512*3+j*3];
            texture[i][j][1] = image[i*512*3+j*3+1];
            texture[i][j][2] = image[i*512*3+j*3+2];
        }
    }

    free(image);
}

void Axo_Corp::flageleMod()
{
    //flagele rectangle un peu moins long que le corp = 0.8
    glPushMatrix();

        glNormal3b(0.0f, 0.0f, 0.2f);
        glBegin(GL_POLYGON);
            glColor3f(r, g - 0.2, b);
            glVertex3f(0, rCyl*1.1, 0);     //coin en haut � gauche

            glColor3f(r, g - 0.2, b);
            glVertex3f(0, 0, 0);  //coin en bas � gauche

            glColor3f(r, g, b);
            glVertex3f(0.72 * hCyl, 0, 0);     //coin en bas � droite

            glColor3f(r, g, b);
            glVertex3f(0.72 * hCyl, rCyl * 1.1, 0);     //coin en haut � droite

        glEnd();

    glPopMatrix();

    //flagele triangle cou
    glPushMatrix();

        glBegin(GL_POLYGON);
            glColor3f(r, g, b);
            glVertex3f(0.72*hCyl, rCyl*1.1, 0);     //coin en haut � gauche

            glColor3f(r, g, b);
            glVertex3f(0.72*hCyl, 0, 0);    //coin en bas � gauche

            glColor3f(r, g, b);
            glVertex3f(hCyl, 0, 0);     //coin en bas � droite

            glColor3f(r, g, b);
            glVertex3f(hCyl, rCyl*0.6, 0);      //coin en haut � droite

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

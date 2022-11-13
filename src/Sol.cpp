#include "Sol.h"

#include <GL/freeglut.h>
#include <cstdlib>
#include <stdio.h>
#include <jpeglib.h>


Sol::Sol()
{
    loadJpegImage("./texture-eau.jpg");
}

void Sol::draw()
{
    glPushMatrix();
    glScalef(5, 0.1, 5);
    glTranslatef(0, -1.0f, 0.0f);
        glEnable(GL_TEXTURE_2D);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,1024,1024,0,GL_RGB,GL_UNSIGNED_BYTE,texture);

        glColor3f(1, 1, 1);
        glBegin(GL_POLYGON);
            glTexCoord2f(0, 0);
            glVertex3f(pCube[fCube[0][0]][0], pCube[fCube[0][0]][1], pCube[fCube[0][0]][2]);
            glTexCoord2f(0, 1);
            glVertex3f(pCube[fCube[0][1]][0], pCube[fCube[0][1]][1], pCube[fCube[0][1]][2]);
            glTexCoord2f(1, 1);
            glVertex3f(pCube[fCube[0][2]][0], pCube[fCube[0][2]][1], pCube[fCube[0][2]][2]);
            glTexCoord2f(1, 0);
            glVertex3f(pCube[fCube[0][3]][0], pCube[fCube[0][3]][1], pCube[fCube[0][3]][2]);
        glEnd();

        glColor3f(34/255.0f, 66/255.0f, 124/255.0f);
        glDisable(GL_TEXTURE_2D);
        for(int i = 1; i < 6; ++i)
        {
            glBegin(GL_POLYGON);
            glVertex3f(pCube[fCube[i][0]][0], pCube[fCube[i][0]][1], pCube[fCube[i][0]][2]);
            glVertex3f(pCube[fCube[i][1]][0], pCube[fCube[i][1]][1], pCube[fCube[i][1]][2]);
            glVertex3f(pCube[fCube[i][2]][0], pCube[fCube[i][2]][1], pCube[fCube[i][2]][2]);
            glVertex3f(pCube[fCube[i][3]][0], pCube[fCube[i][3]][1], pCube[fCube[i][3]][2]);
            glEnd();
        }
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
}

void Sol::loadJpegImage(char *fichier)
{
    unsigned char image[3*1024*1024];
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;
    FILE *file;
    unsigned char *ligne;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    #ifdef __WIN32
    if (fopen_s(&file,fichier,"rb") != 0)
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

    if ((cinfo.image_width != 1024)||(cinfo.image_height != 1024)) {
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
        ligne=image+3*1024*cinfo.output_scanline;
        jpeg_read_scanlines(&cinfo,&ligne,1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    //boucle qui permet de faire la texture
    for(int i = 0; i<1024 ; i++)
    {
        for(int j = 0; j<1024; j++)
        {
            texture[i][j][0] = image[i*1024*3+j*3];
            texture[i][j][1] = image[i*1024*3+j*3+1];
            texture[i][j][2] = image[i*1024*3+j*3+2];
        }
    }
}

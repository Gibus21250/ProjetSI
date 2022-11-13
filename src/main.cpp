#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif
#include <cstdlib>
#include <iostream>

#include "Axolotl.h"
#include "Sol.h"

int framesPassed = 0;

float anglex = 0, angley = 12;
int x, y, xold, yold;
bool presseAngle = false, presseTranslation;
float cposx = 0, cposy = 0, cposz = 10;

Axolotl Axo{1.0f};
Axolotl AxoBleu(0.5f, 115/255.0f, 194/255.0f, 251/255.0f);
Axolotl AxoBleu2(0.7f, 0/255.0f, 204/255.0f, 203/255.0f);
Axolotl AxoRouge(1.2f, 109/255.0f, 7/255.0f, 26/255.0f);
Sol sol;

float ratio = 1.0f;

char nbLum = 3;

/* Prototype des fonctions */
void affichage();
void clavier(unsigned char touche, int x, int y);
void reshape(int x, int y);
void idle();
void mouse(int bouton, int etat, int x, int y);
void mousemotion(int x, int y);
void arrowGestion(int x, int y, int z);

void axolotl()
{
    Axo.draw();
    Axo.setPosition(-3, 0, 0);
    //AxoBleu.setPosition(-3, 0, -1);
    //AxoBleu2.setPosition(-6, 0, -3);
    //AxoRouge.setPosition(2, 0, -2);

    glPushMatrix();
        glTranslatef(-1.5, 0, -2);
        glRotatef(-45, 0, 1, 0);
        AxoBleu.draw();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.1, 0, -3);
        glRotatef(-115, 0, 1, 0);
        AxoBleu2.draw();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(2.35, 0, 0);
        glRotatef(-180, 0, 1, 0);
        AxoRouge.draw();
    glPopMatrix();
    sol.draw();
}

int main(int argc, char** argv)
{
    /* initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1024, 1024);
    glutCreateWindow("Axolotl");

    /* Initialisation d'OpenGL */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    /* Initialisation du systeme de lumière*/
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);


    // Lumière Point, ecla  irage global simple avec les valeurs par défaut
    glEnable(GL_LIGHT0);

    // Lumière numéro 1 //
    glEnable(GL_LIGHT1);

    GLfloat l1_diff[] = { 0.1f, 0.5f, 0.8f, 1.0f };
    GLfloat l1_spotDir[] = { -1.0f, -1.0f, -1.0f };

    glLightfv(GL_LIGHT1, GL_DIFFUSE, l1_diff);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, l1_spotDir);
    // --------------------- //


    /* enregistrement des fonctions de rappel */
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);
    glutIdleFunc(idle);
    glutSpecialFunc(arrowGestion);
    /* Entree dans la boucle principale glut */
    glutMainLoop();

    return 0;
}

void idle()
{
    affichage();

    ++framesPassed;

    if(framesPassed > 500)
    {
       anglex += 0.1;
    }
}

void affichage()
{
    /* effacement de l'image avec la couleur de fond */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //TODO switch entre perspective et ortho
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glOrtho(-cposz, cposz, -cposz, cposz, 0.1, 50);
    gluPerspective(30, ratio, 0.01, 50);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cposx, cposy, cposz, cposx, cposy, cposz - 10, 0.0, 1.0, 0.0);
    //Rotation espace en fonction de l'angle de vue
    glRotatef(angley, 1.0, 0.0, 0.0);
    glRotatef(anglex, 0.0, 1.0, 0.0);

        //Lumière numero 0 de type Point
    GLfloat light_position[] = { 0.0f, 1.0f, 1.0f, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    //Lumière rouge de type SPOT
    GLfloat l1_pos[] = { 1.0f, 5.0f, -3.0f, 1.0f };
    glLightfv(GL_LIGHT1, GL_POSITION, l1_pos);

    if(nbLum == 0){
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
    }
    else if (nbLum == 1)
    {
        glEnable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
    }
    else if (nbLum == 2)
    {
        glDisable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
    }
    else
    {
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
    }


    axolotl();

    /*
    //Repère
    //axe x en rouge
    glBegin(GL_LINES);
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(2, 0, 0.0);
    glEnd();
    //axe des y en vert
    glBegin(GL_LINES);
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(0, 2, 0.0);
    glEnd();
    //axe des z en bleu
    glBegin(GL_LINES);
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, 0.0);
    glVertex3f(0, 0, 2.0);
    glEnd();
    */


    glFlush();

    //On echange les buffers
    glutSwapBuffers();
}

void clavier(unsigned char touche, int x, int y)
{
    switch (touche)
    {
    case 'p': /* affichage du carre plein */
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glutPostRedisplay();
        break;
    case 'f': /* affichage en mode fil de fer */
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glutPostRedisplay();
        break;
    case 's': /* Affichage en mode sommets seuls */
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
        glutPostRedisplay();
        break;
    case 'd':
        glEnable(GL_DEPTH_TEST);
        glutPostRedisplay();
        break;
    case 'D':
        glDisable(GL_DEPTH_TEST);
        glutPostRedisplay();
        break;
    case 'a':
        glPolygonMode(GL_BACK, GL_FILL);
        glPolygonMode(GL_FRONT, GL_LINE);
        glutPostRedisplay();
        break;
    case 'r':
        cposx = 0;
        cposy = 0;
        cposz = 5;
        break;
    case ' ':
        Axo.tirerLaLangue();
        break;
    case 'l':
        nbLum ++;
        if(nbLum > 3) nbLum = 0;
        break;
    case 'Z':
        if(cposz < 20)
            cposz += 0.1;
        break;
    case 'z':
        if(cposz > 0)
        cposz -= 0.1;
        break;
    case 'q': /*la touche 'q' permet de quitter le programme */
        exit(0);
    }
}

void arrowGestion(int x, int y, int z)
{
    switch(x)
    {
    case GLUT_KEY_UP:
        angley -= 0.5;
        if(angley < -90) angley = 0;
        framesPassed = 0;
        break;
    case GLUT_KEY_DOWN:
        angley += 0.5;
        if(angley > 90) angley = 90;
        framesPassed = 0;
        break;
    case GLUT_KEY_RIGHT:
        anglex += 0.5;
        framesPassed = 0;
        break;
    case GLUT_KEY_LEFT:
        anglex -= 0.5;
        framesPassed = 0;
        break;
    }
    std::cout << x << " " << y << " " << z << std::endl;
}

void reshape(int x, int y)
{
    ratio = (double)x/y;
    glViewport(0, 0, x, y);
}

void mouse(int button, int state, int x, int y)
{
    framesPassed = 0;
    /* si on appuie sur le bouton gauche */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        presseAngle = true; /* le booleen presse passe a 1 (vrai) */
        xold = x; /* on sauvegarde la position de la souris */
        yold = y;
    }

  /* si on relache le bouton gauche */
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        presseAngle = false; /* le booleen presse passe a 0 (faux) */
    }

        /* si on appuie sur le bouton gauche */
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        presseTranslation = true; /* le booleen presse passe a 1 (vrai) */
        xold = x; /* on sauvegarde la position de la souris */
        yold = y;
    }

  /* si on relache le bouton gauche */
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
    {
        presseTranslation = false; /* le booleen presse passe a 0 (faux) */
    }

    if (button == 4 && cposz < 20)
        cposz += 0.1;
    if (button == 3 && cposz > 0.1)
        cposz -= 0.1;
}

void mousemotion(int x, int y)
{
    framesPassed = 0;
    if (presseAngle) /* si le bouton gauche est presse */
    {
        /* on modifie les angles de rotation de l'objet
       en fonction de la position actuelle de la souris et de la derniere
       position sauvegardee */
        anglex = anglex + (x - xold);
        angley = angley + (y - yold);
        if(angley > 90) angley = 90;
        if(angley < -90) angley = -90;
        glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }

    if(presseTranslation)
    {
        cposx += 0.01*(x - xold);
        cposy += 0.01*(y - yold);
    }

    xold = x; /* sauvegarde des valeurs courante de le position de la souris */
    yold = y;
}

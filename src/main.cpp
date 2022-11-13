#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif
#include <cstdlib>
#include <iostream>

#include "Axolotl.h"
#include "Sol.h"

//Variable translation g�n�rales
float rx = 0, ry = 0, rz = 0;

int anglex, angley, x, y, xold, yold;
bool presseAngle = false, presseTranslation;
float cposx = 0, cposy = 0, cposz = 5;

/*
    this->r = 243 / 255.f;
    this->g = 196 / 255.f;
    this->b = 207 / 255.f;
*/

Axolotl Axo{1.0f};
Sol sol;

/* Prototype des fonctions */
void affichage();
void clavier(unsigned char touche, int x, int y);
void reshape(int x, int y);
void idle();
void mouse(int bouton, int etat, int x, int y);
void mousemotion(int x, int y);

void axolotl()
{
    Axo.draw();
    sol.draw();
}

int main(int argc, char** argv)
{
    /* initialisation de glut et creation de la fenetre */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Axolotl");


    /* Initialisation d'OpenGL */
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(2.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    /* Initialisation du systeme de lumi�re*/
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat lmodel_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);


    glEnable(GL_LIGHT0);

    /* enregistrement des fonctions de rappel */
    glutDisplayFunc(affichage);
    glutKeyboardFunc(clavier);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(mousemotion);
    glutIdleFunc(idle);

    /* Entree dans la boucle principale glut */
    glutMainLoop();

    return 0;
}

void idle()
{
    affichage();
}

void affichage()
{
    /* effacement de l'image avec la couleur de fond */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //TODO switch entre perspective et ortho
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-cposz, cposz, -cposz, cposz, 0.1, 50);
    //gluPerspective(90, 1, 0.01, 25);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cposx, cposy, cposz, cposx, cposy, cposz - 5, 0.0, 1.0, 0.0);
    glRotatef(angley, 1.0, 0.0, 0.0);
    glRotatef(anglex, 0.0, 1.0, 0.0);

    GLfloat light_position[] = { 0.0f, 1.0f, 1.0f, 1.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    axolotl();

    //Rep�re
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
        glPolygonMode(GL_FRONT, GL_FILL);
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
    case 'q': /*la touche 'q' permet de quitter le programme */
        exit(0);
    }
}

void reshape(int x, int y)
{
    if (x < y)
        glViewport(0, (y - x) / 2, x, x);
    else
        glViewport((x - y) / 2, 0, y, y);
}

void mouse(int button, int state, int x, int y)
{
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

    std::cout << cposx << " " << cposy << " " << cposz << " " << std::endl;

    if (button == 4 && cposz < 20)
        cposz += 0.1;
    if (button == 3 && cposz > 0.1)
        cposz -= 0.1;
}

void mousemotion(int x, int y)
{
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

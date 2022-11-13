#ifndef AXO_CORP_H
#define AXO_CORP_H

#include "Axo_Tete.h"
#include "Axo_Pate.h"
#include "Axo_Queue.h"

#include <cmath>

#define NBFACE 100

class Axo_Corp : public Drawable
{
public:
    Axo_Corp(const float size);
    Axo_Corp();
    void draw();

private:

    //Simple sutructure de point pour gerer les normals (et les calculs qui y sont attachés)
    struct Point
    {
        float x, y, z;

        static Point p_vectoriel(const Point& a, const Point& b)
        {
            Point res{
                a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x
            };
            return res;
        }
        static Point normaliser(const Point& p)
        {
            auto norme = sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
            Point res{
                p.x / norme,
                p.y / norme,
                p.z / norme
            };
            return res;
        }
    };

    //Permet de modeliser les flageles sur le dos
    void flageleMod();

    //Génère les coords des points, les faces et les normals
    void generateCyl();

    //Permet de stoquer la texture du dos
    unsigned char texture[512][512][3];
    //Fonction permettant le lire une image et de la stocker dans texture
    void loadJpegImage(char *fichier);

    //Couleurs du corp
    float r, g, b;
    //Proportion du corp
    float size;

    //Rayon et longueur du corps
    float rCyl, hCyl;

    //Tableau stockant les données du cylindre (points, faces et normals)
    float pCyl[2 * NBFACE + 2][3];
    unsigned fCyl[NBFACE][4];
    Point nCyl[NBFACE];

};

#endif// AXO_CORP_H

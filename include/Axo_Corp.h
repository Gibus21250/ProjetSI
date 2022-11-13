#ifndef AXO_CORP_H
#define AXO_CORP_H

#include "Axo_Tete.h"
#include "Axo_Pate.h"
#include "Axo_Queue.h"

#ifdef _WIN32
#define _USE_MATH_DEFINES
#include <cmath>
#elif __linux__
#include <math.h>
#endif

#define NBFACE 100

class Axo_Corp : public Drawable
{
public:
    Axo_Corp(const float size);
    Axo_Corp();
    void draw();

private:

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

    void flageleMod();

    void generateCyl();

    unsigned char texture[512][512][3];
    void loadJpegImage(char *fichier);

    float r, g, b;
    float size;

    float rCyl, hCyl;

    float pCyl[2 * NBFACE + 2][3];
    unsigned fCyl[NBFACE][4];
    Point nCyl[NBFACE];

};

#endif// AXO_CORP_H

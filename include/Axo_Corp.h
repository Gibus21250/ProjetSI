#ifndef AXO_CORP_H
#define AXO_CORP_H

#include "Axo_Tete.h"
#include "Axo_Pate.h"
#include "Axo_Queue.h";

#ifdef _WIN32
#define _USE_MATH_DEFINES
#include <cmath>
#elif __linux__
#include <math.h>
#endif

class Axo_Corp : public Drawable
{
public:
    Axo_Corp(const float size);
    void draw();
    void generateCyl();

    ~Axo_Corp();

private:

    struct m_material_infos material;

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
    
    float r, g, b;
    float size;
    int nbFaces; //TODO peut être supprimer cet attribut
    float rCyl, hCyl;
    float** pCyl;
    unsigned** fCyl;
    Point* nCyl;

    Axo_Tete tete;
    Axo_Pate md, mg, pd, pg;
    Axo_Queue queue;

};

#endif// AXO_CORP_H

#ifndef SOL_H
#define SOL_H

#include "Drawable.h"

class Sol : public Drawable
{
    public:
        Sol();
        void draw();

    private:
        unsigned char texture[1024][1024][3];
        void loadJpegImage(char *fichier);

        float pCube[8][3] = {
            {1, 1, 1},
            {1, 1, -1},
            {-1, 1, -1},
            {-1, 1, 1},

            {1, -1, 1},
            {1, -1, -1},
            {-1, -1, -1},
            {-1, -1, 1}
        };

        unsigned fCube[6][4] = {
            {0, 1, 2, 3},   //Face du haut
            {4, 5, 6, 7},   //Face du bas
            {4, 5, 1, 0},   //Coté en +X
            {5, 6, 2, 1},   //Coté en -Z
            {6, 7, 3, 2},   //Coté en -X
            {7, 4, 0, 3}    //Cote en +Z
        };

        float nCube[6][3] = {

            {0.0f, 1.0f, 0.0f},
            {0.0f, -1.0f, 0.0f},
            {1.0f, 0.0f, 0.0f},

            {0.0f, 0.0f, -1.0f},
            {-1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f}
        };
};

#endif // SOL_H

#ifndef AXO_TETE_H
#define AXO_TETE_H

#include "Drawable.h"

class Axo_Tete : public Drawable
{
public:
    Axo_Tete(const float size, const float r, const float g, const float b);
    Axo_Tete(const float size);
    Axo_Tete();

    void draw();

    void tirerLangue();

private:
    //Rayon tete
    float Rtete;
    //Rayon museau
    float Rmuseau;
    //Rayon yeux
    float Ryeux;
    //Rayon pupille
    float Rpupille;

    //Facteur de taille
    float size;

    //Variable permettant de gerer l'animation de la langue
    //frames est utilisé pour faire une animation lisse durant 500 frames allé, 500 frames retour
    int frames;
    bool direction; //Permet de phaser l'animation en 2 étapes: pousserLangue, et tirerLangue

    float hBranchies;   //Hauteur branchies
    float lBranchies;   //longueur branchies

    //Rayon sourir
    float Rsourir;

    //pour la langue qui sort, Longueur, hauteur, largeur
    float Ll;
    float Hl;
    float ll;

    //Permet de modeliser les branchies (sur le cou)
    void modBranchies();

    float r, g, b;    //couleur générale
    float ry, gy, by; //couleur yeux

};

#endif // AXO_TETE_H

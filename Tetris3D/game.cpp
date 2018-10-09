//
//  game.cpp
//  programmation avancée
//
//  Created by ugo cottin on 09/10/2018.
//

#include "game.hpp"
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

// Point2D Methods
Point2D::Point2D() {
    x = 0;
    y = 0;
}

Point2D::Point2D(double abscisse, double ordonnee) {
    x = abscisse;
    y = ordonnee;
}

double Point2D::getX() {
    return x;
}

double Point2D::getY() {
    return y;
}
// End Point2D Methods

// Segment Methods
Segment::Segment() {
    p1 = Point2D();
    p2 = Point2D();
}

Segment::Segment(Point2D a, Point2D b) {
    p1 = a;
    p2 = b;
}

Point2D Segment::getP1() {
    return p1;
}

Point2D Segment::getP2() {
    return p2;
}

void Segment::RenderDrawSegment(SDL_Renderer* renderer) {
    int dlig = getP2().getY() - getP1().getY();
    int dcol = getP2().getX() - getP1().getX();
    int abscol = abs(dcol);
    int abslig = abs(dlig);
    int col = getP1().getX();
    int lig = getP1().getY();
    int sensLig = 1;
    int sensCol = 1;
    int cumul = 0;
    
    if (dcol < 0) {
        sensCol = -1;
    }
    if (dlig < 0) {
        sensLig = -1;
    }
    
    if (abscol > abslig) {
        cumul = abscol;
        while (col != (getP2().getX() + sensCol)) {
            SDL_RenderDrawPoint(renderer, col, lig);
            cumul += 2 * abslig;
            if (cumul >= 2 * abscol) {
                lig += sensLig;
                cumul -= 2 * abscol;
            }
            col += sensCol;
        }
    } else {
        cumul = abslig;
        while (lig != (getP2().getY() + sensLig)) {
            SDL_RenderDrawPoint(renderer, col, lig);
            cumul += 2 * abscol;
            if (cumul >= 2 * abslig) {
                col += sensCol;
                cumul -= 2 * abslig;
            }
            lig += sensLig;
        }
    }
    
}

// End Segment Methods

// Square Methods
Square::Square() {
    enBasAGauche = Point2D();
    enBasADroite = Point2D();
    enHautAGauche = Point2D();
    enHautADroite = Point2D();
}

Square::Square(Point2D bg, Point2D bd, Point2D hd, Point2D hg) {
    enBasAGauche = bg;
    enBasADroite = bd;
    enHautAGauche = hg;
    enHautADroite = hd;
}

Point2D Square::coinEnBasAGauche() {
    return enBasAGauche;
}

Point2D Square::coinEnBasADroite() {
    return enBasADroite;
}

Point2D Square::coinEnHautAGauche() {
    return enHautAGauche;
}

Point2D Square::coinEnHautADroite() {
    return enHautADroite;
}

Point2D Square::getCentre() {
    return Point2D((enBasAGauche.getX() + enHautADroite.getX())/2, (enBasAGauche.getY() + enHautADroite.getY())/2);
}

void Square::RenderDrawSquare(SDL_Renderer* renderer) {
    
    Segment s1 = Segment(coinEnBasAGauche(), coinEnBasADroite());
    Segment s2 = Segment(coinEnBasADroite(), coinEnHautADroite());
    Segment s3 = Segment(coinEnHautADroite(), coinEnHautAGauche());
    Segment s4 = Segment(coinEnHautAGauche(), coinEnBasAGauche());

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    s1.RenderDrawSegment(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    s2.RenderDrawSegment(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    s3.RenderDrawSegment(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    s4.RenderDrawSegment(renderer);
    
}

Point2D* Square::getNodes() {

    Point2D tab[] = {coinEnBasAGauche(), coinEnBasADroite(), coinEnHautADroite(), coinEnHautAGauche()};
    return tab;
}

void Square::rotate(double alpha) {
    
    Point2D centre = Point2D(
                         (coinEnBasAGauche().getX() + coinEnHautADroite().getX()) / 2,
                         (coinEnBasAGauche().getY() + coinEnHautADroite().getY()) / 2
                         );

    Point2D tab[] = {Point2D(),Point2D(),Point2D(),Point2D()};
    
    for (int i = 0; i < 4; i++) {
        Point2D p = getNodes()[i];
        double a = p.getX() - centre.getX();
        double b = p.getY() - centre.getY();
        double d = hypot(b,a);
        double theta  = atan2(b, a) + alpha;
        
        tab[i] = Point2D(centre.getX() + d * cos(theta), centre.getY() + d * sin(theta));
    }
    enBasAGauche = tab[0];
    enBasADroite = tab[1];
    enHautADroite = tab[2];
    enHautAGauche = tab[3];
}

// End Square Methods

// Point3D Methods

Point3D::Point3D() {
    x = 0;
    y = 0;
    z = 0;
}

Point3D::Point3D(double a, double b, double c) {
    x = a;
    y = b;
    z = c;
}

double Point3D::getX() {
    return x;
}

double Point3D::getY() {
    return y;
}

double Point3D::getZ() {
    return z;
}

// End Point3D Methods

// Cube Methods

Cube::Cube() {
    enBasAGaucheDevant = Point3D();
    enBasADroiteDevant = Point3D();
    enHautAGaucheDevant = Point3D();
    enHautADroiteDevant = Point3D();
    enBasAGaucheDerriere = Point3D();
    enBasADroiteDerriere = Point3D();
    enHautAGaucheDerriere = Point3D();
    enHautADroiteDerriere = Point3D();
}

Cube::Cube(Point3D origineEnBasAGaucheDevant, double taille) {
    
    enBasAGaucheDevant = origineEnBasAGaucheDevant;
    enBasADroiteDevant = Point3D(
                                 origineEnBasAGaucheDevant.getX() + taille,
                                 origineEnBasAGaucheDevant.getY(),
                                 origineEnBasAGaucheDevant.getZ()
                                 );
    enHautAGaucheDevant = Point3D(
                                  origineEnBasAGaucheDevant.getX(),
                                  origineEnBasAGaucheDevant.getY() + taille,
                                  origineEnBasAGaucheDevant.getZ()
                                  );
    enHautADroiteDevant = Point3D(
                                  origineEnBasAGaucheDevant.getX() + taille,
                                  origineEnBasAGaucheDevant.getY() + taille,
                                  origineEnBasAGaucheDevant.getZ()
                                  );
    enBasAGaucheDerriere = Point3D(
                                   origineEnBasAGaucheDevant.getX(),
                                   origineEnBasAGaucheDevant.getY(),
                                   origineEnBasAGaucheDevant.getZ() + taille
                                   );
    enBasADroiteDerriere = Point3D(
                                   origineEnBasAGaucheDevant.getX() + taille,
                                   origineEnBasAGaucheDevant.getY(),
                                   origineEnBasAGaucheDevant.getZ() + taille
                                   );
    enHautAGaucheDerriere = Point3D(
                                    origineEnBasAGaucheDevant.getX(),
                                    origineEnBasAGaucheDevant.getY() + taille,
                                    origineEnBasAGaucheDevant.getZ() + taille
                                    );
    enHautADroiteDerriere = Point3D(
                                    origineEnBasAGaucheDevant.getX() + taille,
                                    origineEnBasAGaucheDevant.getY() + taille,
                                    origineEnBasAGaucheDevant.getZ() + taille
                                    );
}

void Cube::getNodes(Point3D tab[2][2][2]) {
    /*tab[z][y][x]
     
        1,1,0 ------ 1,1,1
         /|           / |
        / |          /  |
       /  |         /   |
     0,1,0 ------ 0,1,1 |
       |1,0,0 ------|-1,0,1
       |  /         |  /
       | /          | /
       |/           |/
     0,0,0 ------ 0,0,1
    
     */
    tab[0][0][0] = enBasAGaucheDevant;
    tab[0][0][1] = enBasADroiteDevant;
    tab[0][1][0] = enHautAGaucheDevant;
    tab[0][1][1] = enHautADroiteDevant;
    tab[1][0][0] = enBasAGaucheDerriere;
    tab[1][0][1] = enBasADroiteDerriere;
    tab[1][1][0] = enHautAGaucheDerriere;
    tab[1][1][1] = enHautADroiteDerriere;
    
}
// End Cube Methods

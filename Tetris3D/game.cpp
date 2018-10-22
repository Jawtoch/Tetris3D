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
#include <iostream>

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
    SDL_RenderDrawLine(renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
    
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

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    s1.RenderDrawSegment(renderer);
    s2.RenderDrawSegment(renderer);
    s3.RenderDrawSegment(renderer);
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

void Square::remplir(SDL_Renderer* renderer) {
    
    Point2D A = coinEnBasAGauche();
    Point2D B = coinEnBasADroite();
    Point2D C = coinEnHautAGauche();
    Point2D D = coinEnHautADroite();
    
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    
    double deltaX = abs(C.getX() - A.getX());
    if (deltaX == 0) {
        for (int i = 0; i < 2 * abs(A.getY() - B.getY()); i++) {
            SDL_RenderDrawLine(renderer, A.getX(), A.getY() + i, B.getX(), B.getY() + i);
        }
    } else {
        double deltaY = abs(C.getY() - A.getY());
        int i = 0;
        double y = 0;
        while (i != deltaX){
            y += (deltaY / deltaX);
            SDL_RenderDrawLine(renderer, A.getX() - i, A.getY() + y, B.getX() - i, B.getY() + y);
            i++;
        }
    }
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

Point2D Point3D::toPoint2D() {
    double i = 0.9546951008;
    return Point2D(getX() + getY(), (getX() + getY()) * cos(i) + 2 * getZ() * cos(i));
}
// End Point3D Methods

// Cube Methods

Cube::Cube() {
    taille = 0.;
    exist = false;
}

Cube::Cube(double taille) {
    this->taille = taille;
    if (taille == 0) {
        exist = false;
    } else {
        exist = true;
    }
}

void Cube::RenderDrawCube(SDL_Renderer *renderer, int x, int y, int z, int shiftX, int shiftY) {
    double angle = 0.9546951008;
    int a = x * taille;
    int b = y * taille;
    int c = z * taille;
    
    
    Point2D A = Point2D(a - b + shiftX, (a + b) * cos(angle) + 2 * c * cos(angle) + shiftY);
    Point2D B = Point2D(a - b + taille + shiftX, (a + b + taille) * cos(angle) + 2 * (c) * cos(angle) + shiftY);
    Point2D C = Point2D(a - b + shiftX, (a + b + 2 * taille) * cos(angle) + 2 * c * cos(angle) + shiftY);
    Point2D D = Point2D(a - b - taille + shiftX, (a + b + taille) * cos(angle) + 2 * c * cos(angle) + shiftY);
    Point2D E = Point2D(a - b + shiftX, (a + b) * cos(angle) + 2 * (c + taille) * cos(angle) + shiftY);
    Point2D F = Point2D(a - b + taille + shiftX, (a + b + taille) * cos(angle) + 2 * (c + taille) * cos(angle) + shiftY);
    Point2D G = Point2D(a - b + shiftX, (a + b + 2 * taille) * cos(angle) + 2 * (c + taille) * cos(angle) + shiftY);
    Point2D H = Point2D(a - b - taille + shiftX, (a + b + taille) * cos(angle) + 2 * (c + taille) * cos(angle) + shiftY);
    
    Square s1 = Square(A, B, C, D);
    Square s2 = Square(B, C, G, F);
    Square s3 = Square(C, D, H, G);
    
    s1.remplir(renderer);
    s1.RenderDrawSquare(renderer);
    s2.remplir(renderer);
    s2.RenderDrawSquare(renderer);
    s3.remplir(renderer);
    s3.RenderDrawSquare(renderer);
    
}

bool Cube::doesExist() {
    return exist;
}
// End Cube Methods

Cube*** creer_tableau(int taille1, int taille2, int taille3) {
    Cube*** T = new Cube**[taille1];
    if (T == NULL)
        exit(EXIT_FAILURE);
    for(int i = 0; i < taille1; i++) {
        T[i] = new Cube*[taille2];
        for(int j = 0; j < taille2; j++) {
            T[i][j] = new Cube[taille3];
        }
    }
    return T;
}
// End Camera Methods

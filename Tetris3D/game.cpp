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

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
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
    origine = Point3D();
    taille = 0.;
}

Cube::Cube(Point3D origine, double taille) {
    this->origine = origine;
    this->taille = taille;
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
    tab[0][0][0] = origine;
    tab[0][0][1] = Point3D(origine.getX() + taille, origine.getY(), origine.getZ());
    tab[0][1][0] = Point3D(origine.getX(), origine.getY() + taille, origine.getZ());
    tab[0][1][1] = Point3D(origine.getX() + taille, origine.getY() + taille, origine.getZ());
    
    tab[1][0][0] = Point3D(origine.getX(), origine.getY(), origine.getZ() + taille);
    tab[1][0][1] = Point3D(origine.getX() + taille, origine.getY(), origine.getZ() + taille);
    tab[1][1][0] = Point3D(origine.getX(), origine.getY() + taille, origine.getZ() + taille);
    tab[1][1][1] = Point3D(origine.getX() + taille, origine.getY() + taille, origine.getZ() + taille);
    
}

void Cube::RenderDrawCube(SDL_Renderer *renderer, int a, int b, int c) {
    double angle = 0.9546951008;
    /*Point3D tab[2][2][2];
    getNodes(tab);
    Square s1 = Square(tab[0][0][0].toPoint2D(), tab[0][0][1].toPoint2D(), tab[0][1][1].toPoint2D(), tab[0][1][0].toPoint2D());
    s1.RenderDrawSquare(renderer);
    Square s2 = Square(tab[1][0][0].toPoint2D(), tab[1][0][1].toPoint2D(), tab[1][1][1].toPoint2D(), tab[1][1][0].toPoint2D());
    s2.RenderDrawSquare(renderer);
    Square s3 = Square(tab[0][0][1].toPoint2D(), tab[1][0][1].toPoint2D(), tab[1][1][1].toPoint2D(), tab[0][1][1].toPoint2D());
    s3.RenderDrawSquare(renderer);
    Square s4 = Square(tab[0][0][0].toPoint2D(), tab[1][0][0].toPoint2D(), tab[1][1][0].toPoint2D(), tab[0][1][0].toPoint2D());
    s4.RenderDrawSquare(renderer);*/
    int taille = 20;
    Point2D A = Point2D(a - b, (a + b) * cos(angle) + 2 * c * cos(angle));
    Point2D B = Point2D(a - b + taille, (a + b + taille) * cos(angle) + 2 * (c) * cos(angle));
    Point2D C = Point2D(a - b, (a + b + 2 * taille) * cos(angle) + 2 * c * cos(angle));
    Point2D D = Point2D(a - b - taille, (a + b + taille) * cos(angle) + 2 * c * cos(angle));
    Point2D E = Point2D(a - b, (a + b) * cos(angle) + 2 * (c + taille) * cos(angle));
    Point2D F = Point2D(a - b + taille, (a + b + taille) * cos(angle) + 2 * (c + taille) * cos(angle));
    Point2D G = Point2D(a - b, (a + b + 2 * taille) * cos(angle) + 2 * (c + taille) * cos(angle));
    Point2D H = Point2D(a - b - taille, (a + b + taille) * cos(angle) + 2 * (c + taille) * cos(angle));
    
    Square s1 = Square(A, B, C, D);
    Square s2 = Square(E, F, G, H);
    Square s3 = Square(A, E, H, D);
    Square s4 = Square(B, C, G, F);
    
    s1.RenderDrawSquare(renderer);
    s2.RenderDrawSquare(renderer);
    s3.RenderDrawSquare(renderer);
    s4.RenderDrawSquare(renderer);
    
}
// End Cube Methods

// Camera Methods

Camera::Camera() {
    x = 0;
    y = 0;
    z = 0;
}

Camera::Camera(int a, int b, int c) {
    x = a;
    y = b;
    z = c;
}

int Camera::getX() {
    return x;
}
int Camera::getY() {
    return y;
}
int Camera::getZ() {
    return z;
}
// End Camera Methods

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

// Point Methods
Point::Point() {
    x = 0;
    y = 0;
}

Point::Point(int abscisse, int ordonnee) {
    x = abscisse;
    y = ordonnee;
}

double Point::getX() {
    return x;
}

double Point::getY() {
    return y;
}
// End Point Methods

// Segment Methods
Segment::Segment() {
    p1 = Point();
    p2 = Point();
}

Segment::Segment(Point a, Point b) {
    p1 = a;
    p2 = b;
}

Point Segment::getP1() {
    return p1;
}

Point Segment::getP2() {
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
    enBasAGauche = Point();
    enBasADroite = Point();
    enHautAGauche = Point();
    enHautADroite = Point();
}

Square::Square(Point bg, Point bd, Point hg, Point hd) {
    enBasAGauche = bg;
    enBasADroite = bd;
    enHautAGauche = hg;
    enHautADroite = hd;
}

Point Square::coinEnBasAGauche() {
    return enBasAGauche;
}

Point Square::coinEnBasADroite() {
    return enBasADroite;
}

Point Square::coinEnHautAGauche() {
    return enHautAGauche;
}

Point Square::coinEnHautADroite() {
    return enHautADroite;
}

Point Square::getCentre() {
    return Point((enBasAGauche.getX() + enHautADroite.getX())/2, (enBasAGauche.getY() + enHautADroite.getY())/2);
}

void Square::RenderDrawSquare(SDL_Renderer* renderer) {
    
    Segment s1 = Segment(coinEnBasAGauche(), coinEnBasADroite());
    Segment s2 = Segment(coinEnBasADroite(), coinEnHautADroite());
    Segment s3 = Segment(coinEnHautADroite(), coinEnHautAGauche());
    Segment s4 = Segment(coinEnHautAGauche(), coinEnBasAGauche());

    s1.RenderDrawSegment(renderer);
    s2.RenderDrawSegment(renderer);
    s3.RenderDrawSegment(renderer);
    s4.RenderDrawSegment(renderer);
    
}

Point* Square::getPoints() {

    Point tab[] = {coinEnBasAGauche(), coinEnBasADroite(), coinEnHautADroite(), coinEnHautAGauche()};
    return tab;
}

void Square::rotate(double alpha) {
    
    Point centre = Point(
                         (coinEnBasAGauche().getX() + coinEnHautADroite().getX()) / 2,
                         (coinEnBasAGauche().getY() + coinEnHautADroite().getY()) / 2
                         );

    Point tab[] = {Point(),Point(),Point(),Point()};
    
    for (int i = 0; i < 4; i++) {
        Point p = getPoints()[i];
        int a = p.getX() - centre.getX();
        int b = p.getY() - centre.getY();
        double d = hypot((double)b,(double)a);
        double theta  = atan2((double)b, (double)a) + alpha;
        
        tab[i] = Point(centre.getX() + d * cos(theta), centre.getY() + d * sin(theta));
    }
    enBasAGauche = tab[0];
    enBasADroite = tab[1];
    enHautADroite = tab[2];
    enHautAGauche = tab[3];
}

// End Square Methods

//
//  square.cpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "square.hpp"

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
    return Point2D((coinEnBasAGauche().getX() + coinEnHautADroite().getX())/2, (coinEnBasAGauche().getY() + coinEnHautADroite().getY())/2);
}

Point2D* Square::getNodes() {
    
    Point2D *tab = new Point2D[4];
    tab[0] = coinEnBasAGauche();
    tab[1] = coinEnBasADroite();
    tab[2] = coinEnHautADroite();
    tab[3] = coinEnHautAGauche();
    return tab;
}

void Square::rotate(double alpha) {
    Point2D centre = Point2D(
                             (coinEnBasAGauche().getX() + coinEnHautADroite().getX()) / 2,
                             (coinEnBasAGauche().getY() + coinEnHautADroite().getY()) / 2
                             );
    
    Point2D tab[] = {Point2D(),Point2D(),Point2D(),Point2D()};
    
    Point2D *p = getNodes();
    for (int i = 0; i < 4; i++) {
        double a = p[i].getX() - centre.getX();
        double b = p[i].getY() - centre.getY();
        double d = hypot(b,a);
        double theta  = atan2(b, a) + alpha;
        
        tab[i] = Point2D(centre.getX() + d * cos(theta), centre.getY() + d * sin(theta));
    }
    delete[] p;
    enBasAGauche = tab[0];
    enBasADroite = tab[1];
    enHautADroite = tab[2];
    enHautAGauche = tab[3];
}

void Square::fill(SDL_Renderer* renderer) {
    
    Point2D A = coinEnBasAGauche();
    Point2D B = coinEnBasADroite();
    Point2D C = coinEnHautAGauche();
    
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

void Square::RenderDrawSquare(SDL_Renderer* renderer) {
    
    Uint8 r = 0;
    Uint8 g = 0;
    Uint8 b = 0;
    Uint8 a = 0;
    int test = SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    if (test != 0)
        SDL_GetError();
    
    Segment s1 = Segment(coinEnBasAGauche(), coinEnBasADroite());
    Segment s2 = Segment(coinEnBasADroite(), coinEnHautADroite());
    Segment s3 = Segment(coinEnHautADroite(), coinEnHautAGauche());
    Segment s4 = Segment(coinEnHautAGauche(), coinEnBasAGauche());
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    s1.RenderDrawSegment(renderer);
    s2.RenderDrawSegment(renderer);
    s3.RenderDrawSegment(renderer);
    s4.RenderDrawSegment(renderer);
    
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

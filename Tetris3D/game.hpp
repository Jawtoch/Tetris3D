//
//  game.hpp
//  programmation avancée
//
//  Created by ugo cottin on 09/10/2018.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>

class Point {
    
private:
    double x;
    double y;
    
public:
    Point();
    Point(int abscisse, int ordonnee);
    double getX();
    double getY();
};

class Segment {
    
private:
    Point p1;
    Point p2;
    
public:
    Segment();
    Segment(Point a, Point b);
    Point getP1();
    Point getP2();
    Point centre();
    void RenderDrawSegment(SDL_Renderer* renderer);
};

class Square {
    
private:
    Point enBasAGauche;
    Point enBasADroite;
    Point enHautAGauche;
    Point enHautADroite;
    
public:
    Square();
    Square(Point bg, Point bd, Point hg, Point hd);
    Point coinEnBasAGauche();
    Point coinEnBasADroite();
    Point coinEnHautAGauche();
    Point coinEnHautADroite();
    Point getCentre();
    void RenderDrawSquare(SDL_Renderer* renderer, Square square);
    
};

#endif /* game_hpp */

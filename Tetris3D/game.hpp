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

class Point2D {
    
private:
    double x;
    double y;
    
public:
    Point2D();
    Point2D(double abscisse, double ordonnee);
    double getX();
    double getY();
};

class Segment {
    
private:
    Point2D p1;
    Point2D p2;
    
public:
    Segment();
    Segment(Point2D a, Point2D b);
    Point2D getP1();
    Point2D getP2();
    Point2D centre();
    void RenderDrawSegment(SDL_Renderer* renderer);
};

class Square {
    
private:
    Point2D enBasAGauche;
    Point2D enBasADroite;
    Point2D enHautAGauche;
    Point2D enHautADroite;
    
public:
    Square();
    Square(Point2D bg, Point2D bd, Point2D hg, Point2D hd);
    Point2D coinEnBasAGauche();
    Point2D coinEnBasADroite();
    Point2D coinEnHautAGauche();
    Point2D coinEnHautADroite();
    Point2D getCentre();
    Point2D* getNodes();
    void RenderDrawSquare(SDL_Renderer* renderer);
    void rotate(double alpha);
    
};

class Point3D {
    
private:
    double x;
    double y;
    double z;

public:
    Point3D();
    Point3D(double a, double b, double c);
    double getX();
    double getY();
    double getZ();
    
};

class Cube {
    
private:
    Point3D enBasAGaucheDevant;
    Point3D enBasADroiteDevant;
    Point3D enHautAGaucheDevant;
    Point3D enHautADroiteDevant;
    Point3D enBasAGaucheDerriere;
    Point3D enBasADroiteDerriere;
    Point3D enHautAGaucheDerriere;
    Point3D enHautADroiteDerriere;
    
public:
    Cube();
    Cube(Point3D origineEnBasAGaucheDevant, double taille);
    void RenderDrawCube(SDL_Renderer* renderer);
    void getNodes(Point3D tab[2][2][2]);
};

#endif /* game_hpp */

//
//  square.hpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#ifndef square_hpp
#define square_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "point2D.hpp"
#include "segment.hpp"

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
    void remplir(SDL_Renderer* renderer);
    
};

#endif /* square_hpp */

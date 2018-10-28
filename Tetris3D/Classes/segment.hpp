//
//  segment.hpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#ifndef segment_hpp
#define segment_hpp

#include <stdio.h>
#include <SDL2/SDL.h>
#include "point2D.hpp"
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


#endif /* segment_hpp */

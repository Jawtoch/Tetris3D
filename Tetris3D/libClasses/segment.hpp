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
    
    /**
     A segment's point
     */
    Point2D p1;
    
    /**
     A segment's point
     */
    Point2D p2;
    
public:
    
    /**
     Constructor of an empty segment defined by two 2D points, both are on (0,0) coordinates
     */
    Segment();
    
    /**
     Constructor of a segment defined by two 2D points, "a" and "b"
     
     @param a A 2D point first end of the segment
     @param b A 2D point second end of the segment
     */
    Segment(Point2D a, Point2D b);
    
    /**
     Return the 2D point first end of the segment
     
     @return A 2D point first end of the segment
     */
    Point2D getP1();
    
    /**
     Return the 2D point second end of the segment
     
     @return A 2D point second end of the segment
     */
    Point2D getP2();
    
    /**
     Return the segment's center
     
     @return A 2D point with the coordinates of the center of the segment
     */
    Point2D center();
    
    /**
     Add the segment to the Renderer
     
     @param renderer A structure representing rendering state
     */
    void RenderDrawSegment(SDL_Renderer* renderer);
};


#endif /* segment_hpp */

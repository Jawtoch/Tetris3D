//
//  segment.cpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "segment.hpp"

Segment::Segment() {
    p1 = Point2D();
    p2 = Point2D();
}

Segment::Segment(Point2D a, Point2D b) {
    p1 = Point2D(a.getX(), a.getY());
    p2 = Point2D(b.getX(), b.getY());
}

Point2D Segment::getP1() {
    return p1;
}

Point2D Segment::getP2() {
    return p2;
}

Point2D Segment::center() {
    return Point2D(
                   (getP1().getX() + getP2().getX()) / 2,
                   (getP1().getY() + getP2().getY()) / 2);
}

void Segment::RenderDrawSegment(SDL_Renderer* renderer) {
    SDL_RenderDrawLine(renderer, getP1().getX(), getP1().getY(), getP2().getX(), getP2().getY());
    
}

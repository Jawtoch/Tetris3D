//
//  square.hpp
//  Tetris3D
//
//  Created by ugo cottin on 25/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#ifndef square_hpp
#define square_hpp

#include "point2D.hpp"
#include "segment.hpp"

/**
 This structure is intended to represent a square on screen, but also work for any four angles shape. There are no verifications if the objects are really squares or rectangles or anything else.
 */
class Square {
    
private:
    Point2D enBasAGauche;
    Point2D enBasADroite;
    Point2D enHautAGauche;
    Point2D enHautADroite;
    
public:
    
    /**
     Constructor of a empty square, all corners are on (0,0)
     */
    Square();
    
    /**
     Constructor of a square according to this four angles
     @param bg A 2D point representing the bottom left angle
     @param bd A 2D point representing the bottom right angle
     @param hg A 2D point representing the top left angle
     @param hd A 2D point representing the top right angle
     */
    Square(Point2D bg, Point2D bd, Point2D hg, Point2D hd);

    /**
     Return the bottom left angle of the square

     @return A 2D point with the bottom left angle coordinates of the square
     */
    Point2D coinEnBasAGauche();
    
    /**
     Return the bottom right angle of the square
     
     @return A 2D point with the bottom right angle coordinates of the square
     */
    Point2D coinEnBasADroite();
    
    /**
     Return the top left angle of the square
     
     @return A 2D point with the top left angle coordinates of the square
     */
    Point2D coinEnHautAGauche();
    
    /**
     Return the top right angle of the square
     
     @return A 2D point with the top right angle coordinates of the square
     */
    Point2D coinEnHautADroite();
    
    /**
     Return the square center
     
     @return A 2D point with the coordinates of the center
     */
    Point2D getCentre();
    
    /**
     Return the angles of the square
     
     @return An array of four elements containing the four angles of the square
     @discussion The array is dynamicaly allocated with "new"
     @warning After use, free the array with "delete[]"
     */
    Point2D* getNodes();
    
    
    /**
     Rotate the square
     
     @param alpha The rotation angle
     */
    void rotate(double alpha);
    
    
    /**
     Fill the square
     
     @param renderer A structure representing rendering state
     @discussion When applied to the top side of a cube, some pixels are not colored, they are just white. It's an obvious bug
     */
    void fill(SDL_Renderer* renderer);
    
    /**
     Add the square to the renderer
     
     @param renderer A structure representing rendering state
     */
    void RenderDrawSquare(SDL_Renderer* renderer);
    
};

#endif /* square_hpp */

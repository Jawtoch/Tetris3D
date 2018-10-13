//
//  main.cpp
//  Tetris3D
//
//  Created by ugo cottin on 09/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <SDL2/SDL.h>
#include "game.hpp"

#define WINDOW_WIDTH 600

void drawAxes(SDL_Renderer *renderer, int x, int y) {
    for(int i = 0; i <= WINDOW_WIDTH; i++) {
        SDL_RenderDrawPoint(renderer, x, i);
    }
    SDL_RenderDrawLine(renderer, x, y,x + WINDOW_WIDTH,(y + WINDOW_WIDTH) * cos(1.5707963268));
    SDL_RenderDrawLine(renderer, x, y,x - WINDOW_WIDTH,(y - WINDOW_WIDTH) * cos(1.5707963268));
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    /*Point2D p1 = Point2D(200, 300);
    Point2D p2 = Point2D(300, 300);
    Point2D p3 = Point2D(300, 200);
    Point2D p4 = Point2D(200, 200);
    
    Square s = Square(p1, p2, p3, p4);
    s.rotate(1.1);
    s.RenderDrawSquare(renderer);
    SDL_RenderPresent(renderer);*/
    
    /*for(int i = 0; i < WINDOW_WIDTH; i++) {
        SDL_RenderDrawPoint(renderer, i, i*cos(0.5236));
        SDL_RenderDrawPoint(renderer, WINDOW_WIDTH/2, i);
        SDL_RenderDrawPoint(renderer, i, WINDOW_WIDTH - i*cos(0.5236));
        
    }*/
    //drawAxes(renderer, WINDOW_WIDTH / 2, WINDOW_WIDTH / 2);
    
    int x,y;
    double angle = 0.9546951008;
    while (1) {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        for(int i = 0; i < WINDOW_WIDTH; i++) {
            SDL_GetMouseState(&x, &y);
            SDL_RenderDrawPoint(renderer, x + i, y + i*cos(angle));
            SDL_RenderDrawPoint(renderer, x - i, y - i*cos(angle));
            
            SDL_RenderDrawPoint(renderer, x + i, y + (-i)*cos(angle));
            SDL_RenderDrawPoint(renderer, x - i, y - (-i)*cos(angle));
            
            SDL_RenderDrawPoint(renderer, x, y + i);
            SDL_RenderDrawPoint(renderer, x, y - i);
            
            Cube c1 = Cube(Point3D(x, y, 0), 10.);
            c1.RenderDrawCube(renderer, x, y, 0);
            
        }
        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    
    return 0;
}

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

#include <thread>
#include <chrono>

#define WINDOW_WIDTH 600

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
    
    Cube c = Cube(Point3D(100, 100, 100), 100.);
    c.RenderDrawCube(renderer, 32);
    SDL_RenderPresent(renderer);
    
    while (1) {
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    
    return 0;
}

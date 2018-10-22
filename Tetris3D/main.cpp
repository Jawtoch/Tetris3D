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

void renderArray(SDL_Renderer *renderer, int x, int y, Cube*** T) {
    
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            for(int k = 9; k >= 0; k--) {
                Cube c = T[i][j][k];
                if (c.doesExist())
                    c.RenderDrawCube(renderer, i, j, k, x, y);
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    Cube*** T = creer_tableau(10, 10, 10);
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            for(int k = 0; k < 10; k++) {
                T[i][j][k] = Cube(0);
            }
        }
    }
    T[0][0][0] = Cube(20);
    T[0][0][0] = Cube(20);
    T[0][0][1] = Cube(20);
    T[0][0][2] = Cube(20);
    T[0][0][3] = Cube(20);
    T[1][0][3] = Cube(20);
    T[2][0][3] = Cube(20);
    T[3][0][3] = Cube(20);
    T[3][1][3] = Cube(20);
    T[3][2][3] = Cube(20);
    T[3][3][3] = Cube(20);
    T[2][3][3] = Cube(20);
    T[1][3][3] = Cube(20);
    T[0][3][3] = Cube(20);


    
    
    int x = 0,y = 0;
    double angle = 0.9546951008;
    while (1) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for(int i = 0; i < WINDOW_WIDTH; i++) {
            SDL_GetMouseState(&x, &y);
            SDL_RenderDrawPoint(renderer, x + i, y + i*cos(angle));
            SDL_RenderDrawPoint(renderer, x - i, y - i*cos(angle));
            
            SDL_RenderDrawPoint(renderer, x + i, y + (-i)*cos(angle));
            SDL_RenderDrawPoint(renderer, x - i, y - (-i)*cos(angle));
            
            SDL_RenderDrawPoint(renderer, x, y + i);
            SDL_RenderDrawPoint(renderer, x, y - i);
            
        }
        renderArray(renderer, x, y, T);
        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
            break;
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    
    return 0;
}

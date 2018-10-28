//
//  main.cpp
//  Tetris3D
//
//  Created by ugo cottin on 09/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "main.hpp"
#include "game.hpp"

#define WINDOW_WIDTH 600

void renderArray(SDL_Renderer *renderer, int x, int y, Cube*** T) {
    Cube *c = new Cube(sizeof(Cube));
    for(int i = 0; i < (sizeof(Cube)/sizeof(Cube*)); i++) {
        for(int j = 0; j < (sizeof(Cube*)/sizeof(Cube**)); j++) {
            for(int k = (sizeof(Cube**)/sizeof(Cube***)) - 1; k >= 0; k--) {
                *c = T[i][j][k];
                if (c->doesExist())
                    c->RenderDrawCube(renderer, i, j, k, x, y);
            }
        }
    }
    delete c;
}

void RenderDrawAxes(SDL_Renderer *renderer, int x, int y) {
    for(int i = 0; i < WINDOW_WIDTH; i++) {
        SDL_RenderDrawPoint(renderer, x + i, y + i*cos(ANGLE));
        SDL_RenderDrawPoint(renderer, x - i, y - i*cos(ANGLE));
        
        SDL_RenderDrawPoint(renderer, x + i, y + (-i)*cos(ANGLE));
        SDL_RenderDrawPoint(renderer, x - i, y - (-i)*cos(ANGLE));
        
        SDL_RenderDrawPoint(renderer, x, y + i);
        SDL_RenderDrawPoint(renderer, x, y - i);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    SDL_Event *event = new SDL_Event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_WIDTH, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    Cube*** T = createArray(3, 3, 3);
    
    T[0][0][0] = Cube(20);
    T[0][0][1] = Cube(20);
    T[0][1][1] = Cube(20);
    T[1][1][1] = Cube(20);
    
    Form f1 = Form(T);
    /*freeArray(T);
    T = createArray(3, 3, 3);
    
    T[1][0][0] = Cube(20);
    T[2][1][0] = Cube(20);
    T[2][2][0] = Cube(20);
    Form f2 = Form(T);
    freeArray(T);*/

    Cube*** container = createArray(10, 10, 10);
    
    Cube *c = new Cube(sizeof(Cube));
    Point3D *p3 = new Point3D;
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            for(int k = 0; k < 3; k++) {
                *c = f1.getElements()[i][j][k];
                if (c->doesExist()) {
                    *p3 = f1.getOrigine();
                    container[i + (int)(p3->getX())][j + (int)(p3->getY())][k + (int)(p3->getZ())] = *c;
                }
            }
        }
    }
    
    
    while (1) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        RenderDrawAxes(renderer, WINDOW_WIDTH/2, WINDOW_WIDTH/2);
        renderArray(renderer, WINDOW_WIDTH/2, WINDOW_WIDTH / 2, container);
        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(event) && event->type == SDL_QUIT)
            break;
    }
    delete event;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    
    return 0;
}

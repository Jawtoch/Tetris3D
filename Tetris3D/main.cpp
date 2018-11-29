//
//  main.cpp
//  Tetris3D
//
//  Created by ugo cottin on 09/10/2018.
//  Copyright © 2018 ugocottin. All rights reserved.
//

#include "main.hpp"

#define WINDOW_WIDTH 600

/*void renderArray(SDL_Renderer *renderer, int x, int y, Cube*** T) {
    Cube *c = new Cube(sizeof(Cube));
    
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            for(int k = 2; k >= 0; k--) {
                *c = T[i][j][k];
                if (c->doesExist())
                    c->RenderDrawCube(renderer, i, j, k, x, y);
            }
        }
    }
    delete c;
}*/

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
    SDL_SetWindowTitle(window, "Tetris3D");
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    FormGenerator generate = FormGenerator();
    
    Container board = Container();
    Cube*** T = createArray(3, 3, 3);
    
    //First form
    T[0][0][0] = Cube(20);
    T[0][0][1] = Cube(20);
    T[0][0][2] = Cube(20);
    T[0][1][0] = Cube(20);
    T[0][1][1] = Cube(20);
    T[0][1][2] = Cube(20);
    T[0][2][0] = Cube(20);
    T[0][2][1] = Cube(20);
    T[0][2][2] = Cube(20);
    
    Form f1 = Form(T);
    freeArray(T,3,3,3);
    generate.addForm(f1);
    
    //Second form
    T = createArray(3, 3, 3);
    
    T[0][0][0] = Cube(20);
    T[1][0][0] = Cube(20);
    T[1][1][0] = Cube(20);
    T[1][2][0] = Cube(20);
    Form f2 = Form(T);
    freeArray(T,3,3,3);
    generate.addForm(f2);
    
    //Third form
    T = createArray(3, 3, 3);

    T[0][0][0] = Cube(20);
    T[0][0][1] = Cube(20);
    T[0][0][2] = Cube(20);
    Form f3 = Form(T);
    freeArray(T,3,3,3);
    generate.addForm(f3);
    
    Form *currentForm = generate.getForm();
    
    int gameover = 0;
    int temps = 0;
    
    while (!gameover) {
        temps += 1;
        /* look for an event */
        if (SDL_PollEvent(event)) {
            /* an event was found */
            switch (event->type) {
                    /* close button clicked */
                case SDL_QUIT:
                    gameover = 1;
                    break;
                    /* handle the keyboard */
                case SDL_KEYDOWN:
                    switch (event->key.keysym.sym) {
                        case SDLK_ESCAPE:
                            gameover = 1;
                            break;
                        case SDLK_RETURN:
                            board.addForm(*currentForm);
                            currentForm = generate.getForm();
                            break;
                        case SDLK_q:
                            currentForm->move(-1, 0, 0);
                            break;
                        case SDLK_d:
                            currentForm->move(1, 0, 0);
                            break;
                        case SDLK_z:
                            currentForm->move(0, 0, -1);
                            break;
                        case SDLK_s:
                            currentForm->move(0, 0, 1);
                            break;
                        case SDLK_a:
                            currentForm->move(0, -1, 0);
                            break;
                        case SDLK_e:
                            currentForm->move(0, 1, 0);
                            break;
                        default:
                            break;
                    }
                    break;
            }
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            RenderDrawAxes(renderer, WINDOW_WIDTH/2, WINDOW_WIDTH/8);
            board.RenderDrawContainer(renderer, WINDOW_WIDTH/2, WINDOW_WIDTH/8);
            currentForm->RenderDrawForm(renderer, WINDOW_WIDTH/2, WINDOW_WIDTH/8);
            SDL_RenderPresent(renderer);
        }
    }
    delete event;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}

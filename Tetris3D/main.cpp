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
    
    //Third form
    T = createArray(3, 3, 3);
    
    T[0][0][0] = Cube(20);
    Form f4 = Form(T);
    freeArray(T,3,3,3);
    generate.addForm(f4);
    
    Form *currentForm = generate.getForm();
    
    int gameover = 0;
    int score = 0;
    time_t now, begining;
    time(&begining);
    time(&now);
    
    int count = 0, seconds = 0;
    bool refresh = false;
    while (!gameover) {
        
        refresh = false;
        
        time(&now);
        if ((int)difftime(now, begining) != seconds) {
            seconds = (int)difftime(now, begining);
            count++;
            if (count == DIFFICULTE) {
                count = 0;
                bool placedForm = currentForm->move(0, 0, 1, board.getElements());
                if (!placedForm) { // Form cannot go down anymore
                    score+= currentForm->getScore();
                    board.addForm(*currentForm);
                    std::cout << "Score : " << score << std::endl;
                    currentForm = generate.getForm();
                }
                refresh = true;
            }
        }
        
        /* look for an event */
        if (SDL_PollEvent(event)) {
            /* an event was found */
            refresh = true;
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
                        case SDLK_q:
                            currentForm->move(-1, 0, 0, board.getElements());
                            break;
                        case SDLK_d:
                            currentForm->move(1, 0, 0, board.getElements());
                            break;
                        case SDLK_s:
                            currentForm->move(0, -1, 0, board.getElements());
                            break;
                        case SDLK_z:
                            currentForm->move(0, 1, 0, board.getElements());
                            break;
                        default:
                            break;
                    }
                    break;
            }
        }
        if (refresh) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderClear(renderer);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            RenderDrawAxes(renderer, WINDOW_WIDTH/2, WINDOW_WIDTH/8);
            board.RenderDrawContainer(renderer, WINDOW_WIDTH/2, WINDOW_WIDTH/8, *currentForm);
            //currentForm->RenderDrawForm(renderer, WINDOW_WIDTH/2, WINDOW_WIDTH/8);
            SDL_RenderPresent(renderer);
        }
    }
    delete event;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    std::cout << "Gameover, your score is " << score << std::endl;
    
    return 1;
}

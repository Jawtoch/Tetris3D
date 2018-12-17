//
//  game.cpp
//  programmation avancée
//
//  Created by ugo cottin on 09/10/2018.
//

#include "game.hpp"

Game::Game() {
    nbForms = 9;
    difficuly = 3;
    windowsWidth = 600;
    formMaxSize = 3;
    containerMaxSize = 10;
}

void Game::start() {
    
    SDL_Event *event = new SDL_Event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(windowsWidth, windowsWidth, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Tetris3D");
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    FormGenerator generate = FormGenerator(containerMaxSize, formMaxSize);
    for(int i = 1; i <= nbForms; i++) {
        Form *f = new Form(choose_form(i, formMaxSize), containerMaxSize, formMaxSize);
        generate.addForm(*f);
    }
    Container board = Container(containerMaxSize, formMaxSize);
    
    int gameover = 0;
    int score = 0;
    time_t now, begining;
    time(&begining);
    time(&now);
    
    int count = 0, seconds = 0;
    bool refresh = false;
    
    Form *currentForm = generate.getForm();
    
    while (!gameover) {
        
        refresh = false;
        
        time(&now);
        if ((int)difftime(now, begining) != seconds) {
            seconds = (int)difftime(now, begining);
            count++;
            if (count == difficuly) {
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
            board.RenderDrawContainer(renderer, windowsWidth/2, windowsWidth/8, *currentForm);
            RenderDrawBorders(renderer, windowsWidth/2, windowsWidth/8);
            SDL_RenderPresent(renderer);
        }
    }
    delete event;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    std::cout << "Gameover, your score is " << score << std::endl;
}

void Game::RenderDrawBorders(SDL_Renderer *renderer, int shiftX, int shiftY) {
    Cube cub = Cube(20 * containerMaxSize);

    int a = 0, b = 0, c = 0;

    Point2D A = Point2D(a - b + shiftX, (a + b) * cos(ANGLE) + 2 * c * cos(ANGLE) + shiftY);
    Point2D B = Point2D(a - b + cub.getSize() + shiftX, (a + b + cub.getSize()) * cos(ANGLE) + 2 * (c) * cos(ANGLE) + shiftY);
    Point2D C = Point2D(a - b + shiftX, (a + b + 2 * cub.getSize()) * cos(ANGLE) + 2 * c * cos(ANGLE) + shiftY);
    Point2D D = Point2D(a - b - cub.getSize() + shiftX, (a + b + cub.getSize()) * cos(ANGLE) + 2 * c * cos(ANGLE) + shiftY);
    Point2D E = Point2D(a - b + shiftX, (a + b) * cos(ANGLE) + 2 * (c + cub.getSize()) * cos(ANGLE) + shiftY);
    Point2D F = Point2D(a - b + cub.getSize() + shiftX, (a + b + cub.getSize()) * cos(ANGLE) + 2 * (c + cub.getSize()) * cos(ANGLE) + shiftY);
    Point2D G = Point2D(a - b + shiftX, (a + b + 2 * cub.getSize()) * cos(ANGLE) + 2 * (c + cub.getSize()) * cos(ANGLE) + shiftY);
    Point2D H = Point2D(a - b - cub.getSize() + shiftX, (a + b + cub.getSize()) * cos(ANGLE) + 2 * (c + cub.getSize()) * cos(ANGLE) + shiftY);
    
    Square s1 = Square(A, B, C, D);
    Square s2 = Square(B, C, G, F);
    Square s3 = Square(C, D, H, G);
    Square s4 = Square(A, D, H, E);
    Square s5 = Square(A, B, F, E);
    
    s1.RenderDrawSquare(renderer);
    s2.RenderDrawSquare(renderer);
    s3.RenderDrawSquare(renderer);
    s4.RenderDrawSquare(renderer);
    s5.RenderDrawSquare(renderer);
    
    
}

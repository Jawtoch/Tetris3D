//
//  game.hpp
//  programmation avancée
//
//  Created by ugo cottin on 09/10/2018.
//

#ifndef game_hpp
#define game_hpp

#include "libClasses/point2D.hpp"
#include "libClasses/segment.hpp"
#include "libClasses/square.hpp"
#include "libClasses/point3D.hpp"
#include "libClasses/cube.hpp"
#include "libClasses/form.hpp"
#include "libClasses/container.hpp"
#include "libClasses/formGenerator.hpp"

class Game {
    int nbForms;
    int difficuly;
    int windowsWidth;
    int formMaxSize;
    int containerMaxSize;
public:
    Game();
    void start();
    void RenderDrawBorders(SDL_Renderer *renderer, int shiftX, int shiftY);
};

#endif /* game_hpp */

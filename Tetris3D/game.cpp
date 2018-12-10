//
//  game.cpp
//  programmation avancée
//
//  Created by ugo cottin on 09/10/2018.
//

#include "game.hpp"

#define NB_PIECES 10

int main() {
    
    FormGenerator generator = FormGenerator();
    
    for(int i = 0; i < NB_PIECES; i++) {
        string s = "form" + i + ".txt"; // a revoir
        int*** piece = file_to_array(s); // existe deja
        Cube*** c = intVersCube(piece); // a écrire
        generator.addForm(c); // existe deja
    
}

/*

 ->récupère la ligne
    -> cherche les trois axes
    -> si les trois non présents
        -> ERREUR
    -> sinon
        -> switch
            -> si x
                -> x = ?
            -> si y
            ...
 
 */

# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 2.0)

# Notre projet est étiqueté libClasses
PROJECT(Tetris3D)

# Ajout de la bibliothèque Classes
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/libClasses)

# Recherche de SDL2
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")

# Crée des variables avec les fichiers à compiler
SET(SRCS
main.cpp
game.cpp
    )
    
SET(HEADERS
main.hpp
game.hpp
    )

FIND_PACKAGE(SDL2 REQUIRED)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR})

ADD_EXECUTABLE(main ${SRCS} ${HEADERS})
TARGET_LINK_LIBRARIES(main ${SDL2_LIBRARY})
TARGET_LINK_LIBRARIES(main Classes)

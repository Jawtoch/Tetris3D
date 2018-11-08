# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 2.0)

# Notre projet est étiqueté libClasses
PROJECT(libClasses)

# Recherche de SDL2
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "../cmake")

# Crée des variables avec les fichiers à compiler
SET(SRCS
point2D.cpp
segment.cpp
square.cpp
point3D.cpp
cube.cpp
form.cpp
container.cpp
    )
    
SET(HEADERS
point2D.hpp
segment.hpp
square.hpp
point3D.hpp
cube.hpp
form.hpp
container.hpp
    )

FIND_PACKAGE(SDL2 REQUIRED)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIR})

ADD_LIBRARY(Classes ${SRCS} ${HEADERS})
TARGET_LINK_LIBRARIES(Classes ${SDL2_LIBRARY})
#!/bin/bash
CPP_FLAG="-Wall -Wextra -pedantic"
SFML="-lsfml-graphics -lsfml-window -lsfml-system"

g++ $CPP_FLAG $SFML DoublePendulum.cpp -o DoublePendulum
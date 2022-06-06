#pragma once

#include <string>

class Card {
public:
    std::string suit;
    std::string description;
    int rank;
    int value;
public:
    Card();
};

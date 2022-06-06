#pragma once

#include "Card.h"

#include <string>
#include <iostream>

class CardArray {
public:
    static const int MAX_CARDS = 52;
    static const int TYPES = 4;
    static const int MAX_PER_HAND = 12;
public:
    Card* cards;
    int max_size;
    int curr_size;
public:
    CardArray();
    ~CardArray();
    void populate();
    void shuffle();
    int score() const;
    std::string get_hand() const;
    void optimize();
    void advice() const;

    friend std::ostream& operator<<(std::ostream& ostr, const CardArray& deck);
private:
    std::string generate_suit(int index);
    std::string generate_description(int index);
    int generate_rank(int index);
    int generate_value(int index);
};

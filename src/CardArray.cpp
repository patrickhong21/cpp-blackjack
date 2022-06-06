#include "CardArray.h"

#include <iostream>
#include <sstream>

CardArray::CardArray():
    cards(nullptr),
    max_size(0),
    curr_size(0) {
}

CardArray::~CardArray() {
    delete[] cards;
}

namespace spades {
    const std::string NAME = "spades";
    const std::string LABEL = "S";
    const int BEGIN = 1;
    const int END = 13;
}

namespace hearts {
    const std::string NAME = "hearts";
    const std::string LABEL = "H";
    const int BEGIN = 14;
    const int END = 26;
}

namespace diamonds {
    const std::string NAME = "diamonds";
    const std::string LABEL = "D";
    const int BEGIN = 27;
    const int END = 39;
}

namespace clubs {
    const std::string NAME = "clubs";
    const std::string LABEL = "C";
    const int BEGIN = 40;
    const int END = 52;
}

void CardArray::populate() {
    max_size = MAX_CARDS;
    curr_size = MAX_CARDS;
    cards = new Card[MAX_CARDS];

    for (int i = 1; i <= MAX_CARDS; i++) {
        cards[i - 1].suit = generate_suit(i);
        cards[i - 1].description = generate_description(i);
        cards[i - 1].rank = generate_rank(i);
        cards[i - 1].value = generate_value(i);
    }
}

void CardArray::shuffle() {
    srand((unsigned) time(nullptr));
    Card temp;

    for (int i = 0; i < 52; i++) {
        Card& curr = cards[i];
        Card& random_card = cards[rand() % 52]; // 0-51

        temp = curr;
        curr = random_card;
        random_card = temp;
    }
}

int CardArray::score() const {
    int score = 0;
    for (int i = 0; i < curr_size; i++) {
        score += cards[i].value;
    }
    return score;
}

std::string CardArray::get_hand() const {
    std::stringstream ss;
    for (int i = 0; i < curr_size; i++) {
        ss << cards[i].description << " ";
    }
    return ss.str();
}

void CardArray::optimize() {
    for (int i = curr_size - 1; i >= 0; i--) {
        if (cards[i].value == 11) {
            cards[i].value = 1;
            break;
        }
    }
}

void CardArray::advice() const {
    if (score() < 12) {
        std::cout << "ADVICE: You should definitely hit since you cannot bust!";
    } else if (score() >= 12 && score() < 17) {
        std::cout << "ADVICE: You should hit if there are lots of high value cards on the table.";
    } else {
        std::cout << "ADVICE: If you hit, you have a high chance of busting based on the statistics.";
    }
}

std::string CardArray::generate_suit(int index) {
    if (index >= spades::BEGIN && index <= spades::END) {
        return "spades";
    } else if (index >= hearts::BEGIN && index <= hearts::END) {
        return "hearts";
    } else if (index >= diamonds::BEGIN && index <= diamonds::END) {
        return "diamonds";
    } else {
        return "clubs";
    }
}

std::string CardArray::generate_description(int index) {
    std::stringstream out;
    int rank = generate_rank(index);
    char suit_initial = toupper(generate_suit(index)[0]); // first letter uppercase

    if (rank == 1) {
        out << "A";
    } else if (rank == 11) {
        out << "J";
    } else if (rank == 12) {
        out << "Q";
    } else if (rank == 13) {
        out << "K";
    } else {
        out << rank;
    }
    out << suit_initial; // append suit inital

    return out.str();
}

int CardArray::generate_rank(int index) {
    return ((index - 1) % (MAX_CARDS / TYPES)) + 1;
}

int CardArray::generate_value(int index) {
    int rank = generate_rank(index);
    if (rank == 1) {
        return 11;
    } else if (rank >= 11 && rank <= 13) {
        return 10;
    }
    return rank;
}

std::ostream &operator<<(std::ostream& ostr, const CardArray& deck) {
    for (int i = 0; i < CardArray::MAX_CARDS; i++) {
        ostr << deck.cards[i].description << "\t";
        if (i % 13 == 12) {
            ostr << "\n";
        }
    }
}

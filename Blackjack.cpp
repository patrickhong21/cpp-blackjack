// blackjack.cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <cmath>
#include <string>

using namespace std;


//Card structure 
struct Card {
    string suit; // card class (ex.hearts)
    string description;
    int rank;
    int value;

    Card() {
        rank = 0;
        value = 0;
        suit = "";
        description = "";
    }
};

struct CardArray
{
    Card* cards;
    int max_used;
    int current_cards;

    CardArray() {
        cards = nullptr;
        max_used = 0;
        current_cards = 0;
    }
};

void get_new_deck(CardArray& deck); //function to fill deck with cards
void print_deck(const CardArray& deck); //function to print description of card in a deck
void shuffle_deck(CardArray& deck); // function to shuffle deck of cards
int blackjack(CardArray& deck); //function to play the game
void deal(CardArray& deck, CardArray& hand); // for dealer and player to be able to draw cards
int score(CardArray& hand); // to keep track of the value of the cards from the total cards in hand
void print_hands(const CardArray& deck); // to print the values of the cards keeping it separate from print deck for no interference
int play_games(CardArray& deck);//where the black jack game will be played


int main() {
    srand(time(0));
    CardArray x;
    get_new_deck(x);
    print_deck(x);
    cout << "   " << endl;
    shuffle_deck(x);
    cout << " " << endl;
    cout << "Shuffled" << endl;

    cout << " " << endl;
    print_deck(x);
    cout << "    " << endl;
    play_games(x);

    delete[] x.cards;
}

//function to populate "CardArray" with standard deck of cards
void get_new_deck(CardArray& deck) {
    deck.max_used = 52;
    deck.current_cards = 52;
    deck.cards = new Card[52];

    //for loops to identify and seperate each suit and rank with the proper value
    for (int x = 0; x < 13; x++) {
        deck.cards[x].suit = "spades";
        deck.cards[x].rank = x + 1;
        deck.cards[x].description = to_string(x + 1) + "S";
        deck.cards[x].value = x + 1;
    }

    deck.cards[0].value = 11;
    deck.cards[0].description = "AS";
    deck.cards[10].description = "JS";
    deck.cards[10].value = 10;
    deck.cards[11].description = "QS";
    deck.cards[11].value = 10;
    deck.cards[12].description = "KS";
    deck.cards[12].value = 10;

    for (int x = 0; x < 13; x++) {
        deck.cards[x + 13].suit = "hearts";
        deck.cards[x + 13].rank = x + 1;
        deck.cards[x + 13].description = to_string(x + 1) + "H";
        deck.cards[x + 13].value = x + 1;
    }

    deck.cards[0 + 13].description = "AH";
    deck.cards[0 + 13].value = 11;
    deck.cards[10 + 13].description = "JH";
    deck.cards[10 + 13].value = 10;
    deck.cards[11 + 13].description = "QH";
    deck.cards[11 + 13].value = 10;
    deck.cards[12 + 13].description = "KH";
    deck.cards[12 + 13].value = 10;

    for (int x = 0; x < 13; x++) {
        deck.cards[x + 26].suit = "diamonds";
        deck.cards[x + 26].rank = x + 1;
        deck.cards[x + 26].description = to_string(x + 1) + "D";
        deck.cards[x + 26].value = x + 1;
    }

    deck.cards[0 + 26].description = "AD";
    deck.cards[0 + 26].value = 11;
    deck.cards[10 + 26].description = "JD";
    deck.cards[10 + 26].value = 10;
    deck.cards[11 + 26].description = "QD";
    deck.cards[11 + 26].value = 10;
    deck.cards[12 + 26].description = "KD";
    deck.cards[12 + 26].value = 10;

    for (int x = 0; x < 13; x++) {
        deck.cards[x + 39].suit = "clubs";
        deck.cards[x + 39].rank = x + 1;
        deck.cards[x + 39].description = to_string(x + 1) + "C";
        deck.cards[x + 39].value = x + 1;
    }

    deck.cards[0 + 39].description = "AC";
    deck.cards[0 + 39].value = 11;
    deck.cards[10 + 39].description = "JC";
    deck.cards[10 + 39].value = 10;
    deck.cards[11 + 39].description = "QC";
    deck.cards[11 + 39].value = 10;
    deck.cards[12 + 39].description = "KC";
    deck.cards[12 + 39].value = 10;
}


//function used to print out the cards of the deck with the value and rank
void print_deck(const CardArray& deck) {
    for (int y = 0; y < deck.max_used; y++) {
        cout << deck.cards[y].description << '\t';
        if (y % 13 == 12) {
            cout << "" << endl;
        }
    }
}

// used for shuffling the deck
void shuffle_deck(CardArray& deck) {
    srand((unsigned)time(NULL));
    Card swapper;
    for (int y = 0; y < 52; y++) {
        int randNum = rand() % 52;
        swapper = deck.cards[y];
        deck.cards[y] = deck.cards[randNum];
        deck.cards[randNum] = swapper;
    }
}

int blackjack(CardArray& deck) {
    CardArray dealer;
    CardArray hand;
    string hit;
    dealer.max_used = 12;
    hand.max_used = 12;
    dealer.cards = new Card[12];
    hand.cards = new Card[12];

    cout << "Deal first card" << endl;
    cout << "---------------" << endl;

    cout << "+Player+: ";
    deal(deck, hand);
    print_hands(hand);
    cout << "" << endl;
    cout << "" << endl;

    cout << "*Dealer*: ";
    deal(deck, dealer);
    print_hands(dealer); // issue for giving so much space
    cout << " " << endl;
    cout << " " << endl;

    if (score(dealer) == 21) {
        cout << "Dealer wins!" << endl;
    } else if (score(hand) == 21) {
        cout << "Player wins!" << endl;
    } else if (score(dealer) == score(hand) && score(hand) == 21) {
        cout << "Game is tied";
    }

    cout << "Deal second card" << endl;
    cout << "----------------" << endl;

    cout << "+Player+: ";
    deal(deck, hand);
    print_hands(hand);
    cout << "" << endl;
    cout << "" << endl;

    cout << "*Dealer*: ";
    deal(deck, dealer);
    cout << dealer.cards[0].description;
    cout << " ?? " << endl;
    cout << "" << endl;
    cout << "" << endl;
    hit = "";
    cout << "ADVICE: If your under 12 you should defintely hit since you cannot bust" << endl;
    cout << "        If your between 12 and 17 you should hit depending on the nubmer of high value cards on the table " << endl;
    cout << "        If you are at or over 17, you have a high chance of busting hence based on the statistics" << endl;

    while (hit != "s" && score(hand) <= 21) {
        cout << " " << endl;
        cout << "Dealing to Player" << endl;
        cout << "---------------" << endl;
        cout << "Enter h to hit or s to stand: ";
        cin >> hit;

        if (hit == "h") {
            cout << "+Player+: ";
            deal(deck, hand);
            print_hands(hand);
        } else {
            cout << "+Player+: ";
            print_hands(hand);
        }
    }

    cout << "" << endl;
    //Decision(hand); //runs to make sure the player has not busted
    cout << "" << endl;

    if (score(hand) <= 21) {
        while (score(dealer) <= 17) {
            deal(deck, dealer);
        }
        cout << "" << endl;
    }


    cout << "*Dealer*: ";
    print_hands(dealer);
    cout << " " << endl;

    //to figure out who wins the game by comparng the scores

    if (score(dealer) == 21) {
        cout << "Blackjack! Dealer Win" << endl;
        return -1;
    } else if (score(hand) == 21) {
        cout << "BlackJack! You Win" << endl;
        return 1;
    } else if (score(dealer) == score(hand) && score(hand) == 21) {
        cout << "Game is tied";
        return 0;
    }


    else if (score(hand) > 21) {
        cout << "You busted, Dealer Win" << endl;
        return -1;
    } else if (score(dealer) > 21) {
        cout << "Dealer busted, You Win" << endl;
        return 1;
    } else if (score(dealer) > score(hand)) {
        cout << "Dealer Win" << endl;
        return -1;
    } else {
        cout << "You Win" << endl;
        return 1;
    }
}

//another print function for the deck to give to the dealer and player to not interfere with print_deck
void print_hands(const CardArray& deck) {
    for (int y = 0; y < deck.max_used; y++) {
        cout << deck.cards[y].description << " ";
    }
}

// function used for drawing cards to the dealer/ user
void deal(CardArray& deck, CardArray& hand){
    if (hand.current_cards <= 12) { //to draw cards and subtracts one card from the deck
        hand.cards[hand.current_cards] = deck.cards[deck.current_cards - 1];
        hand.current_cards++;
        deck.current_cards--;
    }
}

int score(CardArray& hand) {
    int score = 0;

    //depending on how many cards you have in your hand, it'll sum up the score
    for (int x = 0; x < hand.current_cards; x++) {
        score += hand.cards[x].value;
    }
    return score;
}

// where the game is being played
int play_games(CardArray& deck) {
    int wins = 0;
    int draws = 0;
    int losses = 0;
    int current = 0;
    int total = 0;
    string play = "";
    while (play != "n") {

        current = blackjack(deck);

        if (current == -1) {
            losses++;
        } else if (current == 0) {
            draws++;
        } else {
            wins++;
        }

        total++;

        cout << "Do you want to play another hand(y to play)?: ";
        cin >> play;
        cout << " " << endl;
        cout << "-------------------------------------------------- " << endl;
        cout << " " << endl;

    }
    cout << "Thanks for playing, you played " << total << " and your record was: " << endl;
    cout << "wins: " << wins << endl;
    cout << "losses: " << losses << endl;
    cout << "draws: " << draws << endl;

    return 0;
}

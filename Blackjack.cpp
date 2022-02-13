// blackjack.cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <cmath>
#include <string>

using namespace std;


//Card structure 
struct Card
{
    string suit; // card class (ex.hearts)
    string descript;
    int rank;
    int value;

    Card()
    {
        rank = 0;
        value = 0;
        suit = "";
        descript = "";
    }

};

struct CardArray
{
    Card* cards_new;
    int max_used;
    int current_cards;


    CardArray()
    {
        cards_new = nullptr;
        max_used = 0;
        current_cards = 0;


    }
};

void getNewDeck(CardArray& deck); //fucnction to fill deck with cards
void printDeck(const CardArray& deck); //function to print description of card in a deck
void shuffleDeck(CardArray& deck); // function to shuffle deck of cards 
int blackjack(CardArray& deck); //function to play the game
void deal(CardArray& deck, CardArray& hand); // for dealer and player to be able to draw cards
int score(CardArray& hand); // to keep track of the value of the cards from the total cards in hand
void printHands(const CardArray& deck); // to print the values of the cards keeping it seperate from print deck for no interference
void Decision(CardArray& hand); //decides win or lose situation
int hit(CardArray& deck, CardArray& hand, string choice);
int playGames(CardArray& deck);//where the black jack game will be played



int main()
{
    srand(time(0));
    CardArray x;
    getNewDeck(x);
    printDeck(x);
    cout << "   " << endl;
    shuffleDeck(x);
    cout << " " << endl;
    cout << "Shuffled" << endl;

    cout << " " << endl;
    printDeck(x);
    cout << "    " << endl;
    playGames(x);


    delete[] x.cards_new;
}

//function to populate "CardArray" with standard deck of cards
void getNewDeck(CardArray& deck)
{
    deck.max_used = 52;
    deck.current_cards = 52;
    deck.cards_new = new Card[52];

    //for loops to identify and seperate each suit and rank with the proper value
    for (int x = 0; x < 13; x++) {
        deck.cards_new[x].suit = "spades";
        deck.cards_new[x].rank = x + 1;
        deck.cards_new[x].descript = to_string(x + 1) + "S";
        deck.cards_new[x].value = x + 1;
    }

    deck.cards_new[0].value = 11;
    deck.cards_new[0].descript = "AS";
    deck.cards_new[10].descript = "JS";
    deck.cards_new[10].value = 10;
    deck.cards_new[11].descript = "QS";
    deck.cards_new[11].value = 10;
    deck.cards_new[12].descript = "KS";
    deck.cards_new[12].value = 10;


    for (int x = 0; x < 13; x++) {
        deck.cards_new[x + 13].suit = "hearts";
        deck.cards_new[x + 13].rank = x + 1;
        deck.cards_new[x + 13].descript = to_string(x + 1) + "H";
        deck.cards_new[x + 13].value = x + 1;
    }


    deck.cards_new[0 + 13].descript = "AH";
    deck.cards_new[0 + 13].value = 11;
    deck.cards_new[10 + 13].descript = "JH";
    deck.cards_new[10 + 13].value = 10;
    deck.cards_new[11 + 13].descript = "QH";
    deck.cards_new[11 + 13].value = 10;
    deck.cards_new[12 + 13].descript = "KH";
    deck.cards_new[12 + 13].value = 10;


    for (int x = 0; x < 13; x++) {
        deck.cards_new[x + 26].suit = "diamonds";
        deck.cards_new[x + 26].rank = x + 1;
        deck.cards_new[x + 26].descript = to_string(x + 1) + "D";
        deck.cards_new[x + 26].value = x + 1;
    }


    deck.cards_new[0 + 26].descript = "AD";
    deck.cards_new[0 + 26].value = 11;
    deck.cards_new[10 + 26].descript = "JD";
    deck.cards_new[10 + 26].value = 10;
    deck.cards_new[11 + 26].descript = "QD";
    deck.cards_new[11 + 26].value = 10;
    deck.cards_new[12 + 26].descript = "KD";
    deck.cards_new[12 + 26].value = 10;



    for (int x = 0; x < 13; x++) {
        deck.cards_new[x + 39].suit = "clubs";
        deck.cards_new[x + 39].rank = x + 1;
        deck.cards_new[x + 39].descript = to_string(x + 1) + "C";
        deck.cards_new[x + 39].value = x + 1;
    }

    deck.cards_new[0 + 39].descript = "AC";
    deck.cards_new[0 + 39].value = 11;
    deck.cards_new[10 + 39].descript = "JC";
    deck.cards_new[10 + 39].value = 10;
    deck.cards_new[11 + 39].descript = "QC";
    deck.cards_new[11 + 39].value = 10;
    deck.cards_new[12 + 39].descript = "KC";
    deck.cards_new[12 + 39].value = 10;

}


//function used to print out the cards of the deck with the value and rank
void printDeck(const CardArray& deck)
{

    for (int y = 0; y < deck.max_used; y++) {
        cout << deck.cards_new[y].descript << '\t';
        if (y % 13 == 12) {
            cout << "" << endl;
        }
    }

}


void shuffleDeck(CardArray& deck)// used for shuffling the deck 
{
    srand((unsigned)time(NULL));
    Card swapper;
    for (int y = 0; y < 52; y++) {
        int randNum = rand() % 52;
        swapper = deck.cards_new[y];
        deck.cards_new[y] = deck.cards_new[randNum];
        deck.cards_new[randNum] = swapper;
    }

}



int blackjack(CardArray& deck)
{

    CardArray dealer;
    CardArray hand;
    string hit;
    dealer.max_used = 12;
    hand.max_used = 12;
    dealer.cards_new = new Card[12];
    hand.cards_new = new Card[12];


    cout << "Deal first card" << endl;
    cout << "---------------" << endl;

    cout << "+Player+: ";
    deal(deck, hand);
    printHands(hand);
    cout << "" << endl;
    cout << "" << endl;

    cout << "*Dealer*: ";
    deal(deck, dealer);
    printHands(dealer); // issue for giving so much space
    cout << " " << endl;
    cout << " " << endl;

    if (score(dealer) == 21) {
        cout << "Dealer wins!" << endl;
    }
    else if (score(hand) == 21) {
        cout << "Player wins!" << endl;
    }
    else if (score(dealer) == score(hand) && score(hand) == 21) {
        cout << "Game is tied";
    }

    cout << "Deal second card" << endl;
    cout << "----------------" << endl;

    cout << "+Player+: ";
    deal(deck, hand);
    printHands(hand);
    cout << "" << endl;
    cout << "" << endl;

    cout << "*Dealer*: ";
    deal(deck, dealer);
    cout << dealer.cards_new[0].descript;
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
            printHands(hand);
        }
        else {
            cout << "+Player+: ";
            printHands(hand);
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
    printHands(dealer);
    cout << " " << endl;

    //to figure out who wins the game by comparng the scores

    if (score(dealer) == 21) {
        cout << "Blackjack! Dealer Win" << endl;
        return -1;
    }
    else if (score(hand) == 21) {
        cout << "BlackJack! You Win" << endl;
        return 1;
    }
    else if (score(dealer) == score(hand) && score(hand) == 21) {
        cout << "Game is tied";
        return 0;
    }


    else if (score(hand) > 21) {
        cout << "You busted, Dealer Win" << endl;
        return -1;
    }
    else if (score(dealer) > 21) {
        cout << "Dealer busted, You Win" << endl;
        return 1;

    }

    else if (score(dealer) > score(hand)) {
        cout << "Dealer Win" << endl;
        return -1;
    }
    else {
        cout << "You Win" << endl;
        return 1;
    }



    delete[] dealer.cards_new;
    delete[] hand.cards_new;

    return 0;
}

//another print function for the deck to give to the dealer and player to not interfere with printDeck 
void printHands(const CardArray& hands) {


    for (int y = 0; y < hands.max_used; y++) {
        cout << hands.cards_new[y].descript << " ";


    }
}

void deal(CardArray& deck, CardArray& hand) // function used for drawing cards to the dealer/ user
{

    if (hand.current_cards <= 12) { //to draw cards and subtracts one card from the deck
        hand.cards_new[hand.current_cards] = deck.cards_new[deck.current_cards - 1];
        hand.current_cards++;
        deck.current_cards--;

    }


}

int score(CardArray& hand)
{

    int score = 0;

    for (int x = 0; x < hand.current_cards; x++) { //depending on how many cards you have in your hand, itll sum up the socre
        score += hand.cards_new[x].value;
    }
    return score;
}

// where the game is being played
int playGames(CardArray& deck) {
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
        }
        else if (current == 0) {
            draws++;
        }
        else {
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




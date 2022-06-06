#include "CardArray.h"

#include <iostream>
#include <sstream>

void game_loop(CardArray& game_deck);
int blackjack(CardArray& game_deck);
void deal(CardArray& game_deck, CardArray& player_deck);
void display_deal_first_card(const CardArray& dealer, const CardArray& player);
void display_deal_second_card(const CardArray& dealer, const CardArray& player);
void deal_loop(CardArray& game_deck, CardArray& dealer, CardArray& player);

int game_result(const CardArray& dealer, const CardArray& player);

int main() {
    CardArray game_deck;

    game_deck.populate();
    //std::cout << game_deck << std::endl;

    //std::cout << "shuffled" << std::endl;

    game_deck.shuffle();
    //std::cout << game_deck << std::endl;

    std::cout << "***BLACKJACK***" << std::endl;
    std::cout << "---------------\n" << std::endl;
    game_loop(game_deck);

    return 0;
}

void game_loop(CardArray& game_deck) {
    int wins = 0;
    int draws = 0;
    int losses = 0;
    int total = 0;

    std::string play;
    while (play != "n") {
        int result = blackjack(game_deck);

        if (result == -1) {
            losses++;
        } else if (result == 0) {
            draws++;
        } else {
            wins++;
        }

        total++;

        std::cout << "Do you want to play another hand (y to play)?: ";
        std::cin >> play;
        std::cout << "\n--------------------------------------------------\n" << std::endl;

        if (play != "n") {
            game_deck.shuffle();
            game_deck.curr_size = 52;
        }
    }

    std::cout << "Thanks for playing, you played " << total << " games and your record was: " << std::endl;
    std::cout << "wins: " << wins << std::endl;
    std::cout << "losses: " << losses << std::endl;
    std::cout << "draws: " << draws << std::endl;
}

int blackjack(CardArray& game_deck) {
    CardArray player;
    CardArray dealer;

    player.max_size = CardArray::MAX_PER_HAND;
    dealer.max_size = CardArray::MAX_PER_HAND;
    player.cards = new Card[player.max_size];
    dealer.cards = new Card[dealer.max_size];

    for (int i = 0; i < 2; i++) {
        deal(game_deck, dealer);
        deal(game_deck, player);
    }

    display_deal_first_card(dealer, player);
    std::cout << std::endl;
    display_deal_second_card(dealer, player);

    deal_loop(game_deck, dealer, player);

    return game_result(dealer, player);
}

void deal(CardArray& game_deck, CardArray& player_deck) {
    if (player_deck.curr_size <= player_deck.max_size) {
        // set player cards by taking from game_deck
        // decrementing game_deck.curr_size ensures we do not repeat cards.
        player_deck.cards[player_deck.curr_size++] = game_deck.cards[--game_deck.curr_size];
    }
}

void display_deal_first_card(const CardArray& dealer, const CardArray& player) {
    std::cout << "Deal first card" << std::endl;
    std::cout << "---------------" << std::endl;
    std::cout << "+Player+:  " << player.cards[0].description << std::endl;
    std::cout << "*Dealer*:  " << dealer.cards[0].description << std::endl;
}

void display_deal_second_card(const CardArray& dealer, const CardArray& player) {
    std::cout << "Deal second card" << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << "+Player+:  " << player.get_hand() << std::endl;
    std::cout << "*Dealer*:  " << dealer.cards[0].description << " ??" << std::endl;
}

void deal_loop(CardArray& game_deck, CardArray& dealer, CardArray& player) {
    // try to make player and dealer not bust by changing aces to 1
    if (player.score() > 21) {
        player.optimize();
    }
    if (dealer.score() > 21) {
        dealer.optimize();
    }

    if (player.score() <= 21) {
        std::cout << "\nDealing to Player" << std::endl;
        std::cout << "-----------------" << std::endl;
    }
    std::string hit;
    // dealer could be overlimit but player doesn't know that
    while (hit != "s" && player.score() <= 21) {
        player.advice();
        std::cout << "\nEnter h to hit or s to stand: ";
        std::cin >> hit;

        if (hit == "h") {
            deal(game_deck, player);
        }
        std::cout << "+Player+:  " << player.get_hand() << std::endl;
        if (player.score() > 21) {
            player.optimize();
        }
    }

    // dealer will only draw if we have not busted
    if (player.score() <= 21) {
        while (dealer.score() <= 17) {
            deal(game_deck, dealer);
            if (dealer.score() > 21) {
                dealer.optimize();
            }
        }
    }
    std::cout << "*Dealer*:  " << dealer.get_hand() << std::endl;
}

int game_result(const CardArray& dealer, const CardArray& player) {
    std::cout << std::endl;
    if (dealer.score() == 21) {
        std::cout << "Blackjack! Dealer Wins." << std::endl;
        return -1;
    } else if (player.score() == 21) {
        std::cout << "BlackJack! You Win!" << std::endl;
        return 1;
    } else if (player.score() > 21) {
        std::cout << "You busted, Dealer Wins." << std::endl;
        return -1;
    } else if (dealer.score() > 21) {
        std::cout << "Dealer busted, You Win!" << std::endl;
        return 1;
    } else if (dealer.score() == player.score()) {
        std::cout << "Game is tied." << std::endl;
        return 0;
    } else if (dealer.score() > player.score()) {
        std::cout << "Dealer Win!" << std::endl;
        return -1;
    } else {
        std::cout << "You Win!" << std::endl;
        return 1;
    }
}
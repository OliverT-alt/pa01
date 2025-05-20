// Feb 14: This file should implement the game using a custom implementation of a BST (that is based on your implementation from lab02)
#include <iostream>
#include <fstream>
#include <string>
#include "card_list.h"
//Do not include set in this file

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0]
                  << " alice_cards.txt bob_cards.txt\n";
        return 1;
    }
    std::ifstream inA(argv[1]), inB(argv[2]);
    if (!inA.is_open() || !inB.is_open()) {
        std::cerr << "Error opening input files\n";
        return 1;
    }

    custom_bst::BST alice, bob;
    std::string rankStr, suitStr;

    // Read Alice
    while (inA >> rankStr >> suitStr) {
        int rank = (rankStr=="Jack")  ? 11 :
                   (rankStr=="Queen") ? 12 :
                   (rankStr=="King")  ? 13 :
                   (rankStr=="Ace")   ? 14 :
                                        std::stoi(rankStr);
        Suit suit = (suitStr=="Clubs")    ? CLUBS    :
                    (suitStr=="Diamonds") ? DIAMONDS :
                    (suitStr=="Hearts")   ? HEARTS   :
                                            SPADES;
        alice.insert(Card(rank, suit));
    }
    // Read Bob
    while (inB >> rankStr >> suitStr) {
        int rank = (rankStr=="Jack")  ? 11 :
                   (rankStr=="Queen") ? 12 :
                   (rankStr=="King")  ? 13 :
                   (rankStr=="Ace")   ? 14 :
                                        std::stoi(rankStr);
        Suit suit = (suitStr=="Clubs")    ? CLUBS    :
                    (suitStr=="Diamonds") ? DIAMONDS :
                    (suitStr=="Hearts")   ? HEARTS   :
                                            SPADES;
        bob.insert(Card(rank, suit));
    }

    custom_bst::playGame(alice, bob);
    return 0;
}

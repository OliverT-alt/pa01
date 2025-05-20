// Feb 14: This file should implement the game using the std::set container class
// Do not include card_list.h in this file
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "card.h"

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

    set_bst::BST alice, bob;
    char suitCh;
    std::string rankStr;

    // Read Alice:
    while (inA >> suitCh >> rankStr) {
    int rank;
    
    if      (rankStr == "a" || rankStr == "A") rank = 14;
    else if (rankStr == "j" || rankStr == "J") rank = 11;
    else if (rankStr == "q" || rankStr == "Q") rank = 12;
    else if (rankStr == "k" || rankStr == "K") rank = 13;
    else                                       rank = std::stoi(rankStr);

    Suit suit;
    switch (std::tolower(suitCh)) {
      case 'c': suit = CLUBS;    break;
      case 'd': suit = DIAMONDS; break;
      case 'h': suit = HEARTS;   break;
      case 's': suit = SPADES;   break;
      default:
        std::cerr << "Invalid suit: " << suitCh << "\n";
        continue;
    }

    alice.insert(Card(rank, suit));
   }
    // Read bob:
    while (inB >> suitCh >> rankStr) {
    int rank;
    if      (rankStr == "a" || rankStr == "A") rank = 14;
    else if (rankStr == "j" || rankStr == "J") rank = 11;
    else if (rankStr == "q" || rankStr == "Q") rank = 12;
    else if (rankStr == "k" || rankStr == "K") rank = 13;
    else                                       rank = std::stoi(rankStr);

    Suit suit;
    switch (std::tolower(suitCh)) {
      case 'c': suit = CLUBS;    break;
      case 'd': suit = DIAMONDS; break;
      case 'h': suit = HEARTS;   break;
      case 's': suit = SPADES;   break;
      default:
        std::cerr << "Invalid suit: " << suitCh << "\n";
        continue;
    }

    bob.insert(Card(rank, suit));
}
    set_bst::playGame(alice, bob);
    return 0;
}

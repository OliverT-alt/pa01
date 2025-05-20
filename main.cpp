// Feb 14: This file should implement the game using a custom implementation of a BST (that is based on your implementation from lab02)
#include <iostream>
#include <fstream>
#include <string>
#include "card_list.h" 

using namespace std;     

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0]
             << " alice_cards.txt bob_cards.txt\n";
        return 1;
    }

    // Open input files
    ifstream inA(argv[1]), inB(argv[2]);
    if (!inA.is_open() || !inB.is_open()) {
        cerr << "Error opening input files\n";
        return 1;
    }

    // Populate the two BSTs
    custom_bst::BST alice, bob;
    char suitCh;
    string rankStr;

    // Read Alice
    while (inA >> suitCh >> rankStr) {
        int rank;
        if      (rankStr == "a" || rankStr == "A") rank = 14;
        else if (rankStr == "j" || rankStr == "J") rank = 11;
        else if (rankStr == "q" || rankStr == "Q") rank = 12;
        else if (rankStr == "k" || rankStr == "K") rank = 13;
        else                                       rank = stoi(rankStr);

        Suit suit;
        switch (tolower(suitCh)) {
          case 'c': suit = CLUBS;    break;
          case 'd': suit = DIAMONDS; break;
          case 'h': suit = HEARTS;   break;
          case 's': suit = SPADES;   break;
          default:
            cerr << "Invalid suit: " << suitCh << "\n";
            continue;
        }
        alice.insert(Card(rank, suit));
    }

    // Read Bob
    while (inB >> suitCh >> rankStr) {
        int rank;
        if      (rankStr == "a" || rankStr == "A") rank = 14;
        else if (rankStr == "j" || rankStr == "J") rank = 11;
        else if (rankStr == "q" || rankStr == "Q") rank = 12;
        else if (rankStr == "k" || rankStr == "K") rank = 13;
        else                                       rank = stoi(rankStr);

        Suit suit;
        switch (tolower(suitCh)) {
          case 'c': suit = CLUBS;    break;
          case 'd': suit = DIAMONDS; break;
          case 'h': suit = HEARTS;   break;
          case 's': suit = SPADES;   break;
          default:
            cerr << "Invalid suit: " << suitCh << "\n";
            continue;
        }
        bob.insert(Card(rank, suit));
    }


    custom_bst::playGame(alice, bob);
    return 0;
}

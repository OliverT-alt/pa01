// card.cpp
// Author: Your name
// Implementation of the classes defined in card.h

#include "card.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Card::Card(int r, Suit s) : rank(r), suit(s) {
    if (r < 2 || r > 14) throw std::invalid_argument("Invalid rank");
}

std::string Card::toString() const {
    std::string rankStr = (rank >= 2 && rank <= 10) ? std::to_string(rank) :
                          rank == 11 ? "J" : rank == 12 ? "Q" : rank == 13 ? "K" : "A";
    std::string suitStr = suit == CLUBS ? "C" : suit == DIAMONDS ? "D" :
                          suit == HEARTS ? "H" : "S";
    return rankStr + suitStr;
}

bool Card::operator<(const Card& other) const {
    if (rank != other.rank) return rank < other.rank;
    return suit < other.suit;
}

bool Card::operator==(const Card& other) const {
    return rank == other.rank && suit == other.suit;
}

namespace set_bst {
    
BST::BST() {}

void BST::insert(const Card& c) {
    cards.insert(c);
}

void BST::remove(int rank) {
    for (auto it = cards.begin(); it != cards.end(); ++it) {
        if (it->rank == rank) {
            cards.erase(it);
            return;
        }
    }
    throw std::runtime_error("Rank not found");
}

bool BST::contains(int rank) const {
    for (const auto& card : cards) {
        if (card.rank == rank) return true;
    }
    return false;
}

void BST::printDeck() const {
    for (const auto& card : cards) {
        std::cout << card.toString() << " ";
    }
    std::cout << std::endl;
}

Card BST::getSuccessorNode(const Card& c) const {
    auto it = cards.find(c);
    if (it == cards.end() || ++it == cards.end()) {
        throw std::runtime_error("No successor");
    }
    return *it;
}

Card BST::getPredecessorNode(const Card& c) const {
    auto it = cards.find(c);
    if (it == cards.begin() || it == cards.end()) {
        throw std::runtime_error("No predecessor");
    }
    return *(--it);
}


// (be sure to have `using namespace std;` near the top)

void playGame(BST& alice, BST& bob) {
    // 1) Flatten each BST into a sorted vector
    vector<Card> aCards, bCards;
    for (auto it = alice.begin(); it != alice.end(); ++it) 
        aCards.push_back(*it);
    for (auto it = bob.begin(); it != bob.end(); ++it) 
        bCards.push_back(*it);

    // 2) Game loop: Alice picks smallest‐first, then Bob largest‐first
    while (true) {
        // --- Alice’s turn (smallest → largest) ---
        int ai = 0;
        while (ai < (int)aCards.size() && 
               !binary_search(bCards.begin(), bCards.end(), aCards[ai])) {
            ++ai;
        }
        if (ai >= (int)aCards.size()) break;   // no match → end game

        Card matchA = aCards[ai];
        // Print pick
        char sc = (matchA.suit==CLUBS?'c'
                 : matchA.suit==DIAMONDS?'d'
                 : matchA.suit==HEARTS?'h':'s');
        string rs = (matchA.rank==14?"a"
                   : matchA.rank==13?"k"
                   : matchA.rank==12?"q"
                   : matchA.rank==11?"j"
                   : to_string(matchA.rank));
        cout << "Alice picked matching card " << sc << " " << rs << "\n";

        // Remove from BSTs & vectors
        alice.remove(matchA.rank);
        bob.remove(matchA.rank);
        aCards.erase(aCards.begin() + ai);
        auto bi = int(lower_bound(bCards.begin(), bCards.end(), matchA) - bCards.begin());
        bCards.erase(bCards.begin() + bi);

        // --- Bob’s turn (largest → smallest) ---
        int bj = (int)bCards.size() - 1;
        while (bj >= 0 && 
               !binary_search(aCards.begin(), aCards.end(), bCards[bj])) {
            --bj;
        }
        if (bj < 0) break;  // no match → end game

        Card matchB = bCards[bj];
        sc = (matchB.suit==CLUBS?'c'
           : matchB.suit==DIAMONDS?'d'
           : matchB.suit==HEARTS?'h':'s');
        rs = (matchB.rank==14?"a"
           : matchB.rank==13?"k"
           : matchB.rank==12?"q"
           : matchB.rank==11?"j"
           : to_string(matchB.rank));
        cout << "Bob picked matching card " << sc << " " << rs << "\n";

        alice.remove(matchB.rank);
        bob.remove(matchB.rank);
        bCards.erase(bCards.begin() + bj);
        auto aj = int(lower_bound(aCards.begin(), aCards.end(), matchB) - aCards.begin());
        aCards.erase(aCards.begin() + aj);
    }

    // 3) One blank line, then final hands
    cout << "\n";
    cout << "Alice's cards:\n";
    for (auto &c : aCards) {
        char sc = (c.suit==CLUBS?'c'
                 : c.suit==DIAMONDS?'d'
                 : c.suit==HEARTS?'h':'s');
        string rs = (c.rank==14?"a"
                  : c.rank==13?"k"
                  : c.rank==12?"q"
                  : c.rank==11?"j"
                  : to_string(c.rank));
        cout << sc << " " << rs << "\n";
    }
    cout << "Bob's cards:\n";
    for (auto &c : bCards) {
        char sc = (c.suit==CLUBS?'c'
                 : c.suit==DIAMONDS?'d'
                 : c.suit==HEARTS?'h':'s');
        string rs = (c.rank==14?"a"
                  : c.rank==13?"k"
                  : c.rank==12?"q"
                  : c.rank==11?"j"
                  : to_string(c.rank));
        cout << sc << " " << rs << "\n";
    }
}

}
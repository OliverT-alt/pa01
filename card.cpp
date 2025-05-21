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
    if (suit != other.suit)
        return suit < other.suit;

    auto thisOrder  = (rank == 14 ? 1 : rank);
    auto otherOrder = (other.rank == 14 ? 1 : other.rank);
    return thisOrder < otherOrder;
}


bool Card::operator==(const Card& other) const {
    return rank == other.rank && suit == other.suit;
}

namespace set_bst {
    
BST::BST() {}

void BST::insert(const Card& c) {
    cards.insert(c);
}

void BST::remove(const Card& c) {
    auto it = cards.find(c);
    if (it == cards.end()) 
        throw runtime_error("Card not found");
    cards.erase(it);
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

bool BST::contains(const Card& c) const {
    // uses Card::operator< to locate exact suit+rank
    return cards.find(c) != cards.end();
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


void playGame(BST& alice, BST& bob) {
    // Alice smallest matching card
    while (true) {
        auto aIt = alice.begin();
        while (aIt != alice.end() && !bob.contains(*aIt))
            ++aIt;
        if (aIt == alice.end()) break;

        Card matchA = *aIt;
        alice.remove(matchA);
        bob.remove(matchA);


        char sc = (matchA.suit==CLUBS? 'c'
                 : matchA.suit==DIAMONDS? 'd'
                 : matchA.suit==HEARTS? 'h'
                 : 's');
        string rs = (matchA.rank==14? "a"
                  : matchA.rank==13? "k"
                  : matchA.rank==12? "q"
                  : matchA.rank==11? "j"
                  : to_string(matchA.rank));
        cout << "Alice picked matching card " << sc << " " << rs << "\n";

        //Bob picks smallest matching card
        auto bIt = bob.rbegin();
        while (bIt != bob.rend() && !alice.contains(*aIt))
            --bIt;
        if (bIt == bob.rend()) break;

        Card matchB = *bIt;
        alice.remove(matchA);
        bob.remove(matchA);


        sc = (matchB.suit==CLUBS? 'c'
           : matchB.suit==DIAMONDS? 'd'
           : matchB.suit==HEARTS? 'h'
           : 's');
        rs = (matchB.rank==14? "a"
           : matchB.rank==13? "k"
           : matchB.rank==12? "q"
           : matchB.rank==11? "j"
           : to_string(matchB.rank));
        cout << "Bob picked matching card " << sc << " " << rs << "\n";
    }

    cout << "\n";

    // final hands
    cout << "Alice's cards:\n";
    for (auto it = alice.begin(); it != alice.end(); ++it) {
        char sc = (it->suit==CLUBS? 'c'
                 : it->suit==DIAMONDS? 'd'
                 : it->suit==HEARTS? 'h'
                 : 's');
        string rs = (it->rank==14? "a"
                  : it->rank==13? "k"
                  : it->rank==12? "q"
                  : it->rank==11? "j"
                  : to_string(it->rank));
        cout << sc << " " << rs << "\n";
    }
    cout << "\n";
    cout << "Bob's cards:\n";
    for (auto it = bob.begin(); it != bob.end(); ++it) {
        char sc = (it->suit==CLUBS? 'c'
                 : it->suit==DIAMONDS? 'd'
                 : it->suit==HEARTS? 'h'
                 : 's');
        string rs = (it->rank==14? "a"
                  : it->rank==13? "k"
                  : it->rank==12? "q"
                  : it->rank==11? "j"
                  : to_string(it->rank));
        cout << sc << " " << rs << "\n";
    }
}
}
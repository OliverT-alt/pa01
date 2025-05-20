// card.cpp
// Author: Your name
// Implementation of the classes defined in card.h

#include "card.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <string>

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

void playGame(BST& alice, BST& bob) {
    int maxRounds;
    std::string aliceFile, bobFile;
    std::cin >> maxRounds >> aliceFile >> bobFile;

    // read alics cards
    std::ifstream aliceIn(aliceFile);
    if (!aliceIn.is_open()) {
        std::cerr << "Error opening " << aliceFile << std::endl;
        return;
    }
    std::string rankStr, suitStr;
    while (aliceIn >> rankStr >> suitStr) {
        int rank =  
            (rankStr == "Jack")  ? 11 :
            (rankStr == "Queen") ? 12 :
            (rankStr == "King")  ? 13 :
            (rankStr == "Ace")   ? 14 :
                                  std::stoi(rankStr);
        Suit suit =
            (suitStr == "Clubs")    ? CLUBS    :
            (suitStr == "Diamonds") ? DIAMONDS :
            (suitStr == "Hearts")   ? HEARTS   :
                                     SPADES;
        alice.insert(Card(rank, suit));
    }
    aliceIn.close();

    // read bob cards
    std::ifstream bobIn(bobFile);
    if (!bobIn.is_open()) {
        std::cerr << "Error opening " << bobFile << std::endl;
        return;
    }
    while (bobIn >> rankStr >> suitStr) {
        int rank =  
            (rankStr == "Jack")  ? 11 :
            (rankStr == "Queen") ? 12 :
            (rankStr == "King")  ? 13 :
            (rankStr == "Ace")   ? 14 :
                                  std::stoi(rankStr);
        Suit suit =
            (suitStr == "Clubs")    ? CLUBS    :
            (suitStr == "Diamonds") ? DIAMONDS :
            (suitStr == "Hearts")   ? HEARTS   :
                                     SPADES;
        bob.insert(Card(rank, suit));
    }
    bobIn.close();

    // play rounds
    for (int round = 1; round <= maxRounds; ++round) {
        // Stop if no common cards remain
        bool aliceHasAny = false, bobHasAny = false;
        for (int r = 2; r <= 14; ++r) {
            if (alice.contains(r)) aliceHasAny = true;
            if (bob.contains(r))   bobHasAny   = true;
        }
        if (!aliceHasAny || !bobHasAny) break;

        // Alice's turn smallest to largest
        auto aIt = alice.begin();
        while (aIt != alice.end() && !bob.contains(aIt->rank)) ++aIt;
        if (aIt == alice.end()) break;
        Card matchA = *aIt;
        alice.remove(matchA.rank);
        bob.remove(matchA.rank);
        std::cout << "Alice picked matching card " 
                  << matchA.toString() << "\n";  

        // Bob's turn largest to smallest
        auto bIt = bob.rbegin();
        while (bIt != bob.rend() && !alice.contains(bIt->rank)) --bIt;
        if (bIt == bob.rend()) break;
        Card matchB = *bIt;
        alice.remove(matchB.rank);
        bob.remove(matchB.rank);
        std::cout << "Bob picked matching card " 
                  << matchB.toString() << "\n";
    }

    //final hands
    std::cout << "\n"; 

    std::cout << "Alice's cards:\n";
    for (auto it = alice.begin(); it != alice.end(); ++it) {
        std::cout << it->toString() << "\n";
    }

    std::cout << "Bob's cards:\n";
    for (auto it = bob.begin(); it != bob.end(); ++it) {
        std::cout << it->toString() << "\n";
    }
}

}
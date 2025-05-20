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

    std::ifstream aliceIn(aliceFile);
    if (!aliceIn.is_open()) {
        std::cerr << "Error opening " << aliceFile << std::endl;
        return;
    }
    std::string rankStr, suitStr;
    while (aliceIn >> rankStr >> suitStr) {
        int rank;
        if (rankStr == "Jack") rank = 11;
        else if (rankStr == "Queen") rank = 12;
        else if (rankStr == "King") rank = 13;
        else if (rankStr == "Ace") rank = 14;
        else rank = std::stoi(rankStr);
        
        Suit suit;
        if (suitStr == "Clubs") suit = CLUBS;
        else if (suitStr == "Diamonds") suit = DIAMONDS;
        else if (suitStr == "Hearts") suit = HEARTS;
        else suit = SPADES;

        alice.insert(Card(rank, suit));
    }
    aliceIn.close();

    std::ifstream bobIn(bobFile);
    if (!bobIn.is_open()) {
        std::cerr << "Error opening " << bobFile << std::endl;
        return;
    }
    while (bobIn >> rankStr >> suitStr) {
        int rank;
        if (rankStr == "Jack") rank = 11;
        else if (rankStr == "Queen") rank = 12;
        else if (rankStr == "King") rank = 13;
        else if (rankStr == "Ace") rank = 14;
        else rank = std::stoi(rankStr);
        
        Suit suit;
        if (suitStr == "Clubs") suit = CLUBS;
        else if (suitStr == "Diamonds") suit = DIAMONDS;
        else if (suitStr == "Hearts") suit = HEARTS;
        else suit = SPADES;

        bob.insert(Card(rank, suit));
    }
    bobIn.close();

    int aliceScore = 0, bobScore = 0;
    for (int round = 1; round <= maxRounds; ++round) {
        if (!alice.contains(2) && !alice.contains(3) && !alice.contains(4) && !alice.contains(5) &&
            !alice.contains(6) && !alice.contains(7) && !alice.contains(8) && !alice.contains(9) &&
            !alice.contains(10) && !alice.contains(11) && !alice.contains(12) && !alice.contains(13) &&
            !alice.contains(14)) break;
        if (!bob.contains(2) && !bob.contains(3) && !bob.contains(4) && !bob.contains(5) &&
            !bob.contains(6) && !bob.contains(7) && !bob.contains(8) && !bob.contains(9) &&
            !bob.contains(10) && !bob.contains(11) && !bob.contains(12) && !bob.contains(13) &&
            !bob.contains(14)) break;

        auto aliceIt = alice.begin();
        auto bobIt = bob.begin();
        if (aliceIt == alice.end() || bobIt == bob.end()) break;

        Card aliceCard = *aliceIt;
        Card bobCard = *bobIt;

        alice.remove(aliceCard.rank);
        bob.remove(bobCard.rank);

        std::cout << "Alice plays " << aliceCard.toString() << ", Bob plays " << bobCard.toString() << ", ";
        if (aliceCard < bobCard) {
            bobScore++;
            std::cout << "Score: Alice " << aliceScore << ", Bob " << bobScore << std::endl;
        } else if (bobCard < aliceCard) {
            aliceScore++;
            std::cout << "Score: Alice " << aliceScore << ", Bob " << bobScore << std::endl;
        } else {
            std::cout << "Score: Alice " << aliceScore << ", Bob " << bobScore << std::endl;
        }
    }

    bool aliceEmpty = true, bobEmpty = true;
    for (int r = 2; r <= 14; ++r) {
        if (alice.contains(r)) aliceEmpty = false;
        if (bob.contains(r)) bobEmpty = false;
    }

    if (!aliceEmpty && bobEmpty) {
        std::cout << "Alice wins!" << std::endl;
    } else if (!bobEmpty && aliceEmpty) {
        std::cout << "Bob wins!" << std::endl;
    } else if (aliceScore > bobScore) {
        std::cout << "Alice wins!" << std::endl;
    } else if (bobScore > aliceScore) {
        std::cout << "Bob wins!" << std::endl;
    } else {
        std::cout << "Tie!" << std::endl;
    }
}
}
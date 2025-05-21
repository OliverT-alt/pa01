// card.h
// Author: Your name
// All class declarations related to defining a single card go here

#ifndef CARD_H
#define CARD_H

#include <string>
#include <set>

enum Suit { CLUBS, DIAMONDS, SPADES, HEARTS };

class Card {
public:
    int rank; 
    Suit suit;
    Card(int r = 2, Suit s = CLUBS);
    std::string toString() const;
    bool operator<(const Card& other) const;
    bool operator==(const Card& other) const;
};

namespace set_bst {
class BST {
private:
    std::set<Card> cards;
public:
    BST();
    void insert(const Card& c);
    void remove(int rank);
    void remove(const Card& c); 
    bool contains(int rank) const;
    bool contains(const Card& c) const;
    void printDeck() const;
    Card getSuccessorNode(const Card& c) const;
    Card getPredecessorNode(const Card& c) const;

    // Iterator
    class Iterator {
    private:
        std::set<Card>::iterator it;
        const std::set<Card>* set;
    public:
        Iterator(std::set<Card>::iterator iter, const std::set<Card>* s) : it(iter), set(s) {}
        const Card& operator*() const { return *it; }
        const Card* operator->() const { return &(*it); }
        Iterator& operator++() { ++it; return *this; }
        Iterator& operator--() {
           if (it == set->begin()) {
                it = set->end();
            } else {
                --it;
            }
            return *this;
        }
        bool operator==(const Iterator& other) const { return it == other.it; }
        bool operator!=(const Iterator& other) const { return it != other.it; }
    };

    Iterator begin() const { return Iterator(cards.begin(), &cards); }
    Iterator end() const { return Iterator(cards.end(), &cards); }
    Iterator rbegin() const {
        auto i = cards.end();
        if (i != cards.begin())  --i;
        return Iterator(i, &cards);
    }
    Iterator rend() const {
        return Iterator(cards.end(), &cards);
    }
};

void playGame(BST& alice, BST& bob);
}

#endif
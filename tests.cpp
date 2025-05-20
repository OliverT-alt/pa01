#include "card.h"
#include "card_list.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>

void testCard() {
    std::cout << "Testing Card class...\n";
    Card c1(5, CLUBS), c2(5, DIAMONDS), c3(6, CLUBS);
    
    assert(c1.toString() == "5C");
    assert(c2.toString() == "5D");
    assert(c3.toString() == "6C");

    assert(c1 < c2);
    assert(c2 < c3);
    assert(!(c1 == c2));
    assert(Card(5, CLUBS) == Card(5, CLUBS));

    try {
        Card invalid(1, CLUBS);
        assert(false && "Should throw exception for invalid rank");
    } catch (const std::invalid_argument&) {}

    std::cout << "Card tests passed.\n";
}

void testCustomBST() {
    std::cout << "Testing custom BST (card_list.h)...\n";
    custom_bst::BST deck;  // Use custom_bst::BST from card_list.h

    assert(!deck.contains(5));
    try {
        deck.remove(5);
        assert(false && "Should throw exception for empty BST");
    } catch (const std::runtime_error&) {}

    deck.insert(Card(5, CLUBS));
    deck.insert(Card(2, SPADES));
    deck.insert(Card(5, DIAMONDS));
    assert(deck.contains(5));
    assert(deck.contains(2));
    assert(!deck.contains(3));

    std::ostringstream output;
    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());
    deck.printDeck();
    std::cout.rdbuf(coutBuffer);
    assert(output.str() == "2S 5C 5D \n");

    auto it = deck.begin();
    assert(it != deck.end());
    assert(it->toString() == "2S");
    ++it;
    assert(it->toString() == "5C");
    ++it;
    assert(it->toString() == "5D");
    ++it;
    assert(it == deck.end());

    it = deck.rbegin();
    assert(it != deck.rend());
    assert(it->toString() == "5D");
    --it;
    assert(it->toString() == "5C");
    --it;
    assert(it->toString() == "2S");
    --it;
    assert(it == deck.rend());

    Card c1(2, SPADES), c2(5, CLUBS), c3(5, DIAMONDS);
    assert(deck.getSuccessorNode(c1).toString() == "5C");
    assert(deck.getSuccessorNode(c2).toString() == "5D");
    assert(deck.getPredecessorNode(c3).toString() == "5C");
    assert(deck.getPredecessorNode(c2).toString() == "2S");

    deck.remove(5);
    assert(deck.contains(5));
    output.str("");
    std::cout.rdbuf(output.rdbuf());
    deck.printDeck();
    std::cout.rdbuf(coutBuffer);
    assert(output.str() == "2S 5D \n");

    deck.remove(5);
    assert(!deck.contains(5));
    deck.remove(2);
    assert(!deck.contains(2));
    assert(!deck.contains(5));

    std::cout << "Custom BST tests passed.\n";
}

void testSetBST() {
    std::cout << "Testing std::set BST (card.h)...\n";
    set_bst::BST deck;  // Use set_bst::BST from card.h

    assert(!deck.contains(5));
    try {
        deck.remove(5);
        assert(false && "Should throw exception for empty BST");
    } catch (const std::runtime_error&) {}

    deck.insert(Card(5, CLUBS));
    deck.insert(Card(2, SPADES));
    deck.insert(Card(5, DIAMONDS));
    assert(deck.contains(5));
    assert(deck.contains(2));
    assert(!deck.contains(3));

    std::ostringstream output;
    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());
    deck.printDeck();
    std::cout.rdbuf(coutBuffer);
    assert(output.str() == "2S 5C 5D \n");

    auto it = deck.begin();
    assert(it != deck.end());
    assert(it->toString() == "2S");
    ++it;
    assert(it->toString() == "5C");
    ++it;
    assert(it->toString() == "5D");
    ++it;
    assert(it == deck.end());

    it = deck.rbegin();
    assert(it != deck.rend());
    assert(it->toString() == "5D");
    --it;
    assert(it->toString() == "5C");
    --it;
    assert(it->toString() == "2S");
    --it;
    assert(it == deck.rend());

    Card c1(2, SPADES), c2(5, CLUBS), c3(5, DIAMONDS);
    assert(deck.getSuccessorNode(c1).toString() == "5C");
    assert(deck.getSuccessorNode(c2).toString() == "5D");
    assert(deck.getPredecessorNode(c3).toString() == "5C");
    assert(deck.getPredecessorNode(c2).toString() == "2S");

    deck.remove(5);
    assert(deck.contains(5));
    output.str("");
    std::cout.rdbuf(output.rdbuf());
    deck.printDeck();
    std::cout.rdbuf(coutBuffer);
    assert(output.str() == "2S 5D \n");

    deck.remove(5);
    assert(!deck.contains(5));
    deck.remove(2);
    assert(!deck.contains(2));
    assert(!deck.contains(5));

    std::cout << "Set BST tests passed.\n";
}

int main() {
    std::cout << "Running tests...\n";
    testCard();
    testCustomBST();
    testSetBST();
    std::cout << "All tests completed.\n";
    return 0;
}
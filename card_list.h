// card_list.h
// Author: Your name
// All class declarations related to defining a BST that represents a player's hand

#ifndef CARD_LIST_H
#define CARD_LIST_H

#include "card.h"
#include <iostream>

namespace custom_bst {
class BST {
private:
    struct Node {
        Card card;
        Node* left;
        Node* right;
        Node* parent;
        Node(const Card& c, Node* p = nullptr) : card(c), left(nullptr), right(nullptr), parent(p) {}
    };
    Node* root;
    Node* insert(Node* node, const Card& c, Node* parent);
    Node* findMin(Node* node) const;
    Node* findNode(Node* node, int rank) const;
    Node* findExact(Node* node, const Card& c) const;
    void clear(Node* node);
    void printInOrder(Node* node) const;

public:
    BST();
    ~BST();
    void insert(const Card& c);
    void remove(int rank); 
    void remove  (const Card& c);
    bool contains(int rank) const;
    bool contains(const Card& c) const;
    void printDeck() const;
    Card getSuccessorNode(const Card& c) const;
    Card getPredecessorNode(const Card& c) const;

    // Iterator class
    class Iterator {
    private:
        Node* current;
        const BST* tree;
        Node* findMin(Node* node) const;
        Node* findMax(Node* node) const;
        Node* getSuccessor(Node* node) const;
        Node* getPredecessor(Node* node) const;
    public:
        Iterator(Node* node, const BST* t) : current(node), tree(t) {}
        const Card& operator*() const { return current->card; }
        const Card* operator->() const { return &(current->card); }
        Iterator& operator++();
        Iterator& operator--();
        bool operator==(const Iterator& other) const { return current == other.current; }
        bool operator!=(const Iterator& other) const { return current != other.current; }
    };

    Iterator begin() const;
    Iterator end() const;
    Iterator rbegin() const;
    Iterator rend() const;
};

void playGame(BST& alice, BST& bob);
}

#endif
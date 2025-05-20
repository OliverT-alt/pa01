#include "card_list.h"
#include <stdexcept>
#include <fstream>
#include <string>

using namespace std;

namespace custom_bst {
    BST::BST() : root(nullptr) {}

    BST::~BST() {
        clear(root);
    }

    void BST::clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    BST::Node* BST::insert(Node* node, const Card& c, Node* parent) {
        if (!node) {
            return new Node(c, parent);
        }
        if (c < node->card) {
            node->left = insert(node->left, c, node);
        } else {
            node->right = insert(node->right, c, node);
        }
        return node;
    }

    void BST::insert(const Card& c) {
        root = insert(root, c, nullptr);
    }

    BST::Node* BST::findMin(Node* node) const {
        if (!node) return nullptr;
        while (node->left) node = node->left;
        return node;
    }

    BST::Node* BST::findNode(Node* node, int rank) const {
        if (!node) return nullptr;
        if (node->card.rank == rank) {
            Node* leftmost = node;
            while (leftmost->left && leftmost->left->card.rank == rank) {
                leftmost = leftmost->left;
            }
            return leftmost;
        }
        if (rank < node->card.rank) return findNode(node->left, rank);
        return findNode(node->right, rank);
    }
void BST::remove(int rank) {
    // 1) locate the exact node to kill
    Node* node = findNode(root, rank);
    if (!node) throw std::runtime_error("Rank not found");

    // 2) if it has two children, swap with its in‐order successor
    if (node->left && node->right) {
        Node* succ = findMin(node->right);
        node->card = succ->card;
       
        node = succ;
    }

    // 3) node has at most one child
    Node* child = node->left ? node->left : node->right;
    if (child) child->parent = node->parent;

    // 4) splice it out of the tree
    if (!node->parent) {
        root = child;
    } else if (node->parent->left == node) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }

    delete node;
}


    bool BST::contains(int rank) const {
        return findNode(root, rank) != nullptr;
    }

    void BST::printInOrder(Node* node) const {
        if (node) {
            printInOrder(node->left);
            std::cout << node->card.toString() << " ";
            printInOrder(node->right);
        }
    }

    void BST::printDeck() const {
        printInOrder(root);
        std::cout << std::endl;
    }

    Card BST::getSuccessorNode(const Card& c) const {
        Node* node = root;
        Node* successor = nullptr;
        while (node) {
            if (c < node->card) {
                successor = node;
                node = node->left;
            } else {
                node = node->right;
            }
        }
        if (!successor) throw std::runtime_error("No successor");
        return successor->card;
    }

    Card BST::getPredecessorNode(const Card& c) const {
        Node* node = root;
        Node* predecessor = nullptr;
        while (node) {
            if (node->card < c) {
                predecessor = node;
                node = node->right;
            } else {
                node = node->left;
            }
        }
        if (!predecessor) throw std::runtime_error("No predecessor");
        return predecessor->card;
    }

    BST::Iterator BST::begin() const {
        return Iterator(findMin(root), this);
    }

    BST::Iterator BST::end() const {
        return Iterator(nullptr, this);
    }

    BST::Iterator BST::rbegin() const {
        Node* max = root;
        while (max && max->right) max = max->right;
        return Iterator(max, this);
    }

    BST::Iterator BST::rend() const {
        return Iterator(nullptr, this);
    }

    BST::Node* BST::Iterator::findMin(Node* node) const {
        if (!node) return nullptr;
        while (node->left) node = node->left;
        return node;
    }

    BST::Node* BST::Iterator::findMax(Node* node) const {
        if (!node) return nullptr;
        while (node->right) node = node->right;
        return node;
    }

    BST::Node* BST::Iterator::getSuccessor(Node* node) const {
        if (!node) return nullptr;
        if (node->right) return findMin(node->right);
        Node* parent = node->parent;
        while (parent && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    BST::Node* BST::Iterator::getPredecessor(Node* node) const {
        if (!node) return nullptr;
        if (node->left) return findMax(node->left);
        Node* parent = node->parent;
        while (parent && node == parent->left) {
            node = parent;
            parent = parent->parent;
        }
        return parent;
    }

    BST::Iterator& BST::Iterator::operator++() {
        current = getSuccessor(current);
        return *this;
    }

    BST::Iterator& BST::Iterator::operator--() {
        current = getPredecessor(current);
        return *this;
    }


void playGame(BST& alice, BST& bob) {
    //alice picks her smallest matching card
    while (true) {
        auto aIt = alice.begin();
        while (aIt != alice.end() && !bob.contains(aIt->rank))
            ++aIt;
        if (aIt == alice.end()) 
            break;
        Card matchA = *aIt;
        alice.remove(matchA.rank);
        bob.remove(matchA.rank);
        cout << "Alice picked matching card "
             << matchA.toString() << "\n";

        //Bob picks his smallest matching card
        auto bIt = bob.begin();
        while (bIt != bob.end() && !alice.contains(bIt->rank))
            ++bIt;
        if (bIt == bob.end())
            break;
        Card matchB = *bIt;
        alice.remove(matchB.rank);
        bob.remove(matchB.rank);
        cout << "Bob picked matching card "
             << matchB.toString() << "\n";
    }
    cout << "\n";
     // print Alice's remaining cards
    cout << "Alice's cards:\n";
    for (auto it = alice.begin(); it != alice.end(); ++it)
        cout << it->toString() << "\n";

    // print Bob's remaining cards
    cout << "Bob's cards:\n";
    for (auto it = bob.begin(); it != bob.end(); ++it)
        cout << it->toString() << "\n";
}
}
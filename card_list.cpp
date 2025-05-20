#include "card_list.h"
#include <stdexcept>
#include <fstream>
#include <string>

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
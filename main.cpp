// Feb 14: This file should implement the game using a custom implementation of a BST (that is based on your implementation from lab02)
#include <iostream>
#include <fstream>
#include <string>

#include "card_list.h"
//Do not include set in this file


int main() {
    custom_bst::BST alice, bob;
    custom_bst::playGame(alice, bob);
    return 0;
}

#include <iostream>
#include <cassert>
#include "NaiveTree.h"
#include "CurevoTree.h"

int main() {
    int inputLength = 0;
    std::cin >> inputLength;

    assert(inputLength >= 0);
    NaiveTree<int> tree;
    CurevoTree<std::pair<int, int>> cTree;

    while (inputLength--){

        int tmpCinElement = 0;
        std::cin >> tmpCinElement;
        tree.Add(tmpCinElement);
    }

    tree.TraversalFunc();
    cTree.TraversalFunc();
    return 0;
}
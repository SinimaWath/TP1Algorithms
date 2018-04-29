#include <iostream>
#include <cassert>
#include "NaiveTree.h"

int main() {
    int inputLength = 0;
    std::cin >> inputLength;

    assert(inputLength >= 0);

    NaiveTree<int> tree;

    while (inputLength--){

        int tmpCinElement = 0;
        std::cin >> tmpCinElement;
        tree.Add(tmpCinElement);
    }

    MethodCout<int> method;
    tree.Traversal(method);
    return 0;
}
#include <iostream>
#include <cassert>
#include "NaiveTree.h"
#include "CurevoTree.h"

int main() {
    int inputLength = 0;
    std::cin >> inputLength;

    assert(inputLength >= 0);
    NaiveTree<int> nTree;
    CurevoTree<int> cTree;

    while (inputLength--) {

        int tmpValue = 0, tmpPrior = 0;
        std::cin >> tmpValue >> tmpPrior;
        nTree.Add(tmpValue);
        cTree.Add(std::pair<int, int>(tmpValue, tmpPrior));

    }

    std::cout << std ::abs(nTree.GetDepth() - cTree.GetDepth());
    return 0;
}
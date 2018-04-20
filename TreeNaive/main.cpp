#include <iostream>
#include "CTree.h"

using namespace std;

int main() {

    CTree<int> tree;

    tree.Add(1);
    tree.Add(0);
    tree.Add(2);
    tree.Add(3);

    return 0;
}
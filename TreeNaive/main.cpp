#include <iostream>
#include <cassert>
#include "CTree.h"

using namespace std;

int main() {

    int inputLength = 0;
    cin >> inputLength;

    assert(inputLength >= 0);

    CTree<int> tree;

    while (inputLength--){

        int tmpCinElement = 0;
        cin >> tmpCinElement;
        tree.Add(tmpCinElement);
    }

    tree.Traversal([](CTree<int>::Node* node){
        cout << node->value << "\n";
    });
    return 0;
}
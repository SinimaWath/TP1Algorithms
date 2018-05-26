#include <iostream>
#include <cassert>
#include "AVLTree.h"

using namespace std;

int main() {

    int commandCount = 0;
    std::cin >> commandCount;

    assert( commandCount >= 0 );

    AVLTree<int> tree{};

    while (commandCount--){
        int command = 0, value = 0;
        cin >> command >> value;
        switch(command){
            case 1:
                std::cout << tree.Add(value) << "\n";
                break;
            case 2:
                //std::cout << tree.Delete(value)->key << "\n";
                tree.RemoveByPos(value);
                break;
            default:
                std::cout << "No such command\n";
        }
    }
    return 0;
}
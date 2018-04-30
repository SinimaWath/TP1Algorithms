//
// Created by sinimawath on 29.04.18.
//

#ifndef CUREVOTREE_CUREVOTREE_H
#define CUREVOTREE_CUREVOTREE_H

#include <functional>
#include <iostream>
#include <queue>
#include "ITree.h"

// T is pair
template <class T, class Traversal = PreOrderTraversal, class Comparator = std::less<T>>
class CurevoTree: public ITree<T>{
public:

    CurevoTree() : root_(nullptr) {}
    ~CurevoTree();

    void Add(const T &value) override;
    bool Delete(const T &value) override;
    bool Empty() const override;
    void DeleteTree() override;
    void TraversalFunc() override;

    struct Node;
private:
    Comparator comp_;
    Traversal traversal_;

    Node* root_;

    void Split(Node* currentNode, const T& value, Node*& left, Node*& right);
};

template <class T, class Traversal, class Comparator>
struct CurevoTree<T, Traversal, Comparator>::Node{
    T value;
    Node* leftChild;
    Node* rightChild;

    Node(const T& valueOther) : value(valueOther),
                                                   leftChild(nullptr), rightChild(nullptr){}
};

template<class T, class Traversal, class Comparator>
void CurevoTree<T, Traversal, Comparator>::Add(const T &value) {
    if (root_ == nullptr){
        root_ = new Node(value);
    } else {
        Node* tmpSearch = root_;
        Node* parent = nullptr;
        bool isLeftChild = true;

        while (tmpSearch->value.second >= value.second && tmpSearch != nullptr){
            if (comp_(value, tmpSearch->value.first)) {
                tmpSearch = tmpSearch->leftChild;
                isLeftChild = true;
            } else {
                tmpSearch = tmpSearch->rightChild;
                isLeftChild = false;
            }

        }

        Node* newLeft = nullptr, *newRight = nullptr;
        Split(tmpSearch, value, newLeft, newRight);

        auto newNode = new Node(value);
        newNode->leftChild = newLeft;
        newNode->rightChild = newRight;

        assert( parent != nullptr);
        if (isLeftChild){
            parent->leftChild = newNode;
        }else {
            parent->rightChild = newNode;
        }
    }
}

template<class T, class Traversal, class Comparator>
bool CurevoTree<T, Traversal, Comparator>::Delete(const T &value) {
    return false;
}

template<class T, class Traversal, class Comparator>
bool CurevoTree<T, Traversal, Comparator>::Empty() const {
    return root_ == nullptr;
}

template<class T, class Traversal, class Comparator>
void CurevoTree<T, Traversal, Comparator>::DeleteTree() {
    traversal_(root_, [] (Node* node){
        delete node;
    });
}

template<class T, class Traversal, class Comparator>
void CurevoTree<T, Traversal, Comparator>::TraversalFunc() {
    traversal_(root_, [] (Node* node){
        std::cout << node->value.first << " ";
    });

}

template<class T, class Traversal, class Comparator>
void CurevoTree<T, Traversal, Comparator>::Split(Node* currentNode, const T& value, Node*& left, Node*& right){
    if (currentNode == nullptr){
        left = nullptr;
        right = nullptr;
    } else if (currentNode->value.first <= value.first){
        Split(currentNode->rightChild, value, currentNode->rightChild, right);
        left = currentNode;
    } else {
        Split(currentNode->leftChild, value, left, currentNode->leftChild);
        right = currentNode;
    }
}

template<class T, class Traversal, class Comparator>
CurevoTree<T, Traversal, Comparator>::~CurevoTree() {
    traversal_(root_, [](Node* node){
        delete node;
    });
}

#endif //CUREVOTREE_CUREVOTREE_H

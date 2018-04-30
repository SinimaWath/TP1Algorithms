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
    CurevoTree(const CurevoTree&) = delete;
    CurevoTree(CurevoTree&& other) noexcept : root_(std::move(other.root_)){ other.root_ = nullptr;}
    CurevoTree&operator=(const CurevoTree&) = delete;
    CurevoTree&operator=(CurevoTree&& other) noexcept {
        if (this == &other)
            return *this;

        DeleteTree();

        root_ = other.root_;
        other.root_ = nullptr;
    }

    ~CurevoTree() noexcept{
        DeleteTree();
    }

    // Add with random prior
    void Add(const T &value) override;

    // Add with spec prior
    void Add(const std::pair<T, int> &valuePriorPair);
    bool Delete(const T &value) override;
    bool Empty() const override;
    void DeleteTree() override;

    // Это функция нужна, чтобы пользователь мог вызвать Traversal со своим методом
    // Вроде прикольно :0
    template <class Method>
    void TraversalFunc(Method method);

    int GetDepth() override;
    struct Node;
private:
    Comparator comp_;
    Traversal traversal_;

    Node* root_;

    int FindDepth(Node*);
    void Split(Node* currentNode, const T& value, Node*& left, Node*& right);
};

template <class T, class Traversal, class Comparator>
struct CurevoTree<T, Traversal, Comparator>::Node{
    T value;
    int prior;
    Node* leftChild;
    Node* rightChild;

    Node(const T& valueOther, int priorOther) : value(valueOther), prior(priorOther),
                                                   leftChild(nullptr), rightChild(nullptr){}
};

template<class T, class Traversal, class Comparator>
void CurevoTree<T, Traversal, Comparator>::Add(const std::pair<T, int> &valuePriorPair) {
    if (root_ == nullptr){
        root_ = new Node(valuePriorPair.first, valuePriorPair.second);
    } else {
        Node* tmpSearch = root_;
        Node* parent = nullptr;
        bool isLeftChild = true;

        while (tmpSearch != nullptr && tmpSearch->prior >= valuePriorPair.second){
            parent = tmpSearch;
            if (comp_(valuePriorPair.first, tmpSearch->value)) {
                tmpSearch = tmpSearch->leftChild;
                isLeftChild = true;
            } else {
                tmpSearch = tmpSearch->rightChild;
                isLeftChild = false;
            }

        }

        Node* newLeft = nullptr, *newRight = nullptr;
        Split(tmpSearch, valuePriorPair.first, newLeft, newRight);

        auto newNode = new Node(valuePriorPair.first, valuePriorPair.second);
        newNode->leftChild = newLeft;
        newNode->rightChild = newRight;

        if (parent == nullptr) {
            root_ = newNode;
        } else if (isLeftChild){
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
template<class Method>
void CurevoTree<T, Traversal, Comparator>::TraversalFunc(Method method) {
    traversal_(root_, method);

}

template<class T, class Traversal, class Comparator>
void CurevoTree<T, Traversal, Comparator>::Split(Node* currentNode, const T& value, Node*& left, Node*& right){
    if (currentNode == nullptr){
        left = nullptr;
        right = nullptr;
    } else if (currentNode->value <= value){
        Split(currentNode->rightChild, value, currentNode->rightChild, right);
        left = currentNode;
    } else {
        Split(currentNode->leftChild, value, left, currentNode->leftChild);
        right = currentNode;
    }
}


template<class T, class Traversal, class Comparator>
void CurevoTree<T, Traversal, Comparator>::Add(const T &value) {

}

template<class T, class Traversal, class Comparator>
int CurevoTree<T, Traversal, Comparator>::FindDepth(Node* root){
    if (root != nullptr)
        return 1 + std::max(FindDepth(root->leftChild), FindDepth(root->rightChild));
    return 0;
};

template<class T, class Traversal, class Comparator>
int CurevoTree<T, Traversal, Comparator>::GetDepth() {
    return FindDepth(root_);
}

#endif //CUREVOTREE_CUREVOTREE_H

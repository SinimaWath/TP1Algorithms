//
// Created by sinimawath on 29.04.18.
//

#ifndef CUREVOTREE_NAIVETREE_H
#define CUREVOTREE_NAIVETREE_H

#include <functional>
#include <cassert>
#include <stack>
#include "ITree.h"
template <class T, class Traversal = PreOrderTraversal, class Comparator = std::less<T>>
class NaiveTree: public ITree<T>{
public:

    NaiveTree() : root_(nullptr) {}
    NaiveTree(const NaiveTree&) = delete;
    NaiveTree(NaiveTree&& other) noexcept : root_(std::move(other.root_)){ other.root_ = nullptr;}
    NaiveTree&operator=(const NaiveTree&) = delete;
    NaiveTree&operator=(NaiveTree&& other) noexcept {
        if (this == &other)
            return *this;

        DeleteTree();

        root_ = other.root_;
        other.root_ = nullptr;
    }

    void Add(const T &value) override;
    bool Delete(const T &value) override;
    bool Empty() const override;
    void DeleteTree() override;
    void TraversalFunc() override;

private:
    struct Node;

    Traversal traversal_;
    Comparator comp_;

    Node* root_;
};

template <class T, class Traversal, class Comparator>
struct NaiveTree<T, Traversal, Comparator>::Node{
    T value;
    Node* leftChild;
    Node* rightChild;
    Node() = default;
    explicit Node(const T& otherValue) : value(otherValue), leftChild(nullptr), rightChild(nullptr){}
};
template<class T, class Traversal, class Comparator>
void NaiveTree<T, Traversal, Comparator>::Add(const T &value) {
    if (root_ == nullptr){
        root_ = new Node(value);
    }else {

        Node* tmpSearch = root_;
        Node* parent = nullptr;
        bool isLeftChild = true;

        while (tmpSearch != nullptr) {
            parent = tmpSearch;

            if (comp_(value, tmpSearch->value)) {
                tmpSearch = tmpSearch->leftChild;
                isLeftChild = true;
            } else {
                tmpSearch = tmpSearch->rightChild;
                isLeftChild = false;
            }
        }

        assert(parent != nullptr);

        if (isLeftChild){
            parent->leftChild = new Node(value);
        }else{
            parent->rightChild = new Node(value);
        }

    }

}

template<class T, class Traversal, class Comparator>
bool NaiveTree<T, Traversal, Comparator>::Delete(const T &value) {
    return false;
}

template<class T, class Traversal, class Comparator>
bool NaiveTree<T, Traversal, Comparator>::Empty() const {
    return root_ == nullptr;
}

template<class T, class Traversal, class Comparator>
void NaiveTree<T, Traversal, Comparator>::DeleteTree() {
    traversal_(root_, [](Node* node){
        delete node;
    });
}

template<class T, class Traversal, class Comparator>
void NaiveTree<T, Traversal, Comparator>::TraversalFunc() {
    traversal_(root_, [](Node* node){
        std::cout << node->value << " ";
    });
}



#endif //CUREVOTREE_NAIVETREE_H

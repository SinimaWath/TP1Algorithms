//
// Created by sinimawath on 20.04.18.
//

#ifndef TREENAIVE_CTREE_H
#define TREENAIVE_CTREE_H

#include <functional>
#include <set>
#include <memory>
#include <cassert>
#include <stack>

template <class T, class Comparator = std::less<T>>
class CTree {
public:
    CTree(): root_(nullptr), size_(0) {}
    ~CTree();
    CTree(const CTree&) = delete;
    CTree&operator= (const CTree&) = delete;

    CTree(CTree && tree) noexcept : root_(std::move(tree.root_)), size_(std::move(tree.size_)) { tree.root_ = nullptr; }

    CTree&operator=(CTree&& tree) noexcept {

        if (this == &tree){
            return *this;
        }

        root_ = std::move(tree.root_);
        size_ = std::move(tree.size_);

        tree.root_ = nullptr;


    }

    bool Add(const T& value);
    bool Delete(const T& value);
    template<class Method>
    bool Traversal(Method method);
    //void Method(const T&);
    bool Empty();

    struct Node;
private:

    Comparator comp_;

    Node* root_;
    size_t size_;
};

template<class T, class Comparator>
struct CTree<T, Comparator>::Node{
    T value;
    Node* leftChild;
    Node* rightChild;

    Node() = default;
    explicit Node(const T otherValue) : value(otherValue),
                                         leftChild(nullptr), rightChild(nullptr) {}
};

template<class T, class Comparator>
bool CTree<T, Comparator>::Add(const T &value) {
    if (root_ == nullptr){
        root_ = new Node(value);

        //std::cout << "Was added: " <<root_->value << std::endl;
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

    return true;
}


template<class T, class Comparator>
template <class Method>
bool CTree<T, Comparator>::Traversal(Method method) {
    if (Empty()){
        //std::cout << "isEmpty()\n";
        return false;
    }

    std::stack<Node*> nodeStack;
    nodeStack.push(root_);

    while (!nodeStack.empty()){
        Node* currentNode = nodeStack.top();
        nodeStack.pop();

        if (currentNode != nullptr){
            if (currentNode->rightChild != nullptr)
                nodeStack.push(currentNode->rightChild);
            if (currentNode->leftChild != nullptr)
                nodeStack.push(currentNode->leftChild);
            method(currentNode);
        }
    }

    return true;
}

template<class T, class Comparator>
bool CTree<T, Comparator>::Empty() {
    return root_ == nullptr;
}

template<class T, class Comparator>
CTree<T, Comparator>::~CTree() {
    Traversal([](Node* node){
       delete(node);
    });
};

#include "CTree.hpp"

#endif //TREENAIVE_CTREE_H

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

template <class T, class Comparator = std::less_equal<T>>
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
    bool Traversal();
    void Method(const T&);
    bool Empty();

private:
    struct Node;

    Comparator comp_;

    Node* root_;
    size_t size_;
};

template<class T, class Comparator>
struct CTree<T, Comparator>::Node{
    T value;
    Node* parent;
    Node* leftChild;
    Node* rightChild;

    Node() = default;
    explicit Node(const T otherValue) : value(otherValue), parent(nullptr),
                                         leftChild(nullptr), rightChild(nullptr) {}
};

template<class T, class Comparator>
bool CTree<T, Comparator>::Add(const T &value) {
    if (root_ == nullptr){
        root_ = new Node(value);

        //std::cout << "Was added: " <<root_->value << std::endl;
    }else {

        Node* tmpSearch = root_;
        Node* parentSearch = nullptr;

        bool isLeftChild = false;

        while (tmpSearch != nullptr){
            parentSearch = tmpSearch;

            if (comp_(value, tmpSearch->value)){
                tmpSearch = tmpSearch->leftChild;
                isLeftChild = true;
            }else{
                tmpSearch = tmpSearch->rightChild;
                isLeftChild = false;
            }

            if (tmpSearch != nullptr)
                tmpSearch->parent = parentSearch;
        }

        assert(parentSearch != nullptr);

        if (isLeftChild){

            parentSearch->leftChild = new Node(value);
            parentSearch->leftChild->parent = parentSearch;

            //std::cout << value  << " is added as left child of " << parentSearch->value << "\n";
        }else{
            parentSearch->rightChild = new Node(value);
            parentSearch->rightChild->parent = parentSearch;

            //std::cout << value  << " is added as right child of " << parentSearch->value << "\n";
        }

    }
    return true;
}

template<class T, class Comparator>
void CTree<T, Comparator>::Method(const T& value) {
    std::cout << value << " ";
}

template<class T, class Comparator>
bool CTree<T, Comparator>::Traversal() {
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
            Method(currentNode->value);
            if (currentNode->rightChild != nullptr)
                nodeStack.push(currentNode->rightChild);
            if (currentNode->leftChild != nullptr)
                nodeStack.push(currentNode->leftChild);
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
    std::stack<Node*> nodeStack;
    nodeStack.push(root_);

    while (!nodeStack.empty()){
        Node* currentNode = nodeStack.top();
        if (currentNode != nullptr && currentNode->leftChild == nullptr && currentNode->rightChild == nullptr){
            nodeStack.pop();
            if (currentNode->parent == nullptr)
                delete currentNode;
            else{
                if (currentNode->parent->leftChild == currentNode){
                    delete currentNode->parent->leftChild;
                    currentNode->parent->leftChild = nullptr;
                }
                else {
                    delete currentNode->parent->rightChild;
                    currentNode->parent->rightChild = nullptr;
                }
            }
        }else if (currentNode != nullptr){
            if (currentNode->rightChild != nullptr)
                nodeStack.push(currentNode->rightChild);
            if (currentNode->leftChild != nullptr)
                nodeStack.push(currentNode->leftChild);
        }

    }
}

#include "CTree.hpp"

#endif //TREENAIVE_CTREE_H

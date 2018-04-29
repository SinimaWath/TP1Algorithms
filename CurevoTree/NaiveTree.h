//
// Created by sinimawath on 29.04.18.
//

#ifndef CUREVOTREE_NAIVETREE_H
#define CUREVOTREE_NAIVETREE_H

#include <functional>
#include <cassert>
#include <stack>
#include "ITree.h"
template <class T, class Comparator = std::less<T>>
class NaiveTree: public ITree<T>{
public:
    using Node = typename ITree<T>::Node;
    NaiveTree()  = default;
    NaiveTree(const NaiveTree&) = delete;
    NaiveTree(NaiveTree&& other) noexcept : root_(std::move(other.root_)){ other.root_ = nullptr; }
    NaiveTree&operator=(const NaiveTree&) = delete;
    NaiveTree&operator=(NaiveTree&& other){
        if (this == &other){
            return *this;
        }

        DeleteTree();

        root_ = other.root_;
        other.root_ = nullptr;

    }

    void DeleteTree() override;
    void Add(const T &value) override;
    bool Delete(const T &value) override;
    bool Empty() const override;
    void Traversal(IMethod<T>& method) const override;
    ~NaiveTree() override;

private:
    Comparator comp_;
    Node* root_{};
};

template <class T>
struct ITree<T>::Node{
    T value{};
    Node* leftChild;
    Node* rightChild;

    Node() = default;
    explicit Node(const T& otherValue): value(otherValue), leftChild(nullptr),
                                        rightChild(nullptr) {}
};

template<class T, class Comparator>
void NaiveTree<T, Comparator>::Add(const T &value) {
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
}

template<class T, class Comparator>
bool NaiveTree<T, Comparator>::Delete(const T &value) {
    return false;
}

template<class T, class Comparator>
bool NaiveTree<T, Comparator>::Empty() const {
    return root_ == nullptr;
}

template<class T, class Comparator>
void NaiveTree<T, Comparator>::Traversal(IMethod<T> &method) const {
    if (Empty()){
        return;
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

            method.operator()(currentNode);

        }
    }
}

template<class T, class Comparator>
NaiveTree<T, Comparator>::~NaiveTree() {
    DeleteTree();
}

template<class T, class Comparator>
void NaiveTree<T, Comparator>::DeleteTree() {

    MethodDeleteTree<T> method;
    Traversal(method);
}


#endif //CUREVOTREE_NAIVETREE_H

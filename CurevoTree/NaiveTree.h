//
// Created by sinimawath on 29.04.18.
//

#ifndef CUREVOTREE_NAIVETREE_H
#define CUREVOTREE_NAIVETREE_H

#include <functional>
#include <cassert>
#include <stack>
#include <queue>
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

    ~NaiveTree() noexcept{
        DeleteTree();
    }
    void Add(const T &value) override;
    bool Delete(const T &value) override;
    bool Empty() const override;
    void DeleteTree() override;

    // Это функция нужна, чтобы пользователь мог вызвать Traversal со своим методом
    // Вроде прикольно :0
    // Traversal функтор можно передавать разный через параметры шаблона
    // И использовать в классе и вне класса.
    // Конечно, вообще не ООП подход, просто было скучно :(
    template <class Method>
    void TraversalFunc(Method method);

    int GetDepth() override;

    struct Node;
private:

    Traversal traversal_;
    Comparator comp_;

    Node* root_;

    int FindDepth(Node*);
};

template <class T, class Traversal, class Comparator>
struct NaiveTree<T, Traversal, Comparator>::Node{
    T value;
    int depth;
    Node* leftChild;
    Node* rightChild;
    explicit Node(const T& otherValue) : value(otherValue), depth(0), leftChild(nullptr), rightChild(nullptr){}
};
template<class T, class Traversal, class Comparator>
void NaiveTree<T, Traversal, Comparator>::Add(const T &value) {
    if (root_ == nullptr){
        root_ = new Node(value);
        root_->depth = 1;
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

        auto newNode = new Node(value);
        newNode->depth = parent->depth + 1;

        if (isLeftChild){
            parent->leftChild = newNode;
        }else{
            parent->rightChild = newNode;
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
template<class Method>
void NaiveTree<T, Traversal, Comparator>::TraversalFunc(Method method) {
    traversal_(root_, method);
}

template<class T, class Traversal, class Comparator>
int NaiveTree<T, Traversal, Comparator>::GetDepth() {
    return FindDepth(root_);
}

template<class T, class Traversal, class Comparator>
int NaiveTree<T, Traversal, Comparator>::FindDepth(Node* root){
    int maxDepth = 0;
    traversal_(root, [&maxDepth](Node* node){
        maxDepth = std::max(maxDepth, node->depth);
    });

    return maxDepth;
}


#endif //CUREVOTREE_NAIVETREE_H

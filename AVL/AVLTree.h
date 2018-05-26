//
// Created by sinimawath on 30.04.18.
//

#ifndef AVL_AVLTREE_H
#define AVL_AVLTREE_H

#include <functional>
#include <stack>
#include <iostream>

template<class T, class Comparator = std::less<T>>
class AVLTree {
public:

    AVLTree() : root_(nullptr) {}
    AVLTree(const AVLTree&) = delete;
    AVLTree(AVLTree&& other) noexcept : root_(std::move(other.root_)) { other.root_ = nullptr; }
    AVLTree&operator=(const AVLTree&) = delete;
    AVLTree&operator=(AVLTree&& other) noexcept {

        if (this == &other){
            return *this;
        }

        DeleteTree();
        root_ = std::move(other.root_);
        other.root_ = nullptr;
    }
    ~AVLTree() noexcept {
        DeleteTree();
    }

    int Add(const T& key);
    void DeleteTree();
    bool Empty();
    void RemoveByPos(int position);
private:

    struct Node{
        T key;
        int nodes;
        unsigned char height;
        Node* leftChild;
        Node* rightChild;

        explicit Node(const T& k): key(k), nodes(1), height(1), leftChild(nullptr), rightChild(nullptr){}
    };

    Comparator comp_;

    Node* root_;

    unsigned char NodeHeight(Node* node);
    void FixHeight(Node* node);
    void FixNodes(Node* node);
    int BalanceFactor(Node* node);
    Node* RotateRight(Node* node);
    Node* RotateLeft(Node* node);
    Node* BalanceNode(Node* node);
    Node* DeleteMin(Node *node, Node **min);
    Node* Add(Node* node, const T& key, int& pos);

    int Nodes(Node* node);
    Node* RemoveByPos(Node* node, int position);

    template <class Method>
    void Traversal(Method method);
};

template<class T, class Comparator>
bool AVLTree<T, Comparator>::Empty() {
    return root_ == nullptr;
}

template<class T, class Comparator>
int AVLTree<T, Comparator>::Add(const T &key) {
    int pos = 0;
    root_ = Add(root_, key, pos);

    return pos;
}

template<class T, class Comparator>
void AVLTree<T, Comparator>::FixHeight(Node *node) {
    unsigned char hl = NodeHeight(node->leftChild);
    unsigned char hr = NodeHeight(node->rightChild);

    node->height = (hl > hr ? hl : hr) + 1;
}

template<class T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::RotateRight(Node *node) {
    Node* tmp = node->leftChild;

    node->leftChild = tmp->rightChild;
    tmp->rightChild = node;

    FixNodes(node);
    FixNodes(tmp);

    FixHeight(node);
    FixHeight(tmp);

    return tmp;
}

template<class T, class Comparator>
typename AVLTree<T, Comparator>::Node *AVLTree<T, Comparator>::RotateLeft(Node *node) {
    Node* tmp = node->rightChild;
    node->rightChild = tmp->leftChild;
    tmp->leftChild = node;

    FixNodes(node);
    FixNodes(tmp);

    FixHeight(node);
    FixHeight(tmp);

    return tmp;
}

template<class T, class Comparator>
typename AVLTree<T, Comparator>::Node *AVLTree<T, Comparator>::BalanceNode(Node *node) {
    FixNodes(node);
    FixHeight(node);

    if (BalanceFactor(node) == 2){
        if (BalanceFactor(node->rightChild) < 0)
            node->rightChild = RotateRight(node->rightChild);
        return RotateLeft(node);
    } else if (BalanceFactor(node) == -2){
        if (BalanceFactor(node->leftChild) > 0)
            node->leftChild = RotateLeft(node->leftChild);
        return RotateRight(node);
    }

    return node;
}

template<class T, class Comparator>
void AVLTree<T, Comparator>::DeleteTree() {
    Traversal([](Node* node){
        delete node;
    });
}

template<class T, class Comparator>
unsigned char AVLTree<T, Comparator>::NodeHeight(Node *node) {
    return (node ? node->height : 0);
}

template<class T, class Comparator>
int AVLTree<T, Comparator>::BalanceFactor(Node *node) {
    return NodeHeight(node->rightChild) - NodeHeight(node->leftChild);
}

template<class T, class Comparator>
typename AVLTree<T, Comparator>::Node* AVLTree<T, Comparator>::Add(Node *node, const T &key, int& pos) {

    if ( !node ) return new Node(key);

    node->nodes++;

    if (comp_(key, node->key)){
        pos += Nodes(node->rightChild) + 1;
        node->leftChild = Add(node->leftChild, key, pos);
    } else {
        node->rightChild = Add(node->rightChild, key, pos);
    }

    return BalanceNode(node);
}

template<class T, class Comparator>
typename AVLTree<T, Comparator>::Node *AVLTree<T, Comparator>::DeleteMin(Node *node, Node** min) {

    if ( node->leftChild == nullptr ){
        *min = node;
        return node->rightChild;
    }

    node->leftChild = DeleteMin(node->leftChild, min);
    node->nodes--;

    BalanceNode(node);
}


template<class T, class Comparator>
void AVLTree<T, Comparator>::RemoveByPos(int position) {
    if (root_->nodes <= position || Empty())
        return;

    root_= RemoveByPos(root_, position);
}

template<class T, class Comparator>
int AVLTree<T, Comparator>::Nodes(Node *node) {
    return node ? node->nodes: 0;
}

template<class T, class Comparator>
void AVLTree<T, Comparator>::FixNodes(AVLTree::Node *node) {
    int nl = Nodes(node->leftChild);
    int nr = Nodes(node->rightChild);

    node->nodes = nl + nr + 1;
}

template<class T, class Comparator>
typename AVLTree<T, Comparator>::Node *AVLTree<T, Comparator>::RemoveByPos(AVLTree::Node *node, int position) {
    int pos = position - Nodes(node->rightChild);
    if ( pos  > 0){
        node->leftChild = RemoveByPos(node->leftChild, pos - 1);
    }else if ( pos  < 0 ){
        node->rightChild = RemoveByPos(node->rightChild, position);
    }else{
        Node* q = node->leftChild;
        Node* r = node->rightChild;

        delete node;
        if (!r) return q;

        Node* min;
        Node* right = DeleteMin(r, &min);

        min->rightChild = right;
        min->leftChild = q;
        return BalanceNode(min);

    }
    node->nodes--;
    return BalanceNode(node);
}

template<class T, class Comparator>
template<class Method>
void AVLTree<T, Comparator>::Traversal(Method method) {
    std::stack<Node*> nodeStack;
    nodeStack.push(root_);

    while (!nodeStack.empty()) {
        Node *currentNode = nodeStack.top();
        nodeStack.pop();

        if (currentNode != nullptr) {

            if (currentNode->rightChild != nullptr)
                nodeStack.push(currentNode->rightChild);
            if (currentNode->leftChild != nullptr)
                nodeStack.push(currentNode->leftChild);

            method(currentNode);
        }
    }
}


#endif //AVL_AVLTREE_H

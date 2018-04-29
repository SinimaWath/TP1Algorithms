//
// Created by sinimawath on 28.04.18.
//

#ifndef CUREVOTREE_ITREE_H
#define CUREVOTREE_ITREE_H

template <class T>
struct IMethod;
struct MethodImp;

template<class T>
class ITree{
public:
    virtual void Add(const T& value) = 0;
    virtual bool Delete(const T& value) = 0;
    virtual bool Empty() const = 0;

    virtual void Traversal(IMethod<T>& method) const = 0;

    virtual void DeleteTree() = 0;
    virtual ~ITree() = default;

    struct Node;

};

template <class T>
struct IMethod{
    virtual void operator()(typename ITree<T>::Node* node) = 0;
};

template <class T>
class MethodCout: public IMethod<T>{
public:
    void operator()(typename ITree<T>::Node *node) override {
        std::cout << node->value << "\n";
    }
};

template <class T>
class MethodDeleteTree: public IMethod<T>{
public:
    void operator()(typename ITree<T>::Node *node) override {
        delete node;
    }
};



#endif //CUREVOTREE_ITREE_H

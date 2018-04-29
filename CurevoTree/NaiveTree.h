//
// Created by sinimawath on 29.04.18.
//

#ifndef CUREVOTREE_NAIVETREE_H
#define CUREVOTREE_NAIVETREE_H

#include <functional>
#include "ITree.h"
template <class T, class Comparator = std::less<T>>
class NaiveTree: public ITree{
public:

    void Add(const T &value) override;
    bool Delete(const T &value) override;
    bool Empty() const override;
    template <class Method>
    void Traversal(Method method) const override;
    ~NaiveTree() override = default;

private:
    T* buffer_;
    int bufferSize_;

};

template<class T, class Comparator>
void NaiveTree<T, Comparator>::Add(const T &value) {

}

template<class T, class Comparator>
bool NaiveTree<T, Comparator>::Delete(const T &value) {
    return false;
}

template<class T, class Comparator>
bool NaiveTree<T, Comparator>::Empty() const {
    return false;
}

template<class T, class Comparator>
template<class Method>
void NaiveTree<T, Comparator>::Traversal(Method method) const {

}

template<class T, class Comparator>
NaiveTree<T, Comparator>::~NaiveTree() {

}


#endif //CUREVOTREE_NAIVETREE_H

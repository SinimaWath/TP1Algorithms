//
// Created by sinimawath on 28.04.18.
//

#ifndef CUREVOTREE_ITREE_H
#define CUREVOTREE_ITREE_H

template<class T>
class ITree{
public:
    virtual void Add(const T& value) = 0;
    virtual bool Delete(const T& value) = 0;
    virtual bool Empty() const = 0;

    template<class Method>
    virtual void Traversal(Method method) const = 0;
    virtual ~ITree() = default;

};
#endif //CUREVOTREE_ITREE_H

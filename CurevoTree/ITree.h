//
// Created by sinimawath on 28.04.18.
//

#ifndef CUREVOTREE_ITREE_H
#define CUREVOTREE_ITREE_H

// Интерфейс для Деревьев :)
template<class T>
class ITree{
public:
    virtual void Add(const T& value) = 0;
    virtual bool Delete(const T& value) = 0;
    virtual bool Empty() const = 0;
    virtual void DeleteTree() = 0;
    virtual int GetDepth() = 0;
    virtual ~ITree() = default;

};

// default traversal
class PreOrderTraversal{
public:
    template <class NodeType, class Method>
    void operator()(NodeType* root_, Method method){
        std::stack<NodeType*> nodeStack;
        nodeStack.push(root_);

        while (!nodeStack.empty()){
            NodeType* currentNode = nodeStack.top();
            nodeStack.pop();

            if (currentNode != nullptr){

                if (currentNode->rightChild != nullptr)
                    nodeStack.push(currentNode->rightChild);
                if (currentNode->leftChild != nullptr)
                    nodeStack.push(currentNode->leftChild);

                method(currentNode);
            }
        }
    }
};


#endif //CUREVOTREE_ITREE_H

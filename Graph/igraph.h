#include <vector>
#include <cassert>

#ifndef IGRAPH_H
#define IGRAPH_H

struct IGraph{
    virtual ~IGraph() = default;

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

template <class To, class From>
To to (const From& from){
    To to = static_cast<To>(from);
    assert (static_cast<From>(to) == from);

    return to;
};

#endif
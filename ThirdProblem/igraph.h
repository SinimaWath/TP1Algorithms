//
// Created by sinimawath on 26.05.18.
//

#ifndef THIRDPROBLEM_IGRAPH_H
#define THIRDPROBLEM_IGRAPH_H

#include <iostream>
#include <cassert>
#include <vector>
#include <memory>
#include <list>
#include <algorithm>
#include <queue>

struct IGraph{
    virtual ~IGraph() = default;

    // Добавление ребра от from к to.
    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;

};

template <class To, class From>
To to (const From& from){
    auto to = static_cast<To>(from);
    assert (static_cast<From>(to) == from);

    return to;
}
#endif //THIRDPROBLEM_IGRAPH_H

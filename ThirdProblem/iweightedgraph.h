//
// Created by sinimawath on 26.05.18.
//

#ifndef THIRDPROBLEM_IWEIGHTEDGRAPH_H
#define THIRDPROBLEM_IWEIGHTEDGRAPH_H

#include "igraph.h"
// Взвешанный граф
struct IWeightedGraph : public IGraph{
    virtual ~IWeightedGraph() = default;
    virtual void AddEdge(int from, int to, int weight) = 0;
    void AddEdge(int from, int to) override = 0;
    virtual int GetEdgeWeight(int from, int to) = 0;
};

#endif //THIRDPROBLEM_IWEIGHTEDGRAPH_H

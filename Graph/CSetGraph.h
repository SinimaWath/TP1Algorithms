//
// Created by sinimawath on 25.05.18.
//

#ifndef GRAPH_CSETGRAPH_H
#define GRAPH_CSETGRAPH_H

#include <memory>
#include <unordered_set>
#include "igraph.h"

class CSetGraph : public IGraph{
public:
    explicit CSetGraph(const std::shared_ptr<IGraph>& igraph);
    explicit CSetGraph(int n) : setVector(to<decltype(setVector.size())>(n)) {}
    
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

    bool isValidVertices(int ver);
private:
    std::vector<std::unordered_set<int>> setVector;
};


#endif //GRAPH_CSETGRAPH_H

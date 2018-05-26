//
// Created by sinimawath on 18.05.18.
//

#ifndef GRAPH_CLISTGRAPH_H
#define GRAPH_CLISTGRAPH_H

#include <memory>
#include "igraph.h"
#include "list"

class CListGraph : public IGraph{
public:
    explicit CListGraph(int n) : adjacencyList( n ) {}
    explicit CListGraph(const std::shared_ptr<IGraph>& igraph);
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

    bool isValidVertices(int ver);

private:
    std::vector<std::list<int>> adjacencyList;
};


#endif //GRAPH_CLISTGRAPH_H

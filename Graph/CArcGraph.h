//
// Created by sinimawath on 26.05.18.
//

#ifndef GRAPH_CARCGRAPH_H
#define GRAPH_CARCGRAPH_H

#include <memory>
#include "igraph.h"

class CArcGraph : public IGraph{
public:

    explicit CArcGraph(const std::shared_ptr<IGraph>& igraph);
    explicit CArcGraph(int n) : vertCount(n) {}
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
    bool isValidVertices(int ver);

private:
    std::vector<std::pair<int, int>> arcGraph;
    int vertCount;
};


#endif //GRAPH_CARCGRAPH_H

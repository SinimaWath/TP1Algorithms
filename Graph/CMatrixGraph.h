//
// Created by sinimawath on 23.05.18.
//

#ifndef GRAPH_CMATRIXGRAPH_H
#define GRAPH_CMATRIXGRAPH_H

#include <memory>
#include "igraph.h"
class CMatrixGraph : public IGraph {
public:
    explicit CMatrixGraph(int n) : adjacencyMatrix(to<decltype(adjacencyMatrix.size())>(n) ,
                                          std::vector<int>(to<decltype(adjacencyMatrix.size())>(n))) {}
    explicit CMatrixGraph(const std::shared_ptr<IGraph>& igraph);

    bool isValidVertices(int ver);
    void AddEdge(int from, int to) override;
    int VerticesCount() const override;
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;
private:
    std::vector<std::vector<int>> adjacencyMatrix;
};


#endif //GRAPH_CMATRIXGRAPH_H

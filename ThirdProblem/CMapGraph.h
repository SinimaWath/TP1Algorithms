//
// Created by sinimawath on 26.05.18.
//

#ifndef THIRDPROBLEM_CLISTGRAPH_H
#define THIRDPROBLEM_CLISTGRAPH_H

#include "igraph.h"
#include "iweightedgraph.h"
#include <map>
#include <set>
#include <unordered_set>

class CMapGraph : public IWeightedGraph{
public:
    CMapGraph() = default;
    explicit CMapGraph(int n) : adjacencyList( to<decltype(adjacencyList.size())>(n) ) {}
    CMapGraph(const CMapGraph&) = delete;
    CMapGraph&operator=(const CMapGraph&) = delete;
    CMapGraph(CMapGraph&& other) noexcept : adjacencyList(std::move(other.adjacencyList)) {}
    CMapGraph&operator=(CMapGraph&& other) noexcept {
        if (this == &other){
            return *this;
        }
        adjacencyList = std::move(other.adjacencyList);
    }
    ~CMapGraph()  = default;

    void AddEdge(int from, int to, int weight) override;
    int GetEdgeWeight(int from, int to) override;
    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

    bool isValidVertices(int ver);

private:
    std::vector<std::map<int, int>> adjacencyList;

};


#endif //THIRDPROBLEM_CLISTGRAPH_H

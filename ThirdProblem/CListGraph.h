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

class CListGraph : public IWeightedGraph{
public:
    void AddEdge(int from, int to, int weight) override;

    int GetEdgeWeight(int from, int to) override;

    explicit CListGraph(int n) : adjacencyList( to<decltype(adjacencyList.size())>(n) ) {}

    explicit CListGraph(const std::shared_ptr<IGraph>& igraph);
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

    bool isValidVertices(int ver);
    void Print() override;

private:
    //std::vector<std::unordered_set<>> a
    std::vector<std::list<int>> adjacencyList;
    //std::vector<std::list<std::pair<int, int>>> adjacencyList;
    //std::multimap<std::pair<int, int>, int> edgesWeight;
    std::map<std::pair<int, int>, int> edgesWeight;
};


#endif //THIRDPROBLEM_CLISTGRAPH_H

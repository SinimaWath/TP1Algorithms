//
// Created by sinimawath on 26.05.18.
//

#include "CListGraph.h"

void CListGraph::AddEdge(int from, int to) {

    assert(isValidVertices(from));
    assert(isValidVertices(to));

    adjacencyList[from].push_back(to);
}

int CListGraph::VerticesCount() const {
    return to<int>(adjacencyList.size());
}

std::vector<int> CListGraph::GetNextVertices(int vertex) const {
    std::vector<int> vert(adjacencyList[vertex].begin(), adjacencyList[vertex].end());
    return vert;
}

std::vector<int> CListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> vert;
    for (decltype(adjacencyList.size()) i = 0; i < adjacencyList.size(); i++){
        if (std::find(adjacencyList[i].begin(), adjacencyList[i].end(), vertex) != adjacencyList[i].end()){
            vert.push_back(to<int>(i));
        }
    }
    return vert;
}

bool CListGraph::isValidVertices(int ver) {
    return ver >= 0 && ver < to<int>(adjacencyList.size());
}

CListGraph::CListGraph(const std::shared_ptr<IGraph>& igraph) {
    adjacencyList.resize(to<decltype(adjacencyList.size())>(igraph->VerticesCount()));

    for (decltype(igraph->VerticesCount()) i = 0; i <  igraph->VerticesCount(); i++) {
        auto vertices = igraph->GetNextVertices(i);
        std::copy(vertices.begin(), vertices.end(), std::back_inserter(adjacencyList[i]));
    }
}

void CListGraph::AddEdge(int from, int to, int weight) {
    AddEdge(from, to);

    edgesWeight.insert({{from, to}, weight});
    //edgesWeight[{from ,to}] = weight;
}

// -1 - means: there is no such edge
int CListGraph::GetEdgeWeight(int from, int to) {
    auto it = edgesWeight.find({from , to});
    return it != edgesWeight.end() ? it->second : -1;
}

void CListGraph::Print() {
    int i = 0;
    for (const auto& vecVector : adjacencyList){
        std::cout << i++ << " ";
        for (const auto& vec: vecVector ){
            std::cout << vec << " ";
        }
        std::cout << "\n";
    }
}

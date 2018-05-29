//
// Created by sinimawath on 26.05.18.
//

#include "CMapGraph.h"

int CMapGraph::VerticesCount() const {
    return to<int>(adjacencyList.size());
}
std::vector<int> CMapGraph::GetNextVertices(int vertex) const {
    std::vector<int> vert;
    for (const auto &it : adjacencyList[vertex]) {
        vert.push_back(it.first);
    }
    return vert;
}

std::vector<int> CMapGraph::GetPrevVertices(int vertex) const {
    std::vector<int> vert;
    for (decltype(adjacencyList.size()) i = 0; i < adjacencyList.size(); i++){
        if ( adjacencyList[i].find(vertex) != adjacencyList[i].end()){
            vert.push_back(to<int>(i));
        }
    }
    return vert;
}

bool CMapGraph::isValidVertices(int ver) {
    return ver >= 0 && ver < to<int>(adjacencyList.size());
}

void CMapGraph::AddEdge(int from, int to, int weight) {

    assert(isValidVertices(from));
    assert(isValidVertices(to));

    auto it = adjacencyList[from].find(to);
    if (it != adjacencyList[from].end()){
        if (it->second > weight)
            it->second = weight;
    } else{
        adjacencyList[from].insert({to, weight});
    }
}

// -1 - means: there is no such edge
int CMapGraph::GetEdgeWeight(int from, int to) {
    auto it = adjacencyList[from].find(to);
    return it != adjacencyList[from].end() ? it->second : -1;
}

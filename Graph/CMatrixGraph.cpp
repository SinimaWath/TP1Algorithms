//
// Created by sinimawath on 23.05.18.
//

#include "CMatrixGraph.h"
#include <algorithm>
#include <iostream>

void CMatrixGraph::AddEdge(int from, int to) {
    assert( isValidVertices(from) );
    assert( isValidVertices(to) );

    adjacencyMatrix[from][to] = 1;
}

int CMatrixGraph::VerticesCount() const {
    return to<int>(adjacencyMatrix.size());
}

std::vector<int> CMatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> vert;

    for (decltype(adjacencyMatrix[vertex].size()) i = 0; i < adjacencyMatrix[vertex].size(); i++){
        if (adjacencyMatrix[vertex][i] == 1 ){
            vert.push_back(to<int>(i));
        }
    }
    return vert;
}

std::vector<int> CMatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> res;

    decltype(adjacencyMatrix.size()) i = 0;
    std::for_each(adjacencyMatrix.cbegin(), adjacencyMatrix.cend(), [&i, &vertex, &res](const auto vec) {
        if (vec[vertex] == 1)
            res.push_back(to<int>(i));
        i++;
    });

    return res;
}

CMatrixGraph::CMatrixGraph(const std::shared_ptr<IGraph>& igraph) {
    auto vertCount = to<decltype(adjacencyMatrix.size())>(igraph->VerticesCount());

    std::vector<std::vector<int>> tmpMatrix(vertCount, std::vector<int>(vertCount));

    for (decltype(vertCount) i = 0; i < vertCount; i++){
        auto nextVert = igraph->GetNextVertices(to<int>(i));
        for (const auto& el : nextVert){
            tmpMatrix[i][el] = 1;
        }
    }

    adjacencyMatrix = std::move(tmpMatrix);
}

bool CMatrixGraph::isValidVertices(int ver) {
    return ver >= 0 && ver < to<int>(adjacencyMatrix.size());
}
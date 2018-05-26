//
// Created by sinimawath on 25.05.18.
//

#include <algorithm>
#include "CSetGraph.h"

void CSetGraph::AddEdge(int from, int to) {

    assert(isValidVertices(from));
    assert(isValidVertices(to));

    setVector[from].insert(to);
}

int CSetGraph::VerticesCount() const {
    return to<int>(setVector.size());
}

std::vector<int> CSetGraph::GetNextVertices(int vertex) const {
    std::vector<int> vert(setVector[vertex].begin(), setVector[vertex].end());
    return vert;
}

std::vector<int> CSetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> vert;
    for (decltype(setVector.size()) i = 0; i < setVector.size(); i++){
        if ( setVector[i].find(vertex) != setVector[i].end())
            vert.push_back(to<int>(i));
    }
    return vert;
}

CSetGraph::CSetGraph(const std::shared_ptr<IGraph> &igraph) {
    auto verCount = to<decltype(setVector.size())>(igraph->VerticesCount());
    setVector.reserve(verCount);

    for (decltype(verCount) i = 0; i < verCount; i++) {
        auto vecVert = igraph->GetNextVertices(to<int>(i));
        setVector.emplace_back(vecVert.begin(), vecVert.end());
    }
}

bool CSetGraph::isValidVertices(int ver) {
    return ver >=0 && to<decltype(setVector.size())>(ver) < setVector.size();
}

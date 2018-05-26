//
// Created by sinimawath on 26.05.18.
//

#include <algorithm>
#include "CArcGraph.h"

void CArcGraph::AddEdge(int from, int to) {
    assert(isValidVertices(from));
    assert(isValidVertices(to));

    arcGraph.emplace_back(from, to);
}

int CArcGraph::VerticesCount() const {
    return vertCount;
}

std::vector<int> CArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> ver;
    for (const auto& arc : arcGraph)
        if (arc.first == vertex)
            ver.push_back(arc.second);

    return ver;
}

std::vector<int> CArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> ver;
    for (const auto& arc : arcGraph)
        if (arc.second == vertex)
            ver.push_back(arc.first);

    return ver;
}

bool CArcGraph::isValidVertices(int ver) {
    return ver >= 0 && ver < vertCount;
}

CArcGraph::CArcGraph(const std::shared_ptr<IGraph> &igraph) {
    auto vertCount = igraph->VerticesCount();
    for (decltype(vertCount) i = 0; i < vertCount; i++){
        auto vertVector = igraph->GetNextVertices(i);

        for (const auto& vert : vertVector)
            arcGraph.emplace_back(i, vert);

    }
}

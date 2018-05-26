#include <iostream>
#include "CListGraph.h"
#include "CMatrixGraph.h"
#include "CSetGraph.h"
#include "CArcGraph.h"

int main() {
    std::shared_ptr<IGraph> graph(new CMatrixGraph(3));

    graph->AddEdge(1, 0);
    graph->AddEdge(1, 2);
    graph->AddEdge(2, 1);
    graph->AddEdge(2, 0);

    auto setGraph = std::make_shared<CSetGraph>(graph);
    auto vert2 = setGraph->GetPrevVertices(2);

    for (const auto& el: vert2){
        std::cout << el << " ";
    }


    return 0;
}
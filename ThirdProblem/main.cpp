#include <iostream>
#include <cassert>
#include <set>
#include <algorithm>
#include <limits>
#include "iweightedgraph.h"
#include "CListGraph.h"

using namespace std;

int FindShortestWay(const shared_ptr<IWeightedGraph> &graph, int fromVec, int toVec){
    vector<int> distances(to<size_t>(graph->VerticesCount()), INT32_MAX);
    distances[fromVec] = 0;
    set<pair<int, int>> q;
    q.insert({distances[fromVec], fromVec});
    while (!q.empty()){
        auto v = q.begin()->second;
        q.erase(q.begin());

        auto nextVert = graph->GetNextVertices(v);
        for (const auto& to: nextVert){
            auto edgeWeight = graph->GetEdgeWeight(v, to);
            if (distances[v] + edgeWeight < distances[to] && edgeWeight != -1){
                q.erase({distances[to], to});
                distances[to] = distances[v] + edgeWeight;
                q.insert({distances[to], to});
            }
        }
    }


    return distances[toVec];
}
void Test(){
    std::shared_ptr<IWeightedGraph> graph (new CListGraph(2));
    graph->AddEdge(0, 1);
    graph->AddEdge(1, 0, 2);
    graph->Print();

}

int main() {

    int cityCount = 0, roadCount = 0;

    cin >> cityCount >> roadCount;

    assert(cityCount >= 0);
    assert(roadCount >= 0);

   // auto graph = new CListGraph(cityCount);
    std::shared_ptr<IWeightedGraph> graph (new CListGraph(cityCount));
    while (roadCount--){
        int from = 0, to = 0, weight = 0;

        cin >> from >> to >> weight;

        assert(from >= 0);
        assert(to >= 0);
        assert(weight >= 0);

        graph->AddEdge(from, to, weight);
        graph->AddEdge(to, from, weight);
    }

    int from = 0, to = 0;

    cin >> from >> to;

    assert(from >= 0);
    assert(to >= 0);

    graph->Print();
    cout << FindShortestWay(graph, from ,to);

    return 0;
}
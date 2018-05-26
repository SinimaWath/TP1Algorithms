/*
 * Дан невзвешенный неориентированный граф.
 * В графе может быть несколько кратчайших путей между какими-то вершинами.
 * Найдите количество различных кратчайших путей между заданными вершинами.
 * Требуемая сложность O(V+E).
 */

#include <iostream>
#include <cassert>
#include <vector>
#include <memory>
#include <list>
#include <algorithm>
#include <queue>

struct IGraph{
    virtual ~IGraph() = default;

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

template <class To, class From>
To to (const From& from){
    auto to = static_cast<To>(from);
    assert (static_cast<From>(to) == from);

    return to;
}

class CListGraph : public IGraph{
public:
    explicit CListGraph(int n) : adjacencyList( n ) {}
    explicit CListGraph(const std::shared_ptr<IGraph>& igraph);
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

    bool isValidVertices(int ver);

private:
    std::vector<std::list<int>> adjacencyList;
};

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


int FindShortestWayCount(const std::shared_ptr<IGraph>& graph, const int fromVert, const int toVert){
    auto graphCount = to<size_t>(graph->VerticesCount());
    std::vector<int> dist(graphCount);
    std::vector<int> waysCount(graphCount);
    std::vector<char> visited(graphCount);

    std::queue<int> queue;
    queue.push(fromVert);

    visited[fromVert] = 1;
    dist[fromVert] = 0;
    waysCount[fromVert] = 1;

    while (!queue.empty()){
        int currentVert = queue.front();
        queue.pop();
        auto nextVerts = graph->GetNextVertices(currentVert);
        for (const auto& vert : nextVerts){
            if (visited[vert] == 0){
                dist[vert] = dist[currentVert] + 1;
                visited[vert] = 1;
                queue.push(vert);
            }
            if (dist[currentVert] + 1 == dist[vert]){
                waysCount[vert] += waysCount[currentVert];
            }
        }
    }

    return waysCount[toVert];
}

int main() {
    int vCount = 0, eCount = 0;
    std::cin >> vCount >> eCount;

    assert(vCount >= 0);
    assert(eCount >= 0);

    std::shared_ptr<IGraph> graph(new CListGraph(vCount));

    while (eCount--){
        int from = 0, to = 0;
        std::cin >> from >> to;
        assert(from >= 0);
        assert(to >= 0);

        graph->AddEdge(from , to);
        graph->AddEdge(to , from);
    }

    int from = 0, to = 0;

    std::cin >> from >> to;

    assert(from >= 0 && from < vCount);
    assert(to >= 0 && from < vCount);

    std::cout << FindShortestWayCount(graph, from, to);

    return 0;
}
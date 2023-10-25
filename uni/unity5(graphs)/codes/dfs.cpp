#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Graph {
    int vertices;
    vector<vector<int>> adjacencyList;

public:
    Graph(int vertices) {
        this->vertices = vertices;
        adjacencyList.resize(vertices);
    }

    void addEdge(int v, int w){adjacencyList[v].push_back(w);}

    void DFS(int start);
};


void Graph::DFS(int start) {
    vector<bool> visited(vertices, false);
    stack<int> stack;

    visited[start] = true;
    stack.push(start);

    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();

        cout << current << " ";

        for (int neighbor : adjacencyList[current]) {
            if (visited[neighbor]==false) {
                visited[neighbor] = true;
                stack.push(neighbor);
            }
        }
    }
}


int main() {
    Graph g(7); // Criar um grafo com 7 vértices

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    cout << "Busca em Profundidade a partir do vertice 0: " << endl;
    g.DFS(0);

    return 0;
}

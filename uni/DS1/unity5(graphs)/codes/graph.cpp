#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<int>> adjMatrix;

public:
    Graph(int vertices) : numVertices(vertices) {
        adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
    }

    void addEdge(int source, int destination) {
        if (source >= 0 && source < numVertices && destination >= 0 && destination < numVertices) {
            adjMatrix[source][destination] = 1;
            adjMatrix[destination][source] = 1; // Uncomment this line if the graph is undirected
        }
    }

    void printGraph() {
        for (int i = 0; i < numVertices; i++) {
            cout << "Adjacent to vertex " << i << ": ";
            for (int j = 0; j < numVertices; j++) {
                if (adjMatrix[i][j] == 1) {
                    cout << j << " ";
                }
            }
            cout << endl;
        }
    }

    vector<vector<int>> getAdjacencyMatrix() {
        return adjMatrix;
    }
};

int main() {
    Graph graph(5);

    graph.addEdge(0, 1);
    graph.addEdge(0, 4);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);

    graph.printGraph();


    vector<vector<int>> adjacencyMatrix = graph.getAdjacencyMatrix();
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}

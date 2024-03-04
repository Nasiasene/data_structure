#include <iostream>
#include <list>
#include <queue>

using namespace std;

class Grafo {
    int vertices; // Número de vértices
    list<int> *adj; // Lista de adjacência

public:
    Grafo(int V){
        vertices = V;
        adj = new list<int>[V];
    }

    void adicionarAresta(int v, int w){adj[v].push_back(w);}

    void BFS(int s); // Realizar busca em largura a partir de um vértice
};

void Grafo::BFS(int s) {
    // Marca todos os vértices como não visitados
    bool *visitado = new bool[vertices];
    for (int i = 0; i < vertices; i++)
        visitado[i] = false; //Marcando como não visitado.


    // Cria uma pilha para a busca em largura
    queue<int> pilha;

    // Marca o vértice atual como visitado e o enfileira
    visitado[s] = true;
    pilha.push(s);

    while (!pilha.empty()) {
        // Desenfileira um vértice da pilha e imprime
        s = pilha.front();
        cout << s << " ";
        pilha.pop();

        // Pega todos os vértices adjacentes ao vértice desenfileirado
        for (auto i = adj[s].begin(); i != adj[s].end(); ++i) {
            if (!visitado[*i]) {
                visitado[*i] = true;
                pilha.push(*i);
            }
        }
    }
}

int main() {
    Grafo grafo(6);
    grafo.adicionarAresta(0, 1);
    grafo.adicionarAresta(0, 2);
    grafo.adicionarAresta(1, 3);
    grafo.adicionarAresta(2, 4);
    grafo.adicionarAresta(2, 5);

    cout << "Busca em Largura (BFS) a partir do vertice 0:" << endl;
    grafo.BFS(1);

    return 0;
}
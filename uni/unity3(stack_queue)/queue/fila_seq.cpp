#include <iostream>

using namespace std;

class FilaSeq{
    int *dados;
    int inicio;
    int fim;
    int tamanho;
    int tamanho_max;

    public:
        FilaSeq(int tam){
            inicio = 0; //index inicial
            fim = -1;
            tamanho = 0;

            tamanho_max = tam;
            dados = new int[tamanho_max];
        }

        bool vazia(){return (tamanho == 0);}
        bool cheia(){return (tamanho == tamanho_max);}
        int get_tamanho(){return tamanho;}
        int primeiro(){
            if (vazia())
                return -1;
            return dados[inicio];
        }

        bool insere(int valor){
            if (this->cheia())
                return false;
            
            fim = (fim+1) % tamanho_max;
            dados[fim] = valor;

            tamanho++;
            return true;
        }
        int remove(){
            if (this->vazia())
                return -1;

            int num = primeiro();
            inicio = (inicio + 1) % tamanho_max;
            tamanho--;
            return num;
        }
};

int main() {
    FilaSeq fila(5); // Cria uma fila com capacidade para 5 elementos

    // Insere elementos na fila
    fila.insere(1);
    fila.insere(2);
    fila.insere(3);

    // Verifica o estado da fila
    cout << "Tamanho da fila: " << fila.get_tamanho() << endl;
    cout << "Fila esta vazia? " << (fila.vazia() ? "Sim" : "Nao") << endl;

    // Remove elementos da fila e imprime-os
    while (!fila.vazia()) {
        cout << "Removendo: " << fila.remove() << endl;
    }

    // Verifica o estado da fila novamente
    cout << "Tamanho da fila: " << fila.get_tamanho() << endl;
    cout << "Fila esta vazia? " << (fila.vazia() ? "Sim" : "Não") << endl;

    return 0;
}
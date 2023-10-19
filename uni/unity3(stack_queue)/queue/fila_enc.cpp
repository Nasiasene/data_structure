#include <iostream>

using namespace std;

class No{
    No* proximo;
    int valor;

    public:
        No():proximo{nullptr} {}

        No* get_proximo(){return proximo;}
        int get_valor(){return valor;}

        void set_proximo(No* n){proximo = n;}
        void set_valor(int va){valor = va;}
};

class FilaEnc{
    No* inicio;
    No* fim;
    int tamanho;

    public:
        FilaEnc(){
            inicio = nullptr; //index inicial
            fim = nullptr;
            tamanho = 0;
        }

        bool vazia(){return (tamanho == 0);}
        int get_tamanho(){return tamanho;}
        int primeiro(){
            if (vazia())
                return -1;
            return inicio->get_valor();
        }

        bool insere(int valor){
            No *novo_no = new No();
            novo_no->set_valor(valor);
            novo_no->set_proximo(nullptr);

            if (vazia()){ //Inserção em fila vazia
                inicio = novo_no;
                fim = novo_no;
            }
            else {
                fim->set_proximo(novo_no); // liga com a fila
                fim = novo_no; // atualiza o novo fim
            }
            tamanho++;
            return true;
        }

        int remove(){
            if (this->vazia())
                return -1;

            int num = primeiro();
            if(inicio == fim)
                fim = nullptr;

            No *p = inicio;
            inicio = p->get_proximo();
            tamanho--;
            delete p;
            return num;
        }
};

int main() {
    FilaEnc fila; // Cria uma fila

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
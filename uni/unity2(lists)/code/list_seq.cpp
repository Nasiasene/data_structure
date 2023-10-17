#include <iostream>

class ListaSeq {
    private:
        //privado

        int *dados;
        int tamAtual;
        int tamMax;

    public:
        //construtor

        ListaSeq(){
            tamMax = 100;
            tamAtual = 0;
            dados = new int[tamMax];
        };

        //metodos:

        //caracteristicas (gets)
        bool vazia();
        bool cheia();
        int tamanho();
        int elemento(int pos); 
        int posicao(int dado); 

        //modificações (sets)
        bool insere(int pos, int dado);  //Insere um elemento em uma determinada posição.
        int remove(int pos);             //Remove um elemento de uma determinada posição.
        void retorna_lista();
};

bool ListaSeq::vazia() {
    return tamAtual == 0;
}

bool ListaSeq::cheia() {
    return tamAtual == tamMax;
}

int ListaSeq::tamanho() {
    return tamAtual;
}

int ListaSeq::elemento(int pos) {
    int dado;

    if (pos > tamAtual || pos <= 0) {
        return -1;
    }
    dado = dados[pos - 1];
    return dado;
}

int ListaSeq::posicao(int dado) {
    for (int i = 0; i < tamAtual; i++) {
        if (dados[i] == dado) {
            return (i + 1);  // index
        }
    }
    return -1;
}

bool ListaSeq::insere(int pos, int dado) {
    if (cheia() || pos > tamAtual + 1 || pos <= 0) {
        return false;
    }

    for (int i = tamAtual; i >= pos; i--) {
        dados[i] = dados[i - 1];
    }

    dados[pos - 1] = dado;
    tamAtual++;
    return true;
}

int ListaSeq::remove(int pos) {
    int dado;
    if (pos > tamAtual || pos < 1) {
        return -1;
    }

    dado = dados[pos - 1];
    for (int i = pos - 1; i < tamAtual - 1; i++) {
        dados[i] = dados[i + 1];
    }
    tamAtual--;
    return dado;
}

void ListaSeq::retorna_lista(){
    for (int i = 0; i < tamAtual; i++){
        std::cout << dados[i] << " ";
     }
}


void preenche_lista(ListaSeq* l){
    for(int i = 0; i < 100; i++){
        l->insere(i, i);
    }
}


int main(){
    ListaSeq lista;

    if (lista.vazia()){ std::cout << "Lista Vazia!" << std::endl;}
    else{ std::cout << "Lista Nao Vazia!" << std::endl;}

    preenche_lista(&lista);

    if (lista.vazia()){ std::cout << "Lista Vazia!" << std::endl;}
    else{ std::cout << "Lista Nao Vazia!" << std::endl;}

    std::cout << lista.tamanho() << std::endl;

    std::cout << lista.elemento(50) << std::endl;
    lista.remove(50);
    lista.insere(50, 2);

    lista.retorna_lista();
}
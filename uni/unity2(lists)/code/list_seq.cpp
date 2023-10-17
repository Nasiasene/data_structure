#include <iostream>

class ListaSeq {
    private:
        //privado

        int *dados; //vetor de inteiros
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
        int elemento(int pos);  //Retorna o VALOR de um elemento em uma dada posição.
        int posicao(int dado);  //Retorna o INDEX de um elemento com um dado valor.

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
        return -1; //Se o index informado for > tam_lista OU o index < 0: retorne -1
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
    return -1; //Se não achou o valor na lista retorne -1.
}

bool ListaSeq::insere(int pos, int dado) {
    if (cheia() || pos > tamAtual + 1 || pos <= 0) {
        return false; //Se a lista esta cheia OU a index > tam_max OU index < 0: retorne false 
    }

    for (int i = tamAtual; i >= pos; i--) {
        dados[i] = dados[i - 1]; //Passa os dados que estão a frente do index indicado para frente.
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

//Fim Objeto


void preenche_lista(ListaSeq* l){
    for(int i = 0; i < 100; i++){
        l->insere(i, i);
    }
}

int main(){
    ListaSeq lista;

    if (lista.vazia())
        std::cout << "Lista Vazia!" << std::endl;
    else
        std::cout << "Lista Nao Vazia!" << std::endl;

    preenche_lista(&lista);

    if (lista.vazia())
        std::cout << "Lista Vazia!" << std::endl;
    else
        std::cout << "Lista Nao Vazia!" << std::endl;

    std::cout << lista.tamanho() << std::endl;

    std::cout << lista.elemento(50) << std::endl;
    lista.remove(50);
    lista.insere(50, 2);

    lista.retorna_lista();
}
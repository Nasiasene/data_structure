#include <iostream>

using namespace std;


//NÓ
class No{
    private:
        No* proximo;
        int valor;

    public:
        No() : proximo{nullptr} {}

        //gets
        int getValor(){return valor;}
        No* getProximo(){return proximo;} //Retorna um ponteiro para o próximo nó

        //sets
        void setProx(No* p){proximo = p;}
        void setValor(int v){valor = v;}
};



//LISTA
class ListaEnc{
    private:
        No* cabeca;  //Primeiro Nó da lista
        int tamanho; //Tamanho atual da lista

        //SETS
        bool insereInicio(int dado);
        bool insereMeio(int pos, int dado);
        bool insereFim(int dado);
        int removeInicio();
        int removeMeio(int pos);

    public:
        //construct
        ListaEnc() : cabeca(nullptr), tamanho(0) {}

        //gets
        bool vazia(){if(tamanho==0){return true;}
                     else{return false;};}
        int get_tamanho(){return tamanho;}
        int posicao(int dado); //Retorna o INDEX de um dado valor.
        int elemento(int pos); //Retorna o VALOR de um dado index.
        void retorna_lista();

        //sets
        bool insere(int pos, int dado); //Retorna true se conseguir inserir e false caso contrario.
        int remove(int pos);
};

//gets
int ListaEnc::posicao(int dado){   
    int count = 1;
    No* aux = cabeca;

    if(vazia())
        return 0;

    while (aux != nullptr) {
        if (aux->getValor() == dado)
            return count;
        aux = aux->getProximo();
        count++;
    }

    return -1;
}

int ListaEnc::elemento(int pos){
    if (vazia() || pos < 1 || pos > tamanho)
        return -1;

    No* aux = cabeca;
    int count = 1;

    while (count < pos){
        aux = aux->getProximo();
        count++;
    }
    return aux->getValor();
}

void ListaEnc::retorna_lista() {
    No* aux = cabeca;

    while (aux != nullptr) {
        std::cout << aux->getValor() << " ";
        aux = aux->getProximo();
    }
    std::cout << std::endl;
}


//sets (ADICIONAR)
bool ListaEnc::insere(int pos, int dado){
    if ((vazia()) && (pos != 1))
        return false;

    if (pos == 1) 
        return insereInicio(dado);

    else if (pos == tamanho+1)
        return insereFim(dado);
    
    else 
        return insereMeio(pos, dado); 
}

bool ListaEnc::insereInicio(int dado){
    No *novo_no = new No();

    novo_no->setValor(dado);
    novo_no->setProx(cabeca);
    cabeca = novo_no;
    tamanho++;
    return true;
}

bool ListaEnc::insereMeio(int pos, int dado){
    int count = 1;
    No *novo_no = new No();
    novo_no->setValor(dado);

    No* aux = cabeca;
    while ((count < pos-1) && (aux->getProximo() != nullptr)){
        aux = aux->getProximo();
        count++;
    }

    if (aux->getProximo() == nullptr)
        return false;

    novo_no->setProx(aux->getProximo());
    aux->setProx(novo_no);
    tamanho++;
    return true;
}

bool ListaEnc::insereFim(int dado){
    No *novo_no = new No();
    novo_no->setValor(dado); novo_no->setProx(nullptr);

    No* aux = cabeca;
    while(aux->getProximo() != nullptr){
        aux = aux->getProximo();
    }

    novo_no->setProx(nullptr);
    aux->setProx(novo_no);
    tamanho++;
    return true;
}


//sets(REMOVER)
int ListaEnc::remove(int pos) {
    if (vazia())
        return -1; 

    if (pos == 1)
        return removeInicio();

    else
        return removeMeio(pos);
}

int ListaEnc::removeInicio(){
    No* aux = cabeca;
    int dado = aux->getValor();

    cabeca = aux->getProximo();
    tamanho--;

    delete aux;
    return dado;
}

int ListaEnc::removeMeio(int pos){
    No* atual = cabeca;
    No* antecessor = nullptr;
    int count = 1;

    while((count < pos) && (atual->getProximo() != nullptr)){
        antecessor = atual;
        atual = atual->getProximo();
        count++;
    }

    int dado = atual->getValor();

    if (antecessor) 
        antecessor->setProx(atual->getProximo());
    else 
        cabeca = atual->getProximo();

    delete atual;
    tamanho--;

    return dado;
}
//FIM LISTA

void preenche_lista(ListaEnc* l) {
    for (int i = 1; i <= 100; i++) {
        l->insere(i, i);
    }
}

int main(){
    ListaEnc lista;

    if (lista.vazia())
        std::cout << "Lista Vazia!" << std::endl;
    else
        std::cout << "Lista Nao Vazia!" << std::endl;

    preenche_lista(&lista);

    if (lista.vazia())
        std::cout << "Lista Vazia!" << std::endl;
    else
        std::cout << "Lista Nao Vazia!" << std::endl;

    std::cout << lista.get_tamanho() << std::endl;

    std::cout << lista.elemento(50) << std::endl;
    lista.remove(50);
    lista.insere(50, 2);

    lista.retorna_lista();
}
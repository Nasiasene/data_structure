#include <iostream>

using namespace std;


//NÓ
class No{
    private:
        No* proximo;
        No* anterior;
        int valor;

    public:
        No() : proximo{nullptr}, anterior{nullptr} {}

        //gets
        int getValor(){return valor;}
        No* getProximo(){return proximo;} //Retorna um ponteiro para o próximo nó
        No* getAnterior(){return anterior;}

        //sets
        void setProx(No* p){proximo = p;}
        void setAnterior(No* p){anterior = p;}
        void setValor(int v){valor = v;}

};



//LISTA
class ListaDuplaEnc{
    private:
        No* cabeca;  //Primeiro Nó da lista
        No* cauda;   //Último Nó da lista
        int tamanho; //Tamanho atual da lista

        //SETS
        bool insereInicio(int dado);
        bool insereMeio(int pos, int dado);
        bool insereFim(int dado);
        int removeInicio();
        int removeInicioUnitaria();
        int removeMeio(int pos);
        int removeFim();

    public:
        //construct
        ListaDuplaEnc() : cabeca(nullptr), cauda{nullptr}, tamanho(0) {}

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
int ListaDuplaEnc::posicao(int dado){   
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

int ListaDuplaEnc::elemento(int pos){
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

void ListaDuplaEnc::retorna_lista() {
    No* aux = cabeca;

    while (aux != nullptr) {
        std::cout << aux->getValor() << " ";
        aux = aux->getProximo();
    }
    std::cout << std::endl;
}


//sets (ADICIONAR)
bool ListaDuplaEnc::insere(int pos, int dado){
    if ((vazia()) && (pos != 1))
        return false;

    if (pos == 1) 
        return insereInicio(dado);

    else if (pos == tamanho+1)
        return insereFim(dado);
    
    else 
        return insereMeio(pos, dado); 
}

bool ListaDuplaEnc::insereInicio(int dado){
    No *novo_no = new No();
    novo_no->setValor(dado);
    novo_no->setProx(cabeca);

    novo_no->setAnterior(nullptr);
    if (vazia())
        cauda = novo_no;
    else
        cabeca->setAnterior(novo_no);

    cabeca = novo_no;
    tamanho++;
    return true;
}

bool ListaDuplaEnc::insereMeio(int pos, int dado){
    int count = 1;
    No *novo_no = new No();
    novo_no->setValor(dado);

    No* aux = cabeca;
    while ((count < pos-1) && (aux->getProximo() != nullptr)){
        aux = aux->getProximo();
        count++;
    }

    if (aux == nullptr)
        return false;

    novo_no->setAnterior(aux);
    novo_no->setProx(aux->getProximo());
    aux->getProximo()->setAnterior(novo_no);
    aux->setProx(novo_no);
    tamanho++;
    return true;
}

bool ListaDuplaEnc::insereFim(int dado){
    No *novo_no = new No();
    novo_no->setValor(dado);

    No* aux = cauda;

    novo_no->setProx(nullptr);
    aux->setProx(novo_no);
    novo_no->setAnterior(cauda);
    cauda->setProx(novo_no);
    cauda = novo_no;
    tamanho++;
    return true;
}


//sets(REMOVER)
int ListaDuplaEnc::remove(int pos) {
    if (vazia())
        return 0; 

    if (pos == 1 && tamanho == 1)
        return removeInicioUnitaria();

    else if (pos == 1)
        return removeInicio();

    else if (pos == tamanho)
        return removeFim();

    else
        return removeMeio(pos);
}

int ListaDuplaEnc::removeInicioUnitaria(){
    int dado = cabeca->getValor();
    cabeca = nullptr;
    cauda = nullptr;
    tamanho--;
    return dado;
}

int ListaDuplaEnc::removeInicio(){
    No* aux = cabeca;
    int dado = aux->getValor();

    cabeca = aux->getProximo();
    aux->getProximo()->setAnterior(nullptr);
    tamanho--;

    delete aux;
    return dado;
}

int ListaDuplaEnc::removeFim(){
    No* aux = cauda;
    int dado = aux->getValor();

    cauda->getAnterior()->setProx(nullptr);
    cauda = cauda->getAnterior();
    tamanho--;

    delete aux;
    return dado;
}

int ListaDuplaEnc::removeMeio(int pos){
    No* aux = cabeca;
    int count = 1;

    while((count < pos-1) && (aux != nullptr)){
        aux = aux->getProximo();
        count++;
    }

    if (aux == nullptr)
        return -1;
    
    int dado = aux->getValor();
    aux->getAnterior()->setProx(aux->getProximo());
    aux->getProximo()->setAnterior(aux->getAnterior());

    tamanho--;
    delete aux;
    return dado;
}
//FIM LISTA

void preenche_lista(ListaDuplaEnc* l) {
    for (int i = 1; i <= 100; i++) {
        l->insere(i, i);
    }
}

int main(){
    ListaDuplaEnc lista;

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
    lista.remove(100);
    lista.remove(50);
    lista.remove(0);
    lista.insere(50, 2);

    lista.retorna_lista();
}
#include <iostream>

using namespace std;

class No{
    private:
        //atributos
        No* proximo;
        int valor;

    public:
        //construct
        No(){
            proximo = nullptr;
        }

        //gets
        int getValor(){return valor;}
        No* getProximo(){return proximo;}

        //sets
        void setProx(No* p){proximo = p;}
        void setValor(int v){valor = v;}
};

class ListaEnc{
    private:
        //atributos
        No* cabeca;
        int tamanho;

    public:
        //construct
        ListaEnc(){
            tamanho = 0;
            cabeca->setProx(nullptr);
        }

        //gets
        bool vazia(){if(tamanho==0){return true;}
                     else{return false;};}
        int tamanho(){return tamanho;}
        int posicao(int dado);
        int elemento(int pos);

        //sets
        void insereInicio(int dado);
        void insereMeio(int pos, int dado);
        void insereFim(int dado);
        void insere(int pos, int dado);
        void modifica(int pos, int dado);
        int removeInicio();
        

};


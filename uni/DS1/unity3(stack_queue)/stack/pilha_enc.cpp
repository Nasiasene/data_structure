#include <iostream>

using namespace std;

class No{
    int valor;
    No* proximo;

    public:
        No(){ proximo = nullptr;}

        //GETS
        int get_valor(){return valor;}
        No* get_proximo(){return proximo;}

        //SETS
        void set_valor(int v){valor = v;}
        void set_proximo(No* p){proximo = p;}
};

class PilhaEnc{
    No* topo;
    int tamanho;

    public:
        PilhaEnc() : topo{nullptr}, tamanho{0} {}

        //GETS
        bool vazia(){return(tamanho==0);}
        int get_tamanho(){return tamanho;}
        int top(){((this->vazia()) ? -1 : topo->get_valor());}

        //SETS
        bool push(int valor){
            No *novo_no = new No();
            novo_no->set_valor(valor);

            novo_no->set_proximo(topo);

            topo = novo_no;
            tamanho++;
            return true;
        }

        int pop(){
            if(this->vazia())
                return -1;

            No *p = topo;
            int valor = p->get_valor();

            topo = p->get_proximo();
            tamanho--;

            delete p;
            return valor;
        }
};
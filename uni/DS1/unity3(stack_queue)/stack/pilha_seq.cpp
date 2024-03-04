#include <iostream>

using namespace std;

class PilhaSeq{
    int tam_max = 0;
    int *dados;
    int topo; //tamanho atual.

    public:
        PilhaSeq(int t){
            tam_max = t;
            dados = new int[tam_max];
            topo = -1;
        }

        //GETS
        bool vazia(){return (topo == -1);}
        bool cheia(){return (topo == (tam_max-1));}
        int tamanho(){return topo+1;}
        int top(){
            if (this->vazia())
                return -1;
            return dados[topo];
        }

        //SETS
        bool push(int valor);  //ADICONA UM ELEMENTO NO TOPO DA PILHA.
        int pop();             //RETORNA O ELEMENTO DO TOPO DA PILHA E O EXCLUI.

        //extra
        void preenche_pilha(){
            for(int i = 0; i < tam_max; i++){
                this->push(i);
            }
        }

        void printa_pilha(){
            for(int i = 0; i <= topo; i++){
                cout << dados[i];
            }
            if (vazia())
                cout << -1;
        }

        void clear_pilha(){
            for(int i = 0; i <= tam_max; i++){
                this->pop();
            }
        }
};

bool PilhaSeq::push(int valor){
    if (this->cheia())
        return false;
    
    topo++;
    dados[topo] = valor;
    return true;
}

int PilhaSeq::pop(){
    if (this->vazia())
        return -1;
    
    int valor = dados[topo];
    topo--;
    return valor;
}

int main(){
    PilhaSeq pilha(10);

    pilha.preenche_pilha();
    pilha.printa_pilha();

    cout << endl << pilha.pop() << endl;

    pilha.printa_pilha();
    cout << endl;
    pilha.clear_pilha();

    pilha.printa_pilha();
}
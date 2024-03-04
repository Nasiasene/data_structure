//Vetor é um array dinamico, que pode mudar de tamanho.
#include <iostream>
#include <vector>

using namespace std;

void print_vec(vector<int> v){
    for (int i = 0; i < v.size(); i++){ //Para iterar o vetor. 
        cout << v[i] << " ";
    }
    cout << endl;
    for (auto i = v.begin(); i != v.end(); ++i){ //itera o vetor também.
        cout << *i << " ";
    }
}

int main(){
    //vector<type_data> name_vector;
    vector<int> vec1 = {1, 2, 3, 4};

    cout << "-------------\n" << vec1[1] << endl << vec1.front() << endl << vec1.back() << endl << vec1.size() << "\n-------------\n";

    vec1.push_back(9); //Adiciona um elemento no final do vetor.

    cout << vec1.back() << endl << vec1.size() << "\n-------------\n";

    vec1.pop_back(); //Remove o ultimo elemento do vetor mas NÃO o RETORNA.

    cout << vec1.back() << endl << vec1.size() << "\n-------------\n";

    //Para Adicionar valores a index determinados de um vetor, é necessário determinar a posição de memória em que você deseja adicionar, além do valor desejado.
    vec1.insert(vec1.begin(), 0); //Adiciono o valor zero ao inicio da lista. // .begin() retorna a posição de memoria do primeiro elemeno de um vetor.
    vec1.insert(vec1.end() -1, 3); //Adiciono o valor 3 no penúltimo index da lista. // .end() retorna a posição de memoria do último elemeno de um vetor.

    vec1[2] = 0; // posso alterar desta forma tambem;

    print_vec(vec1);
}

//O vetor tem uma capacidade especifica de elemntos no qual ele pode ter, entretanto, essa capacidade é DOBRADA caso a quantidade de elementos seja suficiente.
//A capacidade de elementos assumvalores: 2**n.  (0, 1, 2, 4, 8, 16, 32, 64...)
//Caso a quantidade de elementos seja maior que a capacdade, o valor da capacidade irá dobrar.
//LEMBRE-SE, isso tudo ocorre em tempo de EXECUÇÃO.
//existe a função vec.shrink_to_fit() que fará com que o vetor tenha a sua CAPACIDADE = TAMANHO.
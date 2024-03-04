#include <iostream>
#include <vector>
#include <string>

using namespace std;

class HashTable{
    int table_size;
    vector<pair<string, int>> table; //um vetor cujo os elementos são lstas que contem elementos com valores strings(nesse caso será a key) e inteiros.

    int hashFunction(const string& key){ //retorna o valor hash de uma key, no caso, string.
        int v_hash = 0;
        for (char c : key){
            v_hash += c;
        }
        return v_hash % table_size; //valor da função hash(valor hash), ou index do elemento na tabela hash.
    }

    public:
        HashTable(int tam){
            table_size = int(tam*1.25);
            table.resize(table_size); //Define o tamanho da tabela hash.
        } 

        void insert(const string& key, int value){
            int index = hashFunction(key);
            //Tramento de colisões:
            while (table[index].first != ""){
                index = (index+1)%table_size; //Função de Reespalhamento
            }
            table[index] = make_pair(key, value);
        }

        int search(const string& key){
            int index = hashFunction(key);

            // Procura o valor, considerando o tratamento de colisões por incremento circular
            while (table[index].first != ""){
                if(table[index].first == key)
                    return table[index].second;
                index = (index+1) & table_size;
            }
            return -1; //caso o valor não seja encontrado
        }    
};

int main(){
    HashTable hashTable(10);

    // Inserindo pares chave-valor
    hashTable.insert("apple", 5);
    hashTable.insert("banana", 10);
    hashTable.insert("cherry", 15);

    // Procurando valores por chave
    std::cout << "Value for 'apple': " << hashTable.search("apple") << std::endl;
    std::cout << "Value for 'banana': " << hashTable.search("banana") << std::endl;
    std::cout << "Value for 'cherry': " << hashTable.search("cherry") << std::endl;
    std::cout << "Value for 'grape': " << hashTable.search("grape") << std::endl; //Não achou

    return 0;
}
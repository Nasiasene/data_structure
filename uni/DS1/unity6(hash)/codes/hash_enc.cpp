#include <iostream>
#include <vector>
#include <list>
#include <string>

using namespace std;

class HashTable{
    int table_size;
    vector<list<pair<string, int>>> table; //um vetor cujo os elementos são lstas que contem elementos com valores strings(nesse caso será a key) e inteiros.

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
            table[index].push_back(std::make_pair(key, value)); //Lembre-se neste caso cada elemento da tabela hash é um vetor.
        }

        int search(const string& key){
            int index = hashFunction(key);

            for (auto& i : table[index]){ //como essa tabela está preparada para espalhar valores de forma encadeada, este for irá iterar cada lista de elementos da tabela hash.
                if(i.first == key)        // caso o primeiro elemento de um dos valores da lista tenha o valor da key igual a informada pela função.
                    return i.second; 
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
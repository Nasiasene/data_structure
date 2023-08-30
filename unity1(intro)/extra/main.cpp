#include <iostream>
#include <string>

using namespace std;

void test(std::string str, int x){
    std::cout << "\n\nFuncao teste.\nValor1: " << str << "\nValor2: " << x << "\n\n";
}

struct Pessoa{

    Pessoa() {
        idade = 20;
        altura = 1.75f;
        nome = "davi";
    } //construct, uma funcao sem tipo e retorno, responsável por setar os valores inciais de variaveis.
      //Obs: deve ter o mesmo nome da classe/struct e termina com ;

    int idade;
    float altura;
    std::string nome;

};

class PessoaClass{
    //Atributos
    private:
        string nome;
        int idade, ano;

    //Métodos.
    public:

    //Construtor.
    //Executado ao iniciar a classe.
    //Obs tem o mesmo nome da classe e recebe como parametro os atributos da classe.
    //A o criar um objeto da classe, poderei passar como parametros ao inicializa-la os atributos dela, o construtor será responsável por setar os atributos.
    PessoaClass(string _nome = "", int _idade = 0, int _ano = 0){
        nome = _nome;
        idade = _idade;
        ano = _ano;
    };

    //gets e sets (getNome, setNome, getIdade, setIdade, getAno, setAno).
    void mostraNum(int i);       //protótipo
    void setNome( string nomee); 
    void setIdade(int _idade);
    int getIdade();
    void setAno(int _ano);
    int getAno();

    string getNome() {
        return nome;
    }
};
void PessoaClass::mostraNum(int i) { //definindo a funcao depois de criar a classe é melhor
    if (i == 0){
        cout << "ZERO" << endl;
    }
    else{
        cout << "NUM " << i << endl;
    }
}

void PessoaClass::setNome(string nomee){
    nome = nomee;
}
void PessoaClass::setIdade(int _idade){
    idade = _idade;
}
void PessoaClass::setAno(int _ano){
    ano = _ano;
}
int PessoaClass::getIdade(){
    return idade;
}
int PessoaClass::getAno(){
    return ano;
}


int main(){
    int i=0;
    float f=0.0f;
    double d=0.0;

    bool b = false;
    char c = 'c';
    char str[10] = "ola teste";
    std::string str2 = "teste";

    std::cout << i << "\n" << b << c << f << d;
    std::cout << "\nOla Mundo\n" << str << "\n\n" << str2;
    str2 = "Posso mudar desta forma";
    str2 += ", nao preciso alocar memoria !";
    std::cout << "\n" << str2;
    //cout = console output.

    int count = 0;
    do{
        if (count == 0){
        cout << "\n\nIgual a zero.";
        }
        else if (count ==1){
             std::cout << "\nIgual a um.";
        }
        else {
             std::cout << "\nIgual a dois.\n";
        }
        count++;
    } while(count < 3);

    std::cout << "Digite um valor para i: ";
    std::cin >> i; 
    //cin = console output (muda sinal da seta >>).
    std::cout << "Valor de i: " << i;

    while (count<=5){
        std::cout << count << "\n";
        count +=1;
    }

    int listaInt[10];
    for (int i = 0; i <10; i++){
        listaInt[i] = 0;
    }

    std::cout << listaInt[0] << listaInt[6] << listaInt[9] << "\n" << "Digite uma str: ";

    std::string str3;
    cin >> str3;
    test(str3, i);

    Pessoa p;
    std::cout << p.altura << "\n" << p.idade << "\n" << p.nome;


//  Class  //
    PessoaClass pessoa;
    //pessoa.nome = "Davi Nasiasene";
    //cout << "\n\n" << pessoa.nome << endl;
    //Só posso setar as variaveis dessa forma caso elas sejam publicas.
    cout << "Test endl" << endl;

    pessoa.mostraNum(0);
    pessoa.mostraNum(2);

    string name;
    cin >> name;
    pessoa.setNome(name);
    pessoa.getNome();



    PessoaClass pessoa2 = PessoaClass("Nasiasene", 10);
    cout << "\n\n\nNew Test:\n" << pessoa2.getNome() << endl << pessoa2.getIdade() << endl << pessoa2.getAno() << endl;
    int ano = 2023;
    pessoa2.setAno(ano);
    cout << pessoa2.getAno();


    return 0;
}
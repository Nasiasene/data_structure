class Hash_table:
    def __init__(self, s):
        self.size = int(s*1.25) #definindo o tamanho da tabela
        self.T = [[] for _ in range(self.size)] #lista de elementos, em caso de colisões, usarenmos o método de encadeamento.
     
    def __hash_str(self, key_str): # Calcula valor hash para uma string
        num = 0
        for c in key_str:
            num += ord(c)
        return num
    
    def __hash(self, key_str):
        if type(key_str) == str:
            key_str = self.__hash_str(key_str)
        return key_str % self.size
    
    def insert(self, key, value):
        pos = self.__hash(key)
        self.T[pos].append(value)
    
    def get(self, key):
        pos = self.__hash(key)
        L = self.T[pos]
        for value in L:
            if(value.matricula == key):
                return value
        return None
            
    def print(self):
        print("{")
        for i in range(self.size):
            alunos = self.T[i]
            _str = ""
            for aluno in alunos:
                _str += aluno.to_string() + " "
            print("[" + _str + "]")
        
        print("}")


class Aluno:
    def __init__(self, nome, matricula):
        self.nome = nome
        self.matricula = matricula
   
    def to_string(self):
        return self.nome + " - " + str(self.matricula)

a1 = Aluno("Maria", 12)
a2 = Aluno("João", 6)
a3 = Aluno("José", 24)
a4 = Aluno("Lucas", 36)
a5 = Aluno("Matheus", 3)
a6 = Aluno("Simão", 7)


ht = Hash_table(10)
ht.insert(a1.nome, a1)
ht.insert(a2.nome, a2)
ht.insert(a3.nome, a3)
ht.insert(a4.nome, a4)
ht.insert(a5.nome, a5)
ht.insert(a6.nome, a6)

ht.print()
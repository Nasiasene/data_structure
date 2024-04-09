class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [[] for _ in range(size)]

    def hash_function(self, key):
        return key % self.size

    def insert(self, key, value):
        index = self.hash_function(key)
        self.table[index].append((key, value))

    def search(self, key):
        index = self.hash_function(key)
        for k, v in self.table[index]:
            if k == key:
                return v
        return None

    def delete(self, key):
        index = self.hash_function(key)
        for i, (k, v) in enumerate(self.table[index]):
            if k == key:
                del self.table[index][i]
                return
        raise KeyError(f"Key '{key}' not found")

# Exemplo de uso
hash_table = HashTable(10)
hash_table.insert(5, "Apple")
hash_table.insert(15, "Banana")
hash_table.insert(25, "Cherry")

print(hash_table.search(5))  
print(hash_table.search(15))  
print(hash_table.search(25))  

hash_table.delete(15)
print(hash_table.search(15))  

class HashTable:
    def __init__(self, size):
        self.size = size
        self.table = [None] * size

    def hash_function(self, key):
        return key % self.size

    def linear_probe(self, index, i):
        return (index + i) % self.size

    def quadratic_probe(self, index, i):
        return (index + i**2) % self.size

    def double_hashing(self, index, i, key):
        return (index + i * self.hash_function(key)) % self.size

    def insert(self, key, value, probing="linear"):
        index = self.hash_function(key)
        i = 0
        while i < self.size:
            if self.table[index] is None:
                self.table[index] = (key, value)
                return
            if probing == "linear":
                index = self.linear_probe(index, i)
            elif probing == "quadratic":
                index = self.quadratic_probe(index, i)
            elif probing == "double":
                index = self.double_hashing(index, i, key)
            i += 1
        raise ValueError("Table is full")

    def search(self, key, probing="linear"):
        index = self.hash_function(key)
        i = 0
        while i < self.size:
            if self.table[index] is None:
                return None
            if self.table[index][0] == key:
                return self.table[index][1]
            if probing == "linear":
                index = self.linear_probe(index, i)
            elif probing == "quadratic":
                index = self.quadratic_probe(index, i)
            elif probing == "double":
                index = self.double_hashing(index, i, key)
            i += 1
        return None

# Exemplo de uso
hash_table = HashTable(10)

# Inserção usando sondagem linear
hash_table.insert(5, "Apple", probing="linear")
hash_table.insert(15, "Banana", probing="linear")
hash_table.insert(25, "Cherry", probing="linear")

print(hash_table.search(5, probing="linear"))  # Output: Apple
print(hash_table.search(15, probing="linear"))  # Output: Banana
print(hash_table.search(25, probing="linear"))  # Output: Cherry

# Inserção usando sondagem quadrática
hash_table.insert(6, "Grape", probing="quadratic")

print(hash_table.search(6, probing="quadratic"))  # Output: Grape

# Inserção usando dispersão dupla
hash_table.insert(16, "Peach", probing="double")

print(hash_table.search(16, probing="double"))  # Output: Peach

import time

def insertion_sort(lista):
    for i in range(len(lista)):
        valor_atual = lista[i]
        j = i
        while (j>0) and (lista[j-1] > valor_atual):
            lista[j] = lista[j-1]
            j = j-1
        lista[j] = valor_atual



# Medir o tempo para ordenar lista1
lista1 = []
with open("uni/v_extra(sorting)/data/num.1000.1.in", 'r') as file:
    for linha in file:
        lista1.append(int(linha.strip()))

start_time = time.time()
insertion_sort(lista1)
end_time = time.time()
elapsed_time = end_time - start_time
print("Tempo para ordenar lista1: {:.6f} segundos".format(elapsed_time))


# Medir o tempo para ordenar lista2
lista2 = []
with open("uni/v_extra(sorting)/data/num.10000.2.in", 'r') as file:
    for linha in file:
        lista2.append(int(linha.strip()))

start_time = time.time()
insertion_sort(lista2)
end_time = time.time()
elapsed_time = end_time - start_time
print("Tempo para ordenar lista2: {:.6f} segundos".format(elapsed_time))


# Medir o tempo para ordenar lista3
lista3 = []
with open("uni/v_extra(sorting)/data/num.100000.3.in", 'r') as file:
    for linha in file:
        lista3.append(int(linha.strip()))

start_time = time.time()
insertion_sort(lista3)
end_time = time.time()
elapsed_time = end_time - start_time
print("Tempo para ordenar lista3: {:.6f} segundos".format(elapsed_time))


'''
Tempo para ordenar lista1: 0.045583 segundos
Tempo para ordenar lista2: 3.675838 segundos
Tempo para ordenar lista3: 456.458161 segundos
'''
import time

def merge(ini, meio, post, lista):
    E = lista[ini:meio]
    D = lista[meio:post]

    i, j, k = 0, 0, ini

    while i < len(E) and j < len(D):
        if E[i] < D[j]:
            lista[k] = E[i]
            i += 1
        else:
            lista[k] = D[j]
            j += 1
        k += 1

    while i < len(E):
        lista[k] = E[i]
        i += 1
        k += 1

    while j < len(D):
        lista[k] = D[j]
        j += 1
        k += 1

def merge_sort(lista):
    def merge_sort_recursivo(ini, post):
        if post - ini > 1:
            meio = (ini + post) // 2
            merge_sort_recursivo(ini, meio)
            merge_sort_recursivo(meio, post)
            merge(ini, meio, post, lista)

    merge_sort_recursivo(0, len(lista))



# Medir o tempo para ordenar lista1
lista1 = []
with open("uni/v_extra(sorting)/data/num.1000.1.in", 'r') as file:
    for linha in file:
        lista1.append(int(linha.strip()))

start_time = time.time()
merge_sort(lista1)
end_time = time.time()
elapsed_time = end_time - start_time
print("Tempo para ordenar lista1: {:.6f} segundos".format(elapsed_time))

# Medir o tempo para ordenar lista2
lista2 = []
with open("uni/v_extra(sorting)/data/num.10000.2.in", 'r') as file:
    for linha in file:
        lista2.append(int(linha.strip()))

start_time = time.time()
merge_sort(lista2)
end_time = time.time()
elapsed_time = end_time - start_time
print("Tempo para ordenar lista2: {:.6f} segundos".format(elapsed_time))

# Medir o tempo para ordenar lista3
lista3 = []
with open("uni/v_extra(sorting)/data/num.100000.3.in", 'r') as file:
    for linha in file:
        lista3.append(int(linha.strip()))

start_time = time.time()
merge_sort(lista3)
end_time = time.time()
elapsed_time = end_time - start_time
print("Tempo para ordenar lista3: {:.6f} segundos".format(elapsed_time))


'''
Tempo para ordenar lista1: 0.002000 segundos
Tempo para ordenar lista2: 0.023999 segundos
Tempo para ordenar lista3: 0.392688 segundos
'''
import time

def selection_sort(list):
    for i in range (len(list)):
        min = i #SELECIONA O Primeiro elemento e considera-o menor

        for  j in range (i + 1, len(list)): #range da lista para alem da parte ja ordenada.
            if list[j] < list[min]: #Troca de posi
                min = j
                
            aux = list[min]
            list[min] = list[i]
            list[i] = aux

    

# Medir o tempo para ordenar lista1
lista1 = []
with open("uni/v_extra(sorting)/data/num.1000.1.in", 'r') as file:
    for linha in file:
        lista1.append(int(linha.strip()))

start_time = time.time()
selection_sort(lista1)
end_time = time.time()
elapsed_time = end_time - start_time
print("Tempo para ordenar lista1: {:.6f} segundos".format(elapsed_time))


# Medir o tempo para ordenar lista2
lista2 = []
with open("uni/v_extra(sorting)/data/num.10000.2.in", 'r') as file:
    for linha in file:
        lista2.append(int(linha.strip()))

start_time = time.time()
selection_sort(lista2)
end_time = time.time()
elapsed_time = end_time - start_time
print("Tempo para ordenar lista2: {:.6f} segundos".format(elapsed_time))


# Medir o tempo para ordenar lista3
lista3 = []
with open("uni/v_extra(sorting)/data/num.100000.3.in", 'r') as file:
    for linha in file:
        lista3.append(int(linha.strip()))

start_time = time.time()
selection_sort(lista3)
end_time = time.time()
elapsed_time = end_time - start_time
print("Tempo para ordenar lista3: {:.6f} segundos".format(elapsed_time))


'''
Tempo para ordenar lista1: 0.088122 segundos
Tempo para ordenar lista2: 8.228478 segundos
Tempo para ordenar lista3: 1245.874920 segundos
'''
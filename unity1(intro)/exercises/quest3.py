import random as rd

def busca_bi_iterativa(lista, num):
    media_idx = len(lista)/2
    if media_idx % 2 == 0:
        print(media_idx)
        valor_medio = lista[media_idx]
    else:
        media_idx = int(media_idx)
        print(media_idx)
        valor_medio = (lista[media_idx] + lista[media_idx + 1])/2

    if num == valor_medio:
        return media_idx
    elif num > valor_medio:
        for media_idx in range(len(lista)):
            if num == lista[media_idx]:
                 return media_idx
            else:
                 media_idx +=1
    else:
        for i in range(media_idx):
            if num == lista[media_idx]:
                 return i

tam_aleatório = rd.randint(0, 20)
lista_aleatoria = [rd.randint(0, 50) for i in range(tam_aleatório)]
lista_aleatoria.sort()

valor_aleatorio = rd.choice(lista_aleatoria)
print(lista_aleatoria, valor_aleatorio, len(lista_aleatoria))
print(busca_bi_iterativa(lista_aleatoria, valor_aleatorio))

import queue

class Graph:
    def __init__(self, n):
        self.num_vertices = n
        self.matrix = [[0 for _ in range(n)] for _ in range(n)]
        self.list = [[] for _ in range(n)]
        

    def print(self):
        print(self.matrix)
        print(self.list)
        
        
    def bfs(self, source):
        dist = [-1 for _ in range(self.num_vertices)]
        ant = [-1 for _ in range(self.num_vertices)]
        isVisited = [False for _ in range(self.num_vertices)]
        Q = queue.Queue()
        Q.put(source)
        isVisited[source] = True
        dist[source] = 0
        
        while Q.empty() != True:
            p = Q.get()
            print("Vertice: " + str(p))
            
            for v in self.list[p]:
                if isVisited[v] == False:
                    dist[v] = dist[p] + 1
                    ant[v] = p
                    Q.put(v)
                    isVisited[v] = True
        
        return dist, ant
    
def load_from(fileName):
    f = open(fileName, 'r')
    n = int(f.readline())
    
    g = Graph(n)
    
    l = 0
    for line in f:
        #print(line)
        #print("ola")
        line.strip()
        numeros = line.split("\t")
        c = 0
        for i in numeros:
            if(c == g.num_vertices):
                break
            #print(i)
            g.matrix[l][c] = int(i)
            if(g.matrix[l][c] > 0):
                g.list[l].append(c)
            
            c += 1
        l += 1
    return g

x = int(input("Digite o pcv(4, 10, 50, 177): "))
gr = load_from(f"uni/unity5(graphs)/codes/py/instncias_grafo/pcv{x}.txt")
gr.print()

dist, ant = gr.bfs(3)
print("\n")
print(dist)
print(ant)
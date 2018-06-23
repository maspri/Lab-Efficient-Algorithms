import sys


def bellman_ford(start):

    dist = [float("Inf")] * n
    dist[start] = 0

    for i in range(n - 1):
        for u, v, w in edges:
            if dist[v] > dist[u] + w:
                dist[v] = dist[u] + w

    for u, v, w in edges:
        if dist[v] > dist[u] + w:
            print("possible")
            return
    print("not possible")


data = sys.stdin.read().split("\n")
l = 0
tests = int(data[l])
l += 1
for test in range(tests):
    n, m = map(int, data[l].split())
    l += 1
    edges = []
    for i in range(m):
        u, v, w = map(int, data[l].split())
        edges.append([u, v, w])
        l += 1
    bellman_ford(0)




"""
def build_graph(n, m, l):
    graph = {}

    for i in range(0, n):
        graph[i] = {}

    for i in range(0, m):
        a, b, w = map(int, data[l].split())
        l += 1
        graph[a][b] = w

    return graph, l

def bellman_ford():

    for i in range(n-1):
        for u in graph:
            for v in graph[u]:
                if dist[v] > dist[u] + graph[u][v]:
                    dist[v] = dist[u] + graph[u][v]
                    pre[v] = u

    for u in graph:
        for v in graph[u]:
            if dist[v] > dist[u] + graph[u][v]:
                print("possible")
                return
    print("not possible")




    for i in range(1, n):
        dist[i] = float('Inf')
        pre[i] = None
    bellman_ford()
"""

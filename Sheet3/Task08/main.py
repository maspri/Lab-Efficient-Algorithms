import sys

def bfs_list_fifo(graph, start):

    visited = [0] * N
    visited[start] = 1
    d = [0] * N
    bfs_fifo = [start]

    while bfs_fifo:
        u = bfs_fifo.pop()
        # u is current vertex
        u_adjacent = graph[u]
        for v in u_adjacent:
            if not visited[v]:
                # d[u] contains shortest path to u
                d[v] = d[u] + 1
                bfs_fifo.append(v)
                visited[v] = 1
    return d


def build_list(n, m, l):
    graph = {}

    for i in range(0, n):
        graph[i] = set()

    for i in range(0, m):
        a, b = map(int, data[l].split())
        l += 1
        graph[a].add(b)
        graph[b].add(a)

    return graph, l


data = sys.stdin.read().split("\n")
l = 0
tests = int(data[l])
l += 1
for test in range(tests):
    N = int(data[l])
    l += 1
    E = int(data[l])
    l += 1

    graph, l = build_list(N, E, l)
    bc, k = map(int, data[l].split())
    l += 1

    paths = [bfs_list_fifo(graph, bc), bfs_list_fifo(graph, k)]

    longest_shortest_path = max([sum(x) for x in zip(*paths)])
    print("Case " + str(test + 1) + ": " + str(longest_shortest_path))



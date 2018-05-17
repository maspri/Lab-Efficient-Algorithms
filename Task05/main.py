
def dfs_list(graph, start):
    prev_color = color[start]

    for next in graph[start]:
        next_color = color[next]
        if next_color == -1:
            color[next] = 1 - prev_color
            if not dfs_list(graph, next):
                return False
        elif prev_color == next_color:
            return False

    return True


def bfs_matrix(graph, start):
    bfs_queue = [start]
    while bfs_queue:
        u = bfs_queue.pop()
        if graph[u][u] == 1:
            return False
        for v in range(n):
            if graph[u][v] == 1 and color[v] == -1:
                color[v] = 1 - color[u]
                bfs_queue.append(v)
            elif graph[u][v] == 1 and color[u] == color[v]:
                return False
    return True


def build_matrix(n,m):
    graph = [[0 for c in range(n)] for r in range(n)]
    for i in range(m):
        a, b = map(int, input().split())
        graph[a][b] = 1
        graph[b][a] = 1
    return graph


def build_list(n, m):
    graph = {}
    for i in range(0, n):
        graph[i] = set()
        color[i] = -1
    for i in range(0, m):
        a, b = map(int, input().split())
        graph[a].add(b)
        graph[b].add(a)
    return graph


while(1):
    try:
        n, m = map(int, input().split())
    except EOFError:
        break
    graph = build_matrix(n, m)

    color = [-1] * n

    color[0] = 1

    if bfs_matrix(graph, 0):
        print('bipartite')
    else:
        print('not bipartite')

    try:
        blank = input()
        print(blank)
    except EOFError:
        break



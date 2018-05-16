def dfs(graph, start):
    prev_color = color[start]

    for next in graph[start]:

        if color[next] == 0:
            if prev_color == 1:
                color[next] = 2
            else:
                color[next] = 1
            if not dfs(graph, next):
                return False
        elif color[start] == color[next]:
            return False

    return True


while(1):

    try:
        n, m = map(int, input().split())
    except:
        break

    graph = {}
    color = {}

    for i in range(0, n):
        graph[i] = set()
        color[i] = 0
    for i in range(0, m):
        a, b = map(int, input().split())
        graph[a].add(b)
        graph[b].add(a)

    color[0] = 1
    if dfs(graph,0):
        print('bipartite')
    else:
        print('not bipartite')
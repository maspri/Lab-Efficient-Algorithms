from array import *
import sys

# Algorithm idea: we want to check if a graph can be separated in 2 independent vertex sets
# this is achieved by coloring all nodes alternating with 2 colors. These colors are interpreted as those sets
# If the same color is connected the set is not independent and the graph not bipartite
# run time should be O(|V| + |E|) because of the BFS


def bfs_list_fifo(graph, start):

    bfs_fifo = [start]
    # dfs till everything was checked-
    while bfs_fifo:
        u = bfs_fifo.pop()
        # u is current vertex
        # save color + adjacency list
        u_color,  u_adjacent = color[u], graph[u]
        # check 2 coloring property
        for v in u_adjacent:
            v_color = color[v]
            # if uncolored
            if v_color == -1:
                # opposite color
                color[v] = 1 - u_color
                bfs_fifo.append(v)
            # same color means not bipartite
            elif v_color == u_color:
                return False

    return True


def build_list(n, m, l):
    graph = {}
    # sets for efficiency
    for i in range(0, n):
        graph[i] = set()
    # interpret graph as directed, because if edge (a,b) has a legit color combo,
    # also the edge (b,a) has one
    # there fore only add edge (a,b) and ignore edge (b,a)
    for i in range(0, m):
        a, b = map(int, data[l].split())
        l += 1
        graph[a].add(b)

    return graph, l

# sys.stdin becauce input() is slow...


data = sys.stdin.read().split("\n")
l = 0
while l < len(data):
    n, m = map(int, data[l].split())
    l += 1
    # -1: uncolored , 0: blue , 1: red
    color = array('i', [-1] * n)
    color[0] = 1

    graph, l = build_list(n, m, l)
    if bfs_list_fifo(graph, 0):
        print('bipartite')
    else:
        print('not bipartite')

    # this is to fix the weird input/output empty line format
    if l == len(data):
        break
    else:
        print("")
        l += 1
import random

# random.seed()
# p = 0.01  #probability of edge insertion
# numVertices = random.randint(1, 10000)
# numEdges = 0
# graph = [[0 for j in range(numVertices)] for i in range(numVertices)]
# for v in range(0, numVertices):
#     for w in range(v+1, numVertices):
#         if v != w and random.random() < p:
#             graph[v][w] = 1
#             numEdges += 1
#
# listOne = []
# listTwo = []
#
# for i in range(1, numVertices+1):
#     listOne.append(i)
#     listTwo.append(i)
#
# random.shuffle(listOne)
# random.shuffle(listTwo)
#
# # write the graph to file but in arbitrary order!
# with open('test.cases','w') as f:
#     f.write(str(numVertices)+' '+str(numEdges)+'\n')
#     for v in listOne:
#         for w in listTwo:
#             if v != w and graph[v-1][w-1]==1 :
#                 f.write(str(v)+' '+str(w)+'\n')
#
#     f.write("0 0\n")
#
# write the line  graph to file but in arbitrary order!
with open('test2.cases','w') as f:
    f.write(str(10000)+' '+str(9999)+'\n')
    for v in range(10000, 1, -1):
        f.write(str(v)+' '+str(v-1)+'\n')

    f.write("0 0\n")

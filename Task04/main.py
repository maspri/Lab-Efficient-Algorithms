import heapq
#Solution  with heaps. heapq is contained in the standard libary of python
while True:
    cnt = int(input())
    if cnt != 0:
        numbers = list(map(int, input().split()))

        tmp = 0
        cost = 0

        heapq.heapify(numbers)
        for i in range(1, cnt):

            a = heapq.heappop(numbers)
            b = heapq.heappop(numbers)
            tmp = a + b
            cost += tmp
            heapq.heappush(numbers, tmp)
        print(cost)
    else:
        break












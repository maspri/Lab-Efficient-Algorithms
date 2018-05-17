import sys
from array import *


def binary_search(numbers, left, right, element):

    while right - left > 1:
        # define middle of the interval
        middle = int(left + (right - left)/2)

        # we are looking for the smallest index m with numbers[m] >= element

        # ignore everything greater than numbers[m]
        if numbers[middle] >= element:
            right = middle
        # ignore everything smaller than numbers[m]
        else:
            left = middle
    return right


def LISLength(numbers, n):
    # initialize the longest sequence
    sequence = [0 for i in range(n + 1)]
    sequence[0] = numbers[0]
    len = 1
    for i in range(1, n):

        # new smallest value
        if numbers[i] < sequence[0]:
            sequence[0] = numbers[i]

        # sequence is increasing
        elif numbers[i] > sequence[len - 1]:
            sequence[len] = numbers[i]
            # update length
            len += 1

        else:
            # numbers[i] belongs somewhere in the sequence
            # find the largest element in sequence, which is smaller than numbers[i]
            # numbers[i] will then be  appended at this element
            j = binary_search(sequence, -1, len-1, numbers[i])
            sequence[j] = numbers[i]

    return len


data = sys.stdin.read()
numbers = array('i', map(int, data.split()))
n = len(numbers)
print(LISLength(numbers, n))






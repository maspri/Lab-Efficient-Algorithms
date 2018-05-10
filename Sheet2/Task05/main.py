from array import*


class Node:

    def __init__(self, left, right, amount, children):
        self.left = left
        self.right = right
        self.amount = amount
        self.children = children


def query(node, i, j):

    # recursion anchor
    # adjust amount by subtracting the interval differences
    if not node.children:
        most = node.amount - (i - node.left)
        if j < node.right:
           most = most - (node.right - j)
        return most

    # recursion
    else:
        left_node = node.children[0]
        right_node = node.children[1]
        # interval is contained in the left node
        if i <= left_node.right and j <= left_node.right:
            most = query(node.children[0], i, j)
        # interval is split
        elif i <= left_node.right:
            most = max(query(left_node, i, left_node.right), query(right_node, right_node.left, j))
        # interval is contained in the right node
        else:
            most = query(right_node, i, j)

    return most


while True:

    try:
        # successful if input is a test case
        item_cnt, queries = map(int, input().split())
        numbers = array('i', (map(int, input().split())))

    except:
        # error if reading only 1 number -> the 0
        break

    # pre processing the input array by building node objects, which contain information about the interval and amount
    tmp_number = numbers[0]
    tmp_left = 0
    tmp_right = 0
    tmp_amount = 1
    tmp_children = []

    nodes = []

    for i in range(1, item_cnt):
        if tmp_number != numbers[i]:
            nodes.append(Node(tmp_left, tmp_right, tmp_amount, tmp_children))
            tmp_number = numbers[i]
            tmp_left = i
            tmp_right = i
            tmp_amount = 1

        else:
            tmp_right = tmp_right + 1
            tmp_amount = tmp_amount + 1

    nodes.append(Node(tmp_left, tmp_right, tmp_amount, tmp_children))

    # create tree by linking two node pairs, the odd vs even case is handled by the try block
    while len(nodes) != 1:
        new_nodes = []
        i = 0
        while i < len(nodes):

            try:
                tmp_left = nodes[i].left
                tmp_right = nodes[i+1].right
                tmp_amount = max(nodes[i].amount, nodes[i+1].amount)
                tmp_children = [nodes[i], nodes[i+1]]

                new_nodes.append(Node(tmp_left, tmp_right, tmp_amount, tmp_children))
            except:
                new_nodes.append(nodes[i])

            i = i+2

        nodes = new_nodes

    tree = nodes[0]

    # execute the queries
    for test in range(0, queries):
        i, j = map(int, input().split())
        # query indices vs array/list indices
        i = i - 1
        j = j - 1
        most_frequent = query(tree, i, j)
        print(most_frequent)
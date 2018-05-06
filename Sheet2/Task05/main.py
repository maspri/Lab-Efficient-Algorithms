while(True):
    try:
        # succesfull if input is a test case
        item_cnt, queries = map(int,input().split())
        numbers = list(map(int,input().split()))
    except:
        # error if reading only 1 number -> the 0
        break

    # linear time preprocess input array to get intervalls and occurrances
    Dict = {}
    last_number = numbers[0]
    Dict[last_number] = [0, 0, 1]    # triple contains informations(start, end, occurrance)
    glob_most = 1
    for i in range(1, item_cnt):
        if last_number == numbers[i]:
            Dict[numbers[i]][1] += 1
            Dict[numbers[i]][2] += 1
            tmp = Dict[numbers[i]][2]
            if glob_most < tmp:
                glob_most = tmp

        else:
            Dict[numbers[i]] = [i, i, 1]
            last_number = numbers[i]


    for test in range(0, queries):
        i, j = map(int, input().split())
        # adjust the query intervals to array intervals
        i = i - 1
        j = j - 1

        # get informations of the most left and most right number of the query interval
        left_number = numbers[i]
        right_number = numbers[j]
        left_number_i, left_number_j, left_number_a = Dict[left_number]
        right_number_i, right_number_j, right_number_a = Dict[right_number]

        # subtract the cut amount of occurrances of the left number
        most = left_number_a - (i - left_number_i)

        if j < left_number_j:
           most = most - (left_number_j - j)
          # check if it is necessary to calculate for the right number
        elif left_number != right_number:
            right_number_a = right_number_a - (right_number_j - j)

            if right_number_a > most:
                most = right_number_a

            # check if the interval has potential for a better number
            # that is if the most number is smaller then the left over interval and my most isnt the golbal most
            while (most < (right_number_i - left_number_j)) &( most < glob_most):
                right_number_i, right_number_j, right_number_a = Dict[numbers[right_number_i - 1]]
                # no calculation needed,
                # because all occurances are contained between the most left and most right number

                if right_number_a > most:
                    most = right_number_a
        print(most)


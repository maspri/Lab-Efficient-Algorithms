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
    Dict[numbers[0]] = [0, 0, 1]    # triple contains informations(start, end, occurrance)
    for i in range(1, item_cnt):
        if numbers[i] in Dict:
            Dict[numbers[i]][1] += 1
            Dict[numbers[i]][2] += 1
        else:
            Dict[numbers[i]] = [i, i, 1]

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

        #most = left_number_a

        if j < left_number_j:
           most = most - (left_number_j - j)

        # check if it is necessary to calculate for the right number
        elif left_number != right_number:
            right_number_a = right_number_a - (right_number_j - j)

            if right_number_a > most:
                most = right_number_a

            # check if the interval contains more than 2 numbers
            while left_number_j != (right_number_i - 1):
                right_number_i, right_number_j, right_number_a = Dict[numbers[right_number_i -1]]

                # no calculation needed,
                # because all occurances are contained between the most left and most right number

                if right_number_a > left_number_a:
                    most = right_number_a
        print(most)


while(True):
    player_cnt = int(input())
    if player_cnt == 0:
        break
    else:
        # usage of dictionary as a hash table
        Sets = {}
        for i in range(0, player_cnt):
            # frozenset = hashable set
            # set yields the property to be the same entity even if unordered
            new_set = frozenset(input().split())
            # collisions/same sets are counted in the corresponding slot
            if new_set in Sets:
                Sets[new_set] += 1
            else:
                Sets[new_set] = 1
        # get maximum attractiveness
        a, value = max(Sets.items())
        # get sets, which are most attractive
        maxkeys = [k for k, v in Sets.items() if v == value]
        # amount of attractive sets * the attractive value = players playing these sets
        print(len(maxkeys)* value)
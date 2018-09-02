import sys

data = sys.stdin.read().split("\n")
line = 0
# solving up to down and down to up, not sure if necessary
picture = {}
rev_pic = {}


def fix_picture(picture):
    count = 0
    # moving from left to right and up to down
    for row in range(15):
        for col in range(16):
            # looking at the top row and if "O" / True switching the cross below this icon
            if picture[row][col]:
                picture[row][col] = not picture[row][col]
                picture[row + 1][col] = not picture[row + 1][col]
                # some side cases
                if row < 14:
                    picture[row + 2][col] = not picture[row + 2][col]

                if col < 15:
                    picture[row + 1][col + 1] = not picture[row + 1][col + 1]
                if col > 0:
                    picture[row + 1][col - 1] = not picture[row + 1][col - 1]

                count += 1
    # checking if remaining "O" Trues in the last row
    for col in range(16):
        if picture[15][col]:
            count = -1
            break

    return count
# mapping the symbols to bools for better switching
while line < 16:
    picture[line] = []
    for c in data[line]:
        if c == "#":
            picture[line].append(False)
        else:
            picture[line].append(True)
    line += 1

line = 0
# building the reverse pic
while line < 16:
    rev_pic[line] = []
    for c in data[15 - line]:
        if c == "#":
            rev_pic[line].append(False)
        else:
            rev_pic[line].append(True)
    line += 1

count = fix_picture(picture)
rev_count = fix_picture(rev_pic)

print(count)
print(rev_count)


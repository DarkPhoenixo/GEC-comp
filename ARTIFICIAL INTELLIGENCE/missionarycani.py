from collections import deque

def isValid(mLeft, cLeft):
    if mLeft < 0 or mLeft > 3 or cLeft < 0 or cLeft > 3:
        return False

    if mLeft > 0 and mLeft < cLeft:
        return False
    mRight = 3 - mLeft
    cRight = 3 - cLeft

    if mRight > 0 and mRight < cRight:
        return False
    return True
def missionariesAndCannibals():
    solutions = 0
    stack = deque()

    start = (3, 3, 0)
    stack.append((3, 3, 0, [start]))

    moves = [(1, 0), (2, 0), (0, 1), (0, 2), (1, 1)]

    while stack:
        m, c, b, path = stack.pop()

        if (m, c, b) == (0, 0, 1):
            solutions += 1
            print(f"\nSolution {solutions}:")
            for state in path:
                print(f"({state[0]}, {state[1]}, ", end="")
                if state[2] == 0:
                    print("L)")
                else:
                    print("R)")
            continue

        for moveM, moveC in moves:

            if b == 0:
                newState = (m - moveM, c - moveC, 1)
            else:
                newState = (m + moveM, c + moveC, 0)

            _m, _c, _b = newState

            if isValid(_m, _c) and newState not in path:
                stack.append((_m, _c, _b, path + [newState]))

    print(f"\nTotal Solutions: {solutions}")

missionariesAndCannibals()

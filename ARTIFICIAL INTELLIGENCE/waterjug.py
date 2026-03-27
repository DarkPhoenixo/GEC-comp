from collections import deque


#----------------------------------------------------------------------------
def bfs(generate_func, start, goal):
  open_list = deque([(start, None)])
  closed_list = []
  visited = set([start])

  step = 1

  while open_list:
    node, parent = open_list.popleft()
    closed_list.append((node, parent))

    print(f"Step {step}: Expanding node {node}")
    step += 1

    if node == goal:
      break

    successors = generate_func(node)
    if successors:
        print(f"  Successors:")
        for i, succ in enumerate(successors, 1):
            print(f"    {i}. {succ}")
    else:
        print(f"  Successors: None")

    for neighbor in successors:
      if neighbor not in visited:
        visited.add(neighbor)
        open_list.append((neighbor, node))

  return closed_list
#------------------------------------------------------------------------------------

def generate(state, jug1_cap, jug2_cap, target):
    j1, j2 = state
    successors = []

    # Fill jug1
    if j1 < jug1_cap:
        successors.append((jug1_cap, j2))

    # Fill jug2
    if j2 < jug2_cap:
        successors.append((j1, jug2_cap))

    # Empty jug1
    if j1 > 0:
        successors.append((0, j2))

    # Empty jug2
    if j2 > 0:
        successors.append((j1, 0))

    # Pour from jug1 to jug2
    if j1 > 0 and j2 < jug2_cap:
        pour = min(j1, jug2_cap - j2)
        successors.append((j1 - pour, j2 + pour))

    # Pour from jug2 to jug1
    if j2 > 0 and j1 < jug1_cap:
        pour = min(j2, jug1_cap - j1)
        successors.append((j1 + pour, j2 - pour))

    return successors

jug1_cap = int(input("Enter capacity of jug 1: "))
jug2_cap = int(input("Enter capacity of jug 2: "))
target = int(input("Enter target amount: "))

initial = (0, 0)
goal = None

# Find goal state
for j1 in range(jug1_cap + 1):
    for j2 in range(jug2_cap + 1):
        if j1 == target or j2 == target:
            goal = (j1, j2)
            break
    if goal:
        break

if not goal:
    print("No solution possible with given capacities and target.")
    exit()

print(f"\nBFS traversal for Water Jug problem (step-by-step):")
print(f"Jug 1 capacity: {jug1_cap}, Jug 2 capacity: {jug2_cap}, Target: {target}")
print(f"Initial state: {initial}, Goal state: {goal}\n")

closed_list = bfs(lambda state: generate(state, jug1_cap, jug2_cap, target), initial, goal)

# Reconstruct path
parent_of = {node: parent for node, parent in closed_list}
path = []
current = goal
while current is not None:
    path.append(current)
    current = parent_of.get(current)
path.reverse()

print("\nPath to solution:")
for state in path:
    print(state)
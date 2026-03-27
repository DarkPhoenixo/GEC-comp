
#---------------------------------------------------------------------
def dfs_stack(generate_func, start, goal):
  stack = [(start, None)]
  closed_list = []
  visited = set([start])

  step = 1

  while stack:
    node, parent = stack.pop()
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

    for neighbor in reversed(successors):
      if neighbor not in visited:
        visited.add(neighbor)
        stack.append((neighbor, node))

  return closed_list
#-------------------------------------------------------------------------

def generate(state, n_m, n_c):
    m, c, b = state
    successors = []
    if b == 0:  # boat on left, moving to right
        for dm in range(4):  # 0 to 3 missionaries
            for dc in range(4):  # 0 to 3 cannibals
                if dm + dc >= 1 and dm + dc <= 2:
                    nm = m - dm
                    nc = c - dc
                    if nm >= 0 and nc >= 0:
                        # left side: if nm > 0, nc <= nm
                        if nm == 0 or nc <= nm:
                            # right side: rm = n_m - nm, rc = n_c - nc
                            rm = n_m - nm
                            rc = n_c - nc
                            if rm == 0 or rc <= rm:
                                successors.append((nm, nc, 1))
    else: 
        for dm in range(4):
            for dc in range(4):
                if dm + dc >= 1 and dm + dc <= 2:
                    nm = m + dm
                    nc = c + dc
                    if nm <= n_m and nc <= n_c:
                        if nm == 0 or nc <= nm:
                            rm = n_m - nm
                            rc = n_c - nc
                            if rm == 0 or rc <= rm:
                                successors.append((nm, nc, 0))
    return successors

n_m = int(input("Enter number of missionaries: "))
n_c = int(input("Enter number of cannibals: "))

initial = (n_m, n_c, 0)
goal = (0, 0, 1)

print("\nDFS traversal for Missionary Cannibals problem (step-by-step):")
closed_list = dfs_stack(lambda state: generate(state, n_m, n_c), initial, goal)

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

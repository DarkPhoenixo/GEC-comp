def dfs_stack(graph, start):
  stack = [(start, None)]
  closed_list = []
  visited = set([start])

  print(f"{'Step':<5} {'OPEN':<40} {'CLOSED'}")
  step = 1

  while stack:
    print(f"{step:<5} {list(stack)!s:<40} {closed_list}")
    step += 1

    node, parent = stack.pop()
    closed_list.append((node, parent))

    # Add neighbors in reverse to mimic recursive DFS order
    for neighbor in reversed(graph[node]):
      if neighbor not in visited:
        visited.add(neighbor)
        stack.append((neighbor, node))

  print(f"{step:<5} {list(stack)!s:<40} {closed_list}")
  return closed_list



start_node = input("Enter starting node: ")

n = int(input("Enter number of nodes: "))
nodes = []
for i in range(n):
  node = input(f"Enter node {i+1}: ")
  nodes.append(node)

user_graph = {}
for node in nodes:
  user_graph[node] = []

m = int(input("Enter number of edges: "))
for i in range(m):
  edge = input(f"Enter edge {i+1} (format: node1 node2): ").split()
  if len(edge) == 2:
    u, v = edge
    if u in user_graph and v in user_graph:
      user_graph[u].append(v)
      user_graph[v].append(u)

print("\nDFS traversal (step-by-step):")
dfs_stack(user_graph, start_node)

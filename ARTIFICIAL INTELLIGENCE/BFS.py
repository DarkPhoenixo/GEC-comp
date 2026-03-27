from collections import deque


#----------------------------------------------------------------------------
def bfs(graph, start):
  open_list = deque([(start, None)]) 
  closed_list = []
  visited = set([start])

  print(f"{'Step':<5} {'OPEN':<40} {'CLOSED'}")
  step = 1

  while open_list:
    
    print(f"{step:<5} {list(open_list)!s:<40} {closed_list}")
    step += 1

    node, parent = open_list.popleft()
    closed_list.append((node, parent))

    for neighbor in graph[node]:
      if neighbor not in visited:
        visited.add(neighbor)
        open_list.append((neighbor, node))

  
  print(f"{step:<5} {list(open_list)!s:<40} {closed_list}")
  return closed_list
#------------------------------------------------------------------------------------


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

print("\nBFS traversal (step-by-step):")
bfs(user_graph, start_node)
def hill_climbing(graph, heuristic, start, goal, maximize=False):
  current = start
  path = [current]
  visited = set([current])

  while current != goal:
    neighbors = [n for n in graph[current] if n not in visited]
    if not neighbors:
      break  

    
    if maximize:
      next_node = max(neighbors, key=lambda n: heuristic[n])
      if heuristic[next_node] <= heuristic[current]:
        break  
    else:
      next_node = min(neighbors, key=lambda n: heuristic[n])
      if heuristic[next_node] >= heuristic[current]:
        break  

    current = next_node
    path.append(current)
    visited.add(current)

  return path

start_node = input("Enter starting node: ")
goal_node = input("Enter goal node: ")

n = int(input("Enter number of nodes: "))
nodes = []
for i in range(n):
  node = input(f"Enter node {i+1}: ")
  nodes.append(node)

user_graph = {}
heuristic = {}
for node in nodes:
  user_graph[node] = []
  h_value = float(input(f"Enter heuristic value for node {node}: "))
  heuristic[node] = h_value

m = int(input("Enter number of edges: "))
for i in range(m):
  edge = input(f"Enter edge {i+1} (format: node1 node2): ").split()
  if len(edge) == 2:
    u, v = edge
    if u in user_graph and v in user_graph:
      user_graph[u].append(v)
      user_graph[v].append(u)


maximize = False  

print("\nHill Climbing Search starting from", start_node + ":")
result = hill_climbing(user_graph, heuristic, start_node, goal_node, maximize)
print(result)
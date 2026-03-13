import heapq

def a_star_search(graph, heuristic, start, goal):
  open_set = []
  heapq.heappush(open_set, (heuristic[start], 0, start, [start]))  
  visited = {}

  while open_set:
    f, g, node, path = heapq.heappop(open_set)

    if node == goal:
      return path

    if node in visited and visited[node] <= g:
      continue
    visited[node] = g

    for neighbor, cost in graph[node]:
      new_g = g + cost
      new_f = new_g + heuristic[neighbor]
      heapq.heappush(open_set, (new_f, new_g, neighbor, path + [neighbor]))

  return None

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
  edge = input(f"Enter edge {i+1} (format: node1 node2 cost): ").split()
  if len(edge) == 3:
    u, v, cost = edge
    cost = float(cost)
    if u in user_graph and v in user_graph:
      user_graph[u].append((v, cost))
      user_graph[v].append((u, cost))

print("\nA* Search starting from", start_node + ":")
result = a_star_search(user_graph, heuristic, start_node, goal_node)
if result:
  print("Path:", result)
else:
  print("No path found.")
import heapq

def best_first_search(graph, heuristic, start, goal):
  open_pq = [(heuristic[start], start, None)] 
  closed = []
  parent_map = {start: None}
  open_set = set([start]) 

  step = 1
  while open_pq:
    print(f"\nStep {step}:")
    # Print OPEN
    print("OPEN: ", end="")
    print([f"({n}, {parent_map.get(n)}, {h})" for h, n, _ in sorted(open_pq)])
    # Print CLOSED
    print("CLOSED: ", end="")
    print([f"({n}, {parent_map.get(n)}, {heuristic[n]})" for n in closed])

    _, node, _ = heapq.heappop(open_pq)
    open_set.remove(node)
    closed.append(node)

    if node == goal:
      print("\nGoal state found.")
      break

    for neighbor in graph[node]:
      if neighbor not in closed and neighbor not in open_set:
        parent_map[neighbor] = node
        heapq.heappush(open_pq, (heuristic[neighbor], neighbor, node))
        open_set.add(neighbor)
    step += 1

  
  print(f"\nStep {step}:")
  print("OPEN: ", end="")
  print([f"({n}, {parent_map.get(n)}, {heuristic[n]})" for n in open_set])
  print("CLOSED: ", end="")
  print([f"({n}, {parent_map.get(n)}, {heuristic[n]})" for n in closed])

  
  path = []
  curr = goal
  while curr is not None:
    path.append(curr)
    curr = parent_map.get(curr)
  path.reverse()
  print(f"\nPath: {' -> '.join(path)}   Length = {len(path)-1}")



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

print("\nBest First Search steps :")
result = best_first_search(user_graph, heuristic, start_node, goal_node)

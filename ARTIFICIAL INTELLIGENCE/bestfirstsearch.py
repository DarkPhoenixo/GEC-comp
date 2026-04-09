from collections import deque
import heapq

#----------------------------------------------------------------------------
def best_first_search(graph, start, goal, heuristics):
  open_list = [(heuristics[start], start)]  # (heuristic_value, node)
  closed_list = []
  visited = set()
  parent_map = {start: None}

  print(f"{'Step':<5} {'OPEN':<50} {'CLOSED'}")
  step = 1

  while open_list:
    open_display = [(node, h) for h, node in open_list]
    print(f"{step:<5} {open_display!s:<50} {closed_list}")
    step += 1

    h_value, node = heapq.heappop(open_list)  # Pop node with lowest heuristic
    visited.add(node)
    closed_list.append((node, parent_map[node]))

    if node == goal:
      print(f"{step:<5} {[(n, h) for h, n in open_list]!s:<50} {closed_list}")
      print("GOAL STATE REACHED")
      break

    for neighbor in graph[node]:
      if neighbor not in visited:
        if neighbor not in [n for _, n in open_list]:
          parent_map[neighbor] = node
          heapq.heappush(open_list, (heuristics[neighbor], neighbor))

  print(f"{step:<5} {[(n, h) for h, n in open_list]!s:<50} {closed_list}")
  
  # Print path
  path = []
  current = goal
  while current is not None:
    path.append(current)
    current = parent_map.get(current)
  
  path.reverse()
  print(f"\nPath from {start} to {goal}: {' -> '.join(path)}")
  
  return closed_list
#------------------------------------------------------------------------------------

start_node = input("Enter starting node: ")
goal_node = input("Enter goal node: ")

n = int(input("Enter number of nodes: "))
nodes = []
heuristics = {}
for i in range(n):
  node = input(f"Enter node {i+1}: ")
  h_value = int(input(f"Enter heuristic value for {node}: "))
  nodes.append(node)
  heuristics[node] = h_value

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

print("\nBest First Search traversal (step-by-step):")
best_first_search(user_graph, start_node, goal_node, heuristics)
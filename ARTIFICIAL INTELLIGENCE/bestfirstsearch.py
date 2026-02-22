from collections import deque
import heapq

def best_first_search(graph, heuristic, start, goal):
  visited = set()
  pq = [(heuristic[start], start)]
  visited.add(start)
  result = []
  
  while pq:
    _, node = heapq.heappop(pq)
    result.append(node)
    
    if node == goal:
      break
    
    for neighbor in graph[node]:
      if neighbor not in visited:
        visited.add(neighbor)
        heapq.heappush(pq, (heuristic[neighbor], neighbor))
  
  return result


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

print("\nBest First Search starting from", start_node + ":")
result = best_first_search(user_graph, heuristic, start_node, goal_node)
print(result)
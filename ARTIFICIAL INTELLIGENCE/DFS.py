def dfs(graph, start, visited=None):

  if visited is None:
    visited = set()
  
  visited.add(start)
  result = [start]
  
  for neighbor in graph[start]:
    if neighbor not in visited:
      result.extend(dfs(graph, neighbor, visited))
  
  return result


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
  edge = input(f"Enter edge {i+1} (format: integers): ").split()
  if len(edge) == 2:
    u, v = edge
    if u in user_graph and v in user_graph:
      user_graph[u].append(v)
      user_graph[v].append(u)  

print("\nDFS starting from", start_node + ":")
result = dfs(user_graph, start_node)
print(result)

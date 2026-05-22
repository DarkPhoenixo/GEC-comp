import heapq

# Function to implement Dijkstra Algorithm
def dijkstra(graph, start):
    # Step 1: Initialize distances
    distances = {}
    for node in graph:
        distances[node] = float('inf')
    distances[start] = 0

    # Priority Queue
    priority_queue = [(0, start)]

    # To store visited routers
    visited = set()

    print("\nInitial Routing Table")
    print("------------------------------------------------")
    for node in distances:
        print(f"Router {node} --> {distances[node]}")

    # Step 2: Process routers
    while priority_queue:
        current_distance, current_router = heapq.heappop(priority_queue)

        # Skip already visited routers
        if current_router in visited:
            continue
        visited.add(current_router)

        print(f"\nProcessing Router {current_router}")
        print("------------------------------------------------")

        # Check neighboring routers
        for neighbor, weight in graph[current_router]:
            print(f"Checking Path:")
            print(f"{current_router} --> {neighbor}")
            print(f"Link Cost = {weight}")

            new_distance = current_distance + weight

            # Update shortest path
            if new_distance < distances[neighbor]:
                old_distance = distances[neighbor]
                distances[neighbor] = new_distance
                print(f"Updating Router {neighbor}")
                print(f"Old Distance = {old_distance}")
                print(f"New Distance = {new_distance}")

                # Push into priority queue
                heapq.heappush(priority_queue, (new_distance, neighbor))
            else:
                print("No Update Required")
            print()

        # Show routing table after processing
        print("Routing Table After Processing")
        print("------------------------------------------------")
        for node in distances:
            print(f"Router {node} --> {distances[node]}")

    # Step 3: Final Shortest Path Table
    print("\nFinal Shortest Path Table")
    print("------------------------------------------------")
    print("Destination Router\tShortest Distance")
    for node in distances:
        print(f"{node}\t\t\t{distances[node]}")

# --------------------------------------------------------
# Main Program
# --------------------------------------------------------
# Graph Representation
# Format:
# Router : [(Neighbor, Cost)]
graph = {
    0: [(1, 3), (2, 6)],
    1: [(0, 3), (2, 2), (3, 7)],
    2: [(0, 6), (1, 2), (3, 4), (4, 9)],
    3: [(1, 7), (2, 4), (4, 1), (5, 5)],
    4: [(2, 9), (3, 1), (5, 2)],
    5: [(3, 5), (4, 2)]
}

# Starting router (changed)
start = 1

# Function Call
dijkstra(graph, start)
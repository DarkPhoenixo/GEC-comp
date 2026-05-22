def bellman_ford(graph, vertices, source):
    # Step 1: Initialize distances
    distance = [float('inf')] * vertices
    distance[source] = 0

    print("\nInitial Routing Table")
    print("------------------------------------------------")
    for i in range(vertices):
        print(f"Router {i} --> {distance[i]}")

    # Step 2: Relax edges repeatedly
    for iteration in range(vertices - 1):
        print(f"\nIteration {iteration + 1}")
        print("------------------------------------------------")
        updated = False

        for u, v, w in graph:
            # Check for shorter path
            if distance[u] != float('inf') and distance[u] + w < distance[v]:
                old_distance = distance[v]
                distance[v] = distance[u] + w
                updated = True

                print(f"Updating Router {v}")
                print(f"Path: Router {u} --> Router {v}")
                print(f"Edge Cost = {w}")
                print(f"Old Distance = {old_distance}")
                print(f"New Distance = {distance[v]}")
                print()

        # Show current routing table after each iteration
        print("Routing Table After Iteration")
        print("--------------------------------")
        for i in range(vertices):
            print(f"Router {i} --> {distance[i]}")

        # If no update occurs, stop early
        if not updated:
            print("\nNo further updates possible.")
            print("Shortest paths already found.")
            break

    # Step 3: Final Result
    print("\nFinal Routing Table")
    print("------------------------------------------------")
    print("Destination Router\tMinimum Distance")
    for i in range(vertices):
        print(f"{i}\t\t\t{distance[i]}")


graph = [
    (0, 1, 6),
    (0, 2, 5),
    (0, 3, 5),
    (1, 4, -1),
    (2, 1, -2),
    (2, 4, 1),
    (3, 2, -2),
    (3, 5, -1),
    (4, 6, 3),
    (5, 6, 3)
]


vertices = 7


source = 0


bellman_ford(graph, vertices, source)
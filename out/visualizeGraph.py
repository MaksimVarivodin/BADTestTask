import networkx as nx
import matplotlib.pyplot as plt

# Define nodes and edges
nodes = [
    345120,
    120345,
    789012,
    561234,
    901234,
    103456,
    341056,
    405678,
    345678,
    234789
]

edges = [
    (789012, 120345),
    (561234, 345120), (561234, 341056), (561234, 345678),
    (901234, 345120), (901234, 341056), (901234, 345678),
    (103456, 561234),
    (341056, 561234),
    (405678, 789012),
    (345678, 789012)
]
# Define the maximum path\n",
max_path = [901234, 341056, 561234, 345678, 789012, 120345]


def draw_longest_path(nodes, edges, max_path):
    # Create the graph
    G = nx.DiGraph()
    G.add_nodes_from(nodes)
    G.add_edges_from(edges)

    # Setup spring layout for visualization
    k_value = 0.5
    pos = nx.spring_layout(G, seed=41, k=k_value, threshold=0.04)

    # Draw the graph
    plt.figure(figsize=(12, 8))

    # Draw all edges
    nx.draw(
        G, pos, with_labels=True, node_size=500,
        node_color="skyblue", font_size=10, font_weight="bold",
        edge_color="gray"
    )

    # Highlight the maximum path\n",
    max_path_edges = [(max_path[i], max_path[i + 1]) for i in range(len(max_path) - 1)]
    nx.draw_networkx_edges(G, pos, edgelist=max_path_edges, edge_color="red", width=2)

    # Show the title and plot
    plt.title("Graph with Maximum Path Highlighted")
    plt.show()


for i in range(1, len(max_path) + 1):
    draw_longest_path(nodes, edges, max_path[0: i])

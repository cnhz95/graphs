#include "graph.h"
#include <algorithm>
#include <iostream>
#include <stack>
#include <queue>

Graph::Graph(const adjacency_list_t& list) : list(list), matrix(NUMBER_OF_NODES,
    std::vector<std::pair<double, std::string>>(NUMBER_OF_NODES, {DEFAULT_VALUE, ""})) {
    std::for_each(list.second.begin(), list.second.end(), [&](const Edge& edge) -> void {
        matrix[edge.node_1][edge.node_2] = {edge.weight, edge.description};
    });
}

void Graph::print_matrix() const {
    for (size_t row = 0; row < matrix.size(); row++) {
        std::cout << '\n' << row << ": ";
        for (size_t col = 0; col < matrix.size(); col++) {
            std::cout << matrix[row][col].first << " ";
        }
    }
    std::cout << '\n';
}

// Traverses by depth to all nodes that are reachable from a starting node
void Graph::dfs(int start_node) {
    visited.assign(NUMBER_OF_NODES, 0); // Replaces the content of the vector
    std::stack<int> st;
    st.push(start_node);
    while (!st.empty()) {
        int curr = st.top();
        st.pop();
        visited[curr] = true; // Marks the current node as visited
        for (int neighbour : get_neighbours(curr)) {
            st.push(neighbour);
        }
    }
    fix_graph(); // Creates a path to each node that is not connected
}

// Traverses by breadth to all nodes that are reachable from a starting node
void Graph::bfs(int start_node) {
    visited.assign(NUMBER_OF_NODES, 0);
    std::queue<int> q;
    q.push(start_node);
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        visited[curr] = true;
        for (int neighbour : get_neighbours(curr)) {
            q.push(neighbour);
        }
    }
    fix_graph();
}

std::vector<int> Graph::get_neighbours(int node) const {
    std::vector<int> neighbours;
    for (size_t index = 0; index < matrix.size(); index++) {
        if (matrix[node][index].first != DEFAULT_VALUE && !visited[index]) {
            neighbours.push_back((int)index);
        }
    }
    return neighbours;
}

// Calculates the shortest path between two nodes in a graph with non-negative edge weights
double Graph::dijkstra(int start_node, int end_node) {
    distance.assign(NUMBER_OF_NODES, INF); // Sets the distance to all nodes to infinity
    predecessor.assign(NUMBER_OF_NODES, DEFAULT_VALUE);
    visited.assign(NUMBER_OF_NODES, 0);
    distance[start_node] = 0.0;
    std::priority_queue<node_t, std::vector<node_t>, std::greater<node_t>> pq; // min heap
    pq.push({0.0, start_node});
    while (!pq.empty()) {
        auto curr = pq.top(); // Chooses the current most promising node
        pq.pop();
        visited[curr.second] = true;
        if (distance[curr.second] < curr.first) { // A shorter path to this node has already been found
            continue;
        }
        for (const auto& [weight, neighbour] : dijkstra_neighbours(curr)) {
            double new_distance = distance[curr.second] + weight; // Distance from current node to neighbour
            if (new_distance < distance[neighbour]) { // Shorter distance found
                predecessor[neighbour] = curr.second; // Current node has shorter distance to the neighbour
                distance[neighbour] = new_distance; // Update to the new better distance (relaxation)
                pq.push({distance[neighbour], neighbour});
            }
        }
        if (curr.second == end_node) { // Minimum distance has been found
            return distance[end_node];
        }
    }
    return INF; // The end node is unreachable from the start node
}

std::vector<node_t> Graph::dijkstra_neighbours(const node_t& node) const {
    std::vector<node_t> neighbours;
    for (size_t index = 0; index < matrix.size(); index++) {
        if (matrix[node.second][index].first != DEFAULT_VALUE && !visited[index]) {
            neighbours.push_back({matrix[node.second][index].first, index});
        }
    }
    return neighbours;
}

// Creates a path to each node that is not connected
void Graph::fix_graph() {
    for (size_t index = 0; index < visited.size(); index++) {
        if (!visited[index]) { // Node could not be reached
            std::for_each(list.second.begin(), list.second.end(), [&](const Edge& edge) -> void {
                if (edge.node_1 == index) {
                    matrix[edge.node_2][index] = {edge.weight, edge.description};
                    std::cout << "A new edge was created from node " << edge.node_2
                              << " to node " << index << '\n';
                    std::cout << '\n';
                }
            });
        }
    }
}

// Reconstructs the shortest path by starting at the end node and
// repeatedly taking the predecessor until reaching the start node
std::vector<int> Graph::reconstruct_path(int start_node, int end_node) const {
    std::vector<int> path;
    if (distance[end_node] != INF) { // End node is reachable
        for (int curr_node = end_node; curr_node != DEFAULT_VALUE; curr_node = predecessor[curr_node]) {
            path.push_back(curr_node);
        }
        std::reverse(path.begin(), path.end());
    }
    return path;
}

void Graph::print_path(int start_node, int end_node) {
    std::cout << list.first[start_node] << " to" << list.first[end_node] << ": \n";
    for (int node : reconstruct_path(start_node, end_node)) {
        std::cout << "Node " << node << ": " << list.first[node] << '\n';
    }
    std::cout << '\n';
}

size_t Graph::size() const {
    return matrix[0].size();
}
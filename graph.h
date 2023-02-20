#ifndef GRAPHS_GRAPH_H
#define GRAPHS_GRAPH_H

#include "reader.h"
#include <limits>
#include <string>
#include <queue>
#include <vector>

using node_t = std::pair<double, int>;

class Graph {
public:
    explicit Graph(const adjacency_list_t& list);

    void dfs(int start_node);
    void bfs(int start_node);
    double dijkstra(int start_node, int end_node);

    void fix_graph(); // Creates a path to each node that is not connected
    void print_matrix() const;
    void print_path(int start_node, int end_node);
    size_t size() const;

private:
    const int NUMBER_OF_NODES = 48;
    const int DEFAULT_VALUE = -1;
    const double INF = std::numeric_limits<double>::max();

    adjacency_list_t list;
    std::vector<std::vector<std::pair<double, std::string>>> matrix;
    std::vector<double> distance; // Keeps the minimum distance to every node from the start node
    std::vector<int> predecessor; // Keeps track of the node that lead to the current node
    std::vector<bool> visited;

    std::vector<int> get_neighbours(int node) const;
    std::vector<node_t> dijkstra_neighbours(const node_t& node) const;
    std::vector<int> reconstruct_path(int start_node, int end_node) const;
};

#endif
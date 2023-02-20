#include "graph.h"
#include "reader.h"
#include <algorithm>
#include <iostream>

void print_list(const adjacency_list_t& list) {
    std::for_each(list.first.begin(), list.first.end(), [](const auto& meta) -> void {
        std::cout << meta.first << " " << meta.second << '\n';
    });
    std::for_each(list.second.begin(), list.second.end(), [](const Edge& edge) -> void {
        std::cout << edge.node_1 << " " << edge.node_2 << " " << edge.weight << " " << edge.description << '\n';
    });
}

int main() {
    const std::string FILENAME = "edges.txt";
    adjacency_list_t list = parse_file(FILENAME);

    Graph graph(list);
    //print_list(list);

    // Checks if all nodes can be reached starting from any node
    for (size_t index = 0; index < graph.size(); index++) {
        graph.dfs(index);
        //graph.bfs(index);
    }

    graph.print_matrix();

    std::cout << "The distance is " << graph.dijkstra(24, 37) << " from";
    graph.print_path(24, 37);

    std::cout << "The distance is " << graph.dijkstra(46, 47) << " from";
    graph.print_path(46, 47);

    std::cout << "The distance is " << graph.dijkstra(20, 19) << " from";
    graph.print_path(20, 19);

    return 0;
}
#ifndef GRAPHS_READER_H
#define GRAPHS_READER_H

#include <istream>
#include <map>
#include <vector>

using node_id_t = int;
using weight_t = double;
using meta_t = std::map<node_id_t, std::string>;

struct Edge {
    node_id_t node_1;
    node_id_t node_2;
    weight_t weight;
    std::string description;
};

using edge_list_t = std::vector<Edge>;
using adjacency_list_t = std::pair<meta_t, edge_list_t>;
adjacency_list_t parse_file(const std::string& filename);

#endif
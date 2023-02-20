#include "reader.h"
#include <fstream>

meta_t meta;

enum Token {
    COMMENT, META, EDGE, END_OF_FILE
};

Token get_line_type(std::istream& is) {
    switch (is.peek()) { // Reads the next character from the input stream without extracting it
        case std::istream::traits_type::eof():
            return END_OF_FILE;
        case '#':
            return COMMENT;
        case 'M':
            return META;
    }
    return EDGE;
}

Edge read_edge(std::istream& is) {
    Edge edge;
    is >> edge.node_1 >> edge.node_2 >> edge.weight;
    std::getline(is, edge.description);
    return edge;
}

void read_meta(std::istream& is) {
    char discard;
    node_id_t vertex_id;
    std::string name;
    is >> discard >> vertex_id;
    std::getline(is, name);
    meta[vertex_id] = name;
}

adjacency_list_t parse_file(const std::string& filename) {
    std::ifstream in(filename);
    Token l;
    edge_list_t edge_list;
    while ((l = get_line_type(in)) != END_OF_FILE) {
        Edge edge;
        switch (l) {
            case Token::EDGE:
                edge = read_edge(in);
                edge_list.push_back(edge);
                break;
            case Token::META:
                read_meta(in);
                break;
            default:
                std::string comment;
                std::getline(in, comment);
        }
    }
    return adjacency_list_t{meta, edge_list};
}
#ifndef GRAF_H
#define GRAF_H
#include "DFS.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

class graf
{
    public:
    graf( size_t v_number = 0) ;
    ~graf();

    size_t get_vertex_number();
    std::vector<  std::vector<size_t >  > get_edges();
    std::vector<std::pair< size_t, size_t> > find_bridge();
    void set_vertex_count( size_t v_number );
    void add_edge( size_t first, size_t second );
    bool check_edge(size_t first , size_t second, DFS& dfs );
    bool optimisation( size_t first , size_t second  );

    private:
    size_t  vertex_number;
    std::vector<  std::vector<size_t >  > edges;

};

#endif // GRAF_H




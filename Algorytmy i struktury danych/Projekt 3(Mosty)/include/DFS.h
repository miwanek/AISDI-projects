#ifndef DFS_H
#define DFS_H
#include <iostream>
#include <vector>

class DFS
{
    public:
        DFS( size_t v_number );
        ~DFS();
        bool walk( size_t first, size_t second, std::vector<  std::vector<size_t >  >& edges, size_t& vertex_number );
    private:
        std::vector<bool> visited;


};

#endif // DFS_H

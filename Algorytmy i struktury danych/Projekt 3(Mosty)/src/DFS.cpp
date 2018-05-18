#include "DFS.h"
#include <iostream>
#include <vector>
#include <queue>

DFS::DFS(size_t v_number )
{
    visited.resize( v_number, false );
}

DFS::~DFS()
{
    //
}

bool DFS::walk( size_t first, size_t second, std::vector<  std::vector<size_t >  >& edges, size_t& vertex_number )
{
   size_t beginning, current;
   size_t vertex_count= 0;
   for( size_t i=0 ; i< vertex_number; i++ )
   {
        if(i != first && i!= second)
        {
            beginning= i;
            break;
        }
   }
   visited[first] = true;
   visited[second] = true;
   visited[beginning] = true;
   std::queue<size_t >v_stack;
   v_stack.push(beginning);
   while(v_stack.empty() == false )
   {
        current=v_stack.front();
        v_stack.pop();
        ++vertex_count;
        for(auto i= edges[current].begin(); i!=edges[current].end(); ++i)
        {
            if(visited[ *i ] == true ) continue;
            else
            {
                visited[ *i ]= true;
                v_stack.push( *i );
            }

        }
   }
   size_t vector_size= visited.size();
   visited.assign( vector_size, false );
   if( vertex_count != vertex_number-2 )
   {
        return false;
   }
   return true;
}

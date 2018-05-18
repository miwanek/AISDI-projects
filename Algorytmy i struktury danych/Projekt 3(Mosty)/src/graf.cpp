#include "graf.h"
#include "DFS.h"

#include <iostream>
#include <fstream>
#include <list>
#include <queue>
#include <algorithm>

graf::graf(size_t v_number)
{
    vertex_number= v_number;
    if( vertex_number != 0 ) edges.resize(vertex_number ) ;
}

graf::~graf()
{

}

size_t graf::get_vertex_number()
{
    return vertex_number;
}

std::vector<  std::vector<size_t >  > graf::get_edges()
{
    return edges;
}

std::vector<std::pair< size_t, size_t> > graf::find_bridge()
{
   std::vector<std::pair< size_t, size_t> >  bridge;
   DFS dfs( vertex_number );
   for( size_t i =0; i< vertex_number; i++ )
   {
        for(auto j=  edges[i].begin(); j!= edges[i].end() ; ++j )
        {
            if(*j > i )
            {
                if( check_edge(i, *j, dfs) == true )  bridge.push_back( std::make_pair( i, *j ) );
            }
        }
   }
   return bridge;
}

void graf::set_vertex_count( size_t v_number )
{
    vertex_number= v_number;
    edges.resize(vertex_number );
}

void graf::add_edge(  size_t first,  size_t second  )
{
    if( first >= vertex_number || second >= vertex_number)
    {
        std::string edge_failure= "Nie mozna dodać krawedzi z wierzchołkami, których nie ma w grafie";
        throw edge_failure;
    }
    edges[first].push_back(second);
    edges[second].push_back(first);
}

bool graf::optimisation(  size_t first , size_t second  )
{
   if( vertex_number < 4 ) return true;
   if( vertex_number > 4 )
   {
        size_t threshold= ( ( (vertex_number-3) * (vertex_number-4) )/ 2 ) + 1;
        size_t edge_count= 0;
        for( size_t i=0 ; i< vertex_number; i++ )
        {
            edge_count+= edges[i].size();
        }
        edge_count-= 2 * ( edges[first].size() + edges[second].size() );
        edge_count/= 2;
        if(edge_count >= threshold ) return true;
   }
   return false;
}

bool graf::check_edge( size_t first , size_t second, DFS& dfs )
{
   if( optimisation( first, second ) == true ) return false;
   if( dfs.walk( first, second, edges, vertex_number ) == true ) return false;
   return true;
}



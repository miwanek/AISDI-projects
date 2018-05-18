#include <iostream>
#include <algorithm>
#include "graf.h"
#include "Boost_test.h"
#include <chrono>
#include <ctime>
#include <sstream>

void load_graf( graf& tested_graph );
void show_bridge( std::vector<std::pair< size_t, size_t> >  bridge );
void show(graf& tested_graph);

#ifndef _DEBUG
int main(int argc, char **argv)
{
    try
    {
    graf tested_graph;
    load_graf( tested_graph ) ;
    auto clock_start = std::chrono::high_resolution_clock::now();
    std::vector<std::pair< size_t, size_t> > found_bridges= tested_graph.find_bridge();
    auto clock_end = std::chrono::high_resolution_clock::now();
    show_bridge( found_bridges );
    std::cout<<" Znalezienie mostow rozległych zajęło: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_end-clock_start).count()<<" nanosekund \n";
    //show(tested_graph);
    }
    catch(std::string failure)
    {
        std::cout<<"Blad: "<<failure<<"\n";
    }

    return 0;
}
#endif

void load_graf( graf& tested_graph )
{
    size_t v_number ;
    std::cin >> v_number;
    tested_graph.set_vertex_count( v_number );
    std::cin.ignore();
    std::string input;
	while (std::getline(std::cin, input))
	{
        size_t first, second;
		if (input == "") break;
		std::stringstream loaded_edge;
		loaded_edge << input;
		loaded_edge >> first >> second;
		tested_graph.add_edge(first, second );
	}
}

void show_bridge( std::vector<std::pair< size_t, size_t> >  bridge )
{
   for( auto i= bridge.begin(); i!= bridge.end(); ++i )
   {
        std::cout<< (*i).first << " " << (*i).second<<std::endl;
   }

}

void show(graf& tested_graph)
{
   size_t vertex_number= tested_graph.get_vertex_number();
   std::cout<< vertex_number <<std::endl;
   auto edges= tested_graph.get_edges();
   for( size_t i =0; i< vertex_number; i++ )
   {
        for(auto j=  edges[i].begin(); j!= edges[i].end() ; j++ )
        {
            if(*j > i )
            {
                std::cout<< i << " " << *j << std::endl ;
            }
        }
   }
}


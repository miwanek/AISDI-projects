#ifndef BOOST_TEST_H_INCLUDED
#define BOOST_TEST_H_INCLUDED

#ifdef _DEBUG

#include <fstream>
#include <algorithm>
#include "graf.h"

#define BOOST_TEST_MODULE my master test suite name
#include <boost/test/included/unit_test.hpp>

graf load( std::string file_name)
{
    std::fstream plik;
    plik.open(file_name, std::ios::in);
    size_t vertex_number;
    plik >> vertex_number;
    graf tested_graph(vertex_number);
    int first , second ;
    while (plik >> first >> second )
    {
        tested_graph.add_edge(first, second);
    }
    plik.close();
    return tested_graph;
}

BOOST_AUTO_TEST_CASE( test1_txt )
{
    auto tested_graph= load("test1.txt");
    std::vector<std::pair< size_t, size_t> > found_bridges= tested_graph.find_bridge();
    BOOST_REQUIRE_EQUAL( found_bridges.size(), 0 );
    BOOST_REQUIRE_EQUAL( tested_graph.get_vertex_number(), 3 );
}


BOOST_AUTO_TEST_CASE( test2_txt )
{
    auto tested_graph= load("test2.txt");
    std::vector<std::pair< size_t, size_t> > found_bridges= tested_graph.find_bridge();
    BOOST_REQUIRE_EQUAL( found_bridges.size(), 2 );
    BOOST_REQUIRE_EQUAL( tested_graph.get_vertex_number(), 5 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].first , 1 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].second , 2 );
    BOOST_REQUIRE_EQUAL( found_bridges[1].first , 2 );
    BOOST_REQUIRE_EQUAL( found_bridges[1].second , 3 );

}

BOOST_AUTO_TEST_CASE( test3_txt )
{
    auto tested_graph= load("test3.txt");
    std::vector<std::pair< size_t, size_t> > found_bridges= tested_graph.find_bridge();
    BOOST_REQUIRE_EQUAL( found_bridges.size(), 0 );
    BOOST_REQUIRE_EQUAL( tested_graph.get_vertex_number(), 1 );

}

BOOST_AUTO_TEST_CASE( test4_txt )
{
    auto tested_graph= load("test4.txt");
    std::vector<std::pair< size_t, size_t> > found_bridges= tested_graph.find_bridge();
    BOOST_REQUIRE_EQUAL( found_bridges.size(), 1 );
    BOOST_REQUIRE_EQUAL( tested_graph.get_vertex_number(), 4 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].first , 1 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].second , 3 );
}

BOOST_AUTO_TEST_CASE( test5_txt )
{
    auto tested_graph= load("test5.txt");
    std::vector<std::pair< size_t, size_t> > found_bridges= tested_graph.find_bridge();
    BOOST_REQUIRE_EQUAL( found_bridges.size(), 6 );
    BOOST_REQUIRE_EQUAL( tested_graph.get_vertex_number(), 8 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].first , 0 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].second , 1 );
    BOOST_REQUIRE_EQUAL( found_bridges[1].first , 0 );
    BOOST_REQUIRE_EQUAL( found_bridges[1].second , 3 );
    BOOST_REQUIRE_EQUAL( found_bridges[2].first , 1 );
    BOOST_REQUIRE_EQUAL( found_bridges[2].second , 3 );
    BOOST_REQUIRE_EQUAL( found_bridges[3].first , 3 );
    BOOST_REQUIRE_EQUAL( found_bridges[3].second , 7 );
    BOOST_REQUIRE_EQUAL( found_bridges[4].first , 3 );
    BOOST_REQUIRE_EQUAL( found_bridges[4].second , 6 );
    BOOST_REQUIRE_EQUAL( found_bridges[5].first , 3 );
    BOOST_REQUIRE_EQUAL( found_bridges[5].second , 5 );

}

BOOST_AUTO_TEST_CASE( test6_txt )
{
    auto tested_graph= load("test6.txt");
    std::vector<std::pair< size_t, size_t> > found_bridges= tested_graph.find_bridge();
    BOOST_REQUIRE_EQUAL( found_bridges.size(), 6 );
    BOOST_REQUIRE_EQUAL( tested_graph.get_vertex_number(), 11 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].first , 1 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].second , 3 );
    BOOST_REQUIRE_EQUAL( found_bridges[1].first , 3 );
    BOOST_REQUIRE_EQUAL( found_bridges[1].second , 4 );
    BOOST_REQUIRE_EQUAL( found_bridges[2].first , 3 );
    BOOST_REQUIRE_EQUAL( found_bridges[2].second , 9 );
    BOOST_REQUIRE_EQUAL( found_bridges[3].first , 6 );
    BOOST_REQUIRE_EQUAL( found_bridges[3].second , 7 );
    BOOST_REQUIRE_EQUAL( found_bridges[4].first , 6 );
    BOOST_REQUIRE_EQUAL( found_bridges[4].second , 8 );
    BOOST_REQUIRE_EQUAL( found_bridges[5].first , 8 );
    BOOST_REQUIRE_EQUAL( found_bridges[5].second , 9 );
}

BOOST_AUTO_TEST_CASE( test7_txt )
{
    auto tested_graph= load("test7.txt");
    std::vector<std::pair< size_t, size_t> > found_bridges= tested_graph.find_bridge();
    BOOST_REQUIRE_EQUAL( found_bridges.size(), 8 );
    BOOST_REQUIRE_EQUAL( tested_graph.get_vertex_number(), 12 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].first , 0 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].second , 6 );
    BOOST_REQUIRE_EQUAL( found_bridges[1].first , 1 );
    BOOST_REQUIRE_EQUAL( found_bridges[1].second , 10 );
    BOOST_REQUIRE_EQUAL( found_bridges[2].first , 1 );
    BOOST_REQUIRE_EQUAL( found_bridges[2].second , 6 );
    BOOST_REQUIRE_EQUAL( found_bridges[3].first , 2 );
    BOOST_REQUIRE_EQUAL( found_bridges[3].second , 6 );
    BOOST_REQUIRE_EQUAL( found_bridges[4].first , 5 );
    BOOST_REQUIRE_EQUAL( found_bridges[4].second , 6 );
    BOOST_REQUIRE_EQUAL( found_bridges[5].first , 6 );
    BOOST_REQUIRE_EQUAL( found_bridges[5].second , 7 );
    BOOST_REQUIRE_EQUAL( found_bridges[6].first , 7 );
    BOOST_REQUIRE_EQUAL( found_bridges[6].second , 8 );
    BOOST_REQUIRE_EQUAL( found_bridges[7].first , 8 );
    BOOST_REQUIRE_EQUAL( found_bridges[7].second , 10 );
}

BOOST_AUTO_TEST_CASE( test8_txt )
{
    auto tested_graph= load("test8.txt");
    std::vector<std::pair< size_t, size_t> > found_bridges= tested_graph.find_bridge();
    BOOST_REQUIRE_EQUAL( found_bridges.size(), 10 );
    BOOST_REQUIRE_EQUAL( tested_graph.get_vertex_number(), 12 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].first , 0 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].second , 10 );
    BOOST_REQUIRE_EQUAL( found_bridges[1].first , 1 );
    BOOST_REQUIRE_EQUAL( found_bridges[1].second , 10 );
    BOOST_REQUIRE_EQUAL( found_bridges[2].first , 2 );
    BOOST_REQUIRE_EQUAL( found_bridges[2].second , 10 );
    BOOST_REQUIRE_EQUAL( found_bridges[3].first , 3 );
    BOOST_REQUIRE_EQUAL( found_bridges[3].second , 10 );
    BOOST_REQUIRE_EQUAL( found_bridges[4].first , 4 );
    BOOST_REQUIRE_EQUAL( found_bridges[4].second , 10 );
    BOOST_REQUIRE_EQUAL( found_bridges[5].first , 5 );
    BOOST_REQUIRE_EQUAL( found_bridges[5].second , 10 );
    BOOST_REQUIRE_EQUAL( found_bridges[6].first , 6 );
    BOOST_REQUIRE_EQUAL( found_bridges[6].second , 10 );
    BOOST_REQUIRE_EQUAL( found_bridges[7].first , 7 );
    BOOST_REQUIRE_EQUAL( found_bridges[7].second , 10 );
    BOOST_REQUIRE_EQUAL( found_bridges[8].first , 8 );
    BOOST_REQUIRE_EQUAL( found_bridges[8].second , 10 );
    BOOST_REQUIRE_EQUAL( found_bridges[9].first , 9 );
    BOOST_REQUIRE_EQUAL( found_bridges[9].second , 10 );
}

BOOST_AUTO_TEST_CASE( test9_txt )
{
    auto tested_graph= load("test9.txt");
    std::vector<std::pair< size_t, size_t> > found_bridges= tested_graph.find_bridge();
    BOOST_REQUIRE_EQUAL( found_bridges.size(), 0 );
    BOOST_REQUIRE_EQUAL( tested_graph.get_vertex_number(), 12 );
}

BOOST_AUTO_TEST_CASE( test10_txt )
{
    auto tested_graph= load("test10.txt");
    std::vector<std::pair< size_t, size_t> > found_bridges= tested_graph.find_bridge();
    BOOST_REQUIRE_EQUAL( found_bridges.size(), 1 );
    BOOST_REQUIRE_EQUAL( tested_graph.get_vertex_number(), 5 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].first , 1 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].second , 4 );
}

BOOST_AUTO_TEST_CASE( test11_txt )
{
    auto tested_graph= load("test11.txt");
    std::vector<std::pair< size_t, size_t> > found_bridges= tested_graph.find_bridge();
    BOOST_REQUIRE_EQUAL( found_bridges.size(), 2 );
    BOOST_REQUIRE_EQUAL( tested_graph.get_vertex_number(), 5 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].first , 1 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].second , 4 );
    BOOST_REQUIRE_EQUAL( found_bridges[1].first , 2 );
    BOOST_REQUIRE_EQUAL( found_bridges[1].second , 4 );
}

BOOST_AUTO_TEST_CASE( test12_txt )
{
    auto tested_graph= load("test12.txt");
    std::vector<std::pair< size_t, size_t> > found_bridges= tested_graph.find_bridge();
    BOOST_REQUIRE_EQUAL( found_bridges.size(), 16 );
    BOOST_REQUIRE_EQUAL( tested_graph.get_vertex_number(), 15 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].first , 0 );
    BOOST_REQUIRE_EQUAL( found_bridges[0].second , 3 );
    BOOST_REQUIRE_EQUAL( found_bridges[1].first , 1 );
    BOOST_REQUIRE_EQUAL( found_bridges[1].second , 3 );
    BOOST_REQUIRE_EQUAL( found_bridges[2].first , 2 );
    BOOST_REQUIRE_EQUAL( found_bridges[2].second , 6 );
    BOOST_REQUIRE_EQUAL( found_bridges[3].first , 2 );
    BOOST_REQUIRE_EQUAL( found_bridges[3].second , 11 );
    BOOST_REQUIRE_EQUAL( found_bridges[4].first , 3 );
    BOOST_REQUIRE_EQUAL( found_bridges[4].second , 4 );
    BOOST_REQUIRE_EQUAL( found_bridges[5].first , 3 );
    BOOST_REQUIRE_EQUAL( found_bridges[5].second , 6 );
    BOOST_REQUIRE_EQUAL( found_bridges[6].first , 4 );
    BOOST_REQUIRE_EQUAL( found_bridges[6].second , 6 );
    BOOST_REQUIRE_EQUAL( found_bridges[7].first , 4 );
    BOOST_REQUIRE_EQUAL( found_bridges[7].second , 11 );
    BOOST_REQUIRE_EQUAL( found_bridges[8].first , 5 );
    BOOST_REQUIRE_EQUAL( found_bridges[8].second , 6 );
    BOOST_REQUIRE_EQUAL( found_bridges[9].first , 6 );
    BOOST_REQUIRE_EQUAL( found_bridges[9].second , 7 );
    BOOST_REQUIRE_EQUAL( found_bridges[10].first , 6 );
    BOOST_REQUIRE_EQUAL( found_bridges[10].second , 8 );
    BOOST_REQUIRE_EQUAL( found_bridges[11].first , 8 );
    BOOST_REQUIRE_EQUAL( found_bridges[11].second , 10 );
    BOOST_REQUIRE_EQUAL( found_bridges[12].first , 10 );
    BOOST_REQUIRE_EQUAL( found_bridges[12].second , 11 );
    BOOST_REQUIRE_EQUAL( found_bridges[13].first , 11 );
    BOOST_REQUIRE_EQUAL( found_bridges[13].second , 14 );
    BOOST_REQUIRE_EQUAL( found_bridges[14].first , 11 );
    BOOST_REQUIRE_EQUAL( found_bridges[14].second , 13 );
    BOOST_REQUIRE_EQUAL( found_bridges[15].first , 11 );
    BOOST_REQUIRE_EQUAL( found_bridges[15].second , 12 );
}

#endif




#endif // BOOST_TEST_H_INCLUDED

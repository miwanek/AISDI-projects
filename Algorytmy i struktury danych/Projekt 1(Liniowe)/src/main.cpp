#include <cstddef>
#include <cstdlib>
#include <string>
#include <iostream>
#include "Vector.h"
#include "LinkedList.h"
#include <chrono>


namespace
{
template <typename T>
    using Vector = aisdi::Vector<T>;

    template <typename T>
    using List = aisdi::LinkedList<T>;


    void Test_append(int a)
    {
        List <std::string> collection_list;


        Vector <std::string> collection_vector;
        auto clock_start_vector = std::chrono::high_resolution_clock::now();
        for(int i=1;i<=a;i++)
        {

            collection_vector.append("text");

        }
        auto clock_end_vector = std::chrono::high_resolution_clock::now();
        std::cout<<"Appending:   "<<a<<" elements for vector takes: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_end_vector-clock_start_vector).count()<<" nanoseconds \n";


        auto clock_start_list = std::chrono::high_resolution_clock::now();
        for(int i=1;i<+a;i++)
        {
            collection_list.append("text");
        }
        auto clock_end_list = std::chrono::high_resolution_clock::now();
        std::cout<<"Appending:   "<<a<<" elements for list takes:  "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_end_list-clock_start_list).count()<<" nanoseconds \n";


    }

    void Test_prepend(int a)
    {
        List <std::string> collection_list;
        Vector <std::string> collection_vector;

        auto clock_start_vector = std::chrono::high_resolution_clock::now();
        for(int i=1;i<=a;i++)
        {

            collection_vector.prepend("text");

        }
        auto clock_end_vector = std::chrono::high_resolution_clock::now();
        std::cout<<"Prepending: "<<a<<" elements for vector takes: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_end_vector-clock_start_vector).count()<<" nanoseconds \n";


        auto clock_start_list = std::chrono::high_resolution_clock::now();
        for(int i=1;i<+a;i++)
        {
            collection_list.prepend("text");
        }
        auto clock_end_list = std::chrono::high_resolution_clock::now();
        std::cout<<"Prepending: "<<a<<" elements for list takes: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_end_list-clock_start_list).count()<<" nanoseconds \n";


    }
    void Test_ErasingAllElements(int a)
    {
        List <std::string> collection_list;
        Vector <std::string> collection_vector;
        for(int i=1;i<a;i++)
        {
            collection_list.append("text");
            collection_vector.append("text");
        }

        auto clock_start_vector = std::chrono::high_resolution_clock::now();
        collection_vector.erase(collection_vector.begin(),collection_vector.end());
        auto clock_end_vector = std::chrono::high_resolution_clock::now();
        std::cout<<"Erasing all: ("<<a<<") elements from vector take:  "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_end_vector-clock_start_vector).count()<<" nanoseconds \n";


        auto clock_start_list = std::chrono::high_resolution_clock::now();
        collection_list.erase(collection_list.begin(),collection_list.end());
        auto clock_end_list = std::chrono::high_resolution_clock::now();
        std::cout<<"Erasing all: ("<<a<<") elements from list takes: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_end_list-clock_start_list).count()<<" nanoseconds \n";

    }

    void Test_pop_first(int a)
    {
        int b=2*a;
        List <std::string> collection_list;
        Vector <std::string> collection_vector;
        for(int i=1;i<b;i++)
        {
            collection_list.append("text");
            collection_vector.append("text");
        }
        auto clock_start_vector = std::chrono::high_resolution_clock::now();
        for(int i=1;i<=a;i++)
        {
            collection_vector.popFirst();

        }
        auto clock_end_vector = std::chrono::high_resolution_clock::now();
        std::cout<<"Pop first: "<<a<<" elements for vector takes: "<<std::chrono::duration_cast<std::chrono::microseconds>(clock_end_vector-clock_start_vector).count()<<" microseconds \n";


        auto clock_start_list = std::chrono::high_resolution_clock::now();
        for(int i=1;i<+a;i++)
        {
            collection_list.popFirst( );
        }
        auto clock_end_list = std::chrono::high_resolution_clock::now();
        std::cout<<"Pop first: "<<a<<" elements for list takes: "<<std::chrono::duration_cast<std::chrono::microseconds>(clock_end_list-clock_start_list).count()<<" microseconds \n";


    }


    void Test_delete_middle(int a)
    {
        int b=2*a;
        List <std::string> collection_list;
        Vector <std::string> collection_vector;
        for(int i=1;i<b;i++)
        {
            collection_list.append("text");
            collection_vector.append("text");
        }
        auto clock_start_vector = std::chrono::high_resolution_clock::now();
        for(int i=1;i<=a;i++)
        {

            collection_vector.insert(collection_vector.begin()+a,"text");

        }
        auto clock_end_vector = std::chrono::high_resolution_clock::now();
        std::cout<<"Deleting middle: "<<a<<" elements for vector takes: "<<std::chrono::duration_cast<std::chrono::microseconds >(clock_end_vector-clock_start_vector).count()<<" microseconds \n";


        auto clock_start_list = std::chrono::high_resolution_clock::now();
        for(int i=1;i<+a;i++)
        {
            collection_list.insert(collection_list.begin()+a,"text");
        }
        auto clock_end_list = std::chrono::high_resolution_clock::now();
        std::cout<<"Deleting middle: "<<a<<" elements for list takes: "<<std::chrono::duration_cast<std::chrono::microseconds >(clock_end_list-clock_start_list).count()<<" microseconds \n";


    }

}
 // namespace

int main(int argc, char** argv)
{
    const std::size_t repeatCount = argc > 1 ? std::atoll(argv[1]) : 10000;
    //for (std::size_t i = 0; i < repeatCount; ++i)
       // perfomTest();
    Test_ErasingAllElements(100);
    Test_ErasingAllElements(100000);
    Test_pop_first(100);
    Test_pop_first(10000);
    Test_append(100);
    Test_append(1000000);
    Test_prepend(100);
    Test_prepend(10000);
    Test_delete_middle( 1000);
    return 0;
}

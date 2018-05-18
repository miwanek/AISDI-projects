#include <cstddef>
#include <cstdlib> /* srand, rand */
#include <string>

#include <ctime>       /* time */
#include "TreeMap.h"
#include "HashMap.h"
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>


namespace
{
  template <typename K, typename V>
    using TreeMap = aisdi::TreeMap<K, V >;

    template <typename K, typename V>
    using HashMap = aisdi::HashMap< K, V>;


    void Test_add(size_t a)
    {
        TreeMap <int, std::string> collection_tree;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::vector<int> key;
        for (size_t i = 0; i < a; ++i)
        {
                    key.push_back(i);
        }

        shuffle (key.begin(), key.end(), std::default_random_engine(seed));

        HashMap <int, std::string> collection_hash;
        auto clock_start_TreeMap = std::chrono::high_resolution_clock::now();
        for(size_t  i=0; i< a ; ++i)
        {

           collection_tree[ key[i] ]= "alibaba";

        }
        auto clock_end_TreeMap = std::chrono::high_resolution_clock::now();
        std::cout<<"Adding:   "<<a<<" elements for TreeMap takes: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_end_TreeMap-clock_start_TreeMap).count()<<" nanoseconds \n";


        auto clock_start_HashMap = std::chrono::high_resolution_clock::now();
        for(size_t i=1;i<=a; ++i)
        {
            collection_hash[i]= "alibaba";
        }
        auto clock_end_HashMap = std::chrono::high_resolution_clock::now();
        std::cout<<"Adding:   "<<a<<" elements for HashMap takes:  "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_end_HashMap-clock_start_HashMap).count()<<" nanoseconds \n";


    }
    void Test_remove(size_t a)
    {
        TreeMap <int, std::string> collection_tree;
        HashMap <int, std::string> collection_hash;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::vector<int> key;
        for (size_t i = 1; i <= a; ++i)
        {
                    key.push_back(i);
        }

        shuffle (key.begin(), key.end(), std::default_random_engine(seed));
        for(size_t  i=0; i< a ; ++i)
        {

           collection_tree[ key[i] ]= "alibaba";

        }

        auto clock_start_TreeMap = std::chrono::high_resolution_clock::now();
        for(size_t  i=1; i<= a ; ++i)
        {

           collection_tree.remove( i ) ;

        }
        auto clock_end_TreeMap = std::chrono::high_resolution_clock::now();
        std::cout<<"Removing:   "<<a<<" elements for TreeMap takes: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_end_TreeMap-clock_start_TreeMap).count()<<" nanoseconds \n";

        for(size_t i=1; i<=a; ++i)
        {
            collection_hash[i]= "alibaba";
        }

        auto clock_start_HashMap = std::chrono::high_resolution_clock::now();
        for(size_t i=0; i< a ; ++i)
        {
            collection_hash.remove( key[i] );
        }
        auto clock_end_HashMap = std::chrono::high_resolution_clock::now();
        std::cout<<"Removing:   "<<a<<" elements for HashMap takes:  "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_end_HashMap-clock_start_HashMap).count()<<" nanoseconds \n";


    }

    void Test_change(size_t a)
    {
        TreeMap <int, std::string> collection_tree;
        HashMap <int, std::string> collection_hash;
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::vector<int> key;
        for (size_t i = 1; i <= a; ++i)
        {
                    key.push_back(i);
        }

        shuffle (key.begin(), key.end(), std::default_random_engine(seed));
        for(size_t  i=0; i< a ; ++i)
        {

           collection_tree[ key[i] ]= "alibaba";

        }

        auto clock_start_TreeMap = std::chrono::high_resolution_clock::now();
        for(size_t  i=1; i <= a ; ++i )
        {

           collection_tree[ i ] = "kałamarnica" ;

        }
        auto clock_end_TreeMap = std::chrono::high_resolution_clock::now();
        std::cout<<"Modifing:   "<<a<<" elements for TreeMap takes: "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_end_TreeMap-clock_start_TreeMap).count()<<" nanoseconds \n";

        for(size_t i=1; i<=a; ++i)
        {
            collection_hash[i]= "alibaba";
        }

        auto clock_start_HashMap = std::chrono::high_resolution_clock::now();
        for(size_t i=0; i< a ; ++i)
        {
            collection_hash[ i ] = "kałamarnica" ;
        }
        auto clock_end_HashMap = std::chrono::high_resolution_clock::now();
        std::cout<<"Modifing:   "<<a<<" elements for HashMap takes:  "<<std::chrono::duration_cast<std::chrono::nanoseconds>(clock_end_HashMap-clock_start_HashMap).count()<<" nanoseconds \n";


    }



//template <typename K, typename V>
//using Map = aisdi::Map<K, V>;

  //Map<int, std::string> map;
 // map[1] = "TODO";

} // namespace

int main(int argc, char** argv)
{
    srand(time(NULL));
    const std::size_t repeatCount = argc > 1 ? std::atoll(argv[1]) : 10000;
  //for (std::size_t i = 0; i < repeatCount; ++i)
  //  perfomTest();

      Test_add(100);
      Test_add(30000);
      Test_add(3000000);
      Test_remove(100);
      Test_remove(30000);
      Test_remove(3000000);
      Test_change(100);
      Test_change(30000);
      Test_change(3000000);


  return 0;
}

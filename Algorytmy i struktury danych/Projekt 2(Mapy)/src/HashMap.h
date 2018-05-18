#ifndef AISDI_MAPS_HASHMAP_H
#define AISDI_MAPS_HASHMAP_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <list>
#include <iostream>

#define t_size 30000

namespace aisdi
{

template <typename KeyType, typename ValueType>
class HashMap
{
public:
  using key_type = KeyType;
  using mapped_type = ValueType;
  using value_type = std::pair<const key_type, mapped_type>;
  using size_type = std::size_t;
  using reference = value_type&;
  using const_reference = const value_type&;

  class ConstIterator;
  class Iterator;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

private:

        friend class HashMap<KeyType, ValueType>::ConstIterator;
        std::hash < key_type > hash_function;
        static const size_type table_size = t_size;
        std::list<value_type>hash_node[t_size];
        size_type map_size;

        void add_new_element(const key_type& key, int nr_index)
        {
            hash_node[nr_index].push_back(value_type(key, mapped_type{}));
            ++map_size;
        }
        void add_new_element(value_type  data )
        {
            int nr_index= hash_function(data.first) % t_size;
            hash_node[nr_index].push_back( data );
            ++map_size;
        }
        void erase_all()
        {
            for(size_t i =0; i< t_size; i++)
            {
                hash_node[i].clear();
            }
            map_size= 0;
        }

public:
  HashMap(): map_size(0)
  {}

  HashMap(std::initializer_list<value_type> list):HashMap()
  {
        for(auto i=list.begin(); i!=list.end();i++)
        {
            add_new_element(  *i );
        }
  }

  HashMap(const HashMap& other):HashMap()
  {
        hash_function= other.hash_function;
        for(auto it= other.begin(); it!= other.end(); ++it)
        {
            add_new_element(*it);
        }
  }

  HashMap(HashMap&& other):HashMap()
  {
        hash_function=other.hash_function;
        map_size= other.map_size;
        for( size_t i = 0; i< t_size; ++i)
        {
            hash_node[i]= std::move( other.hash_node[i] );
        }
  }

  HashMap& operator=(const HashMap& other)
  {
    if(this != &other) {
         erase_all();
         hash_function= other.hash_function;
         for(auto it= other.begin(); it!= other.end(); ++it)
         {
            add_new_element(*it);
         }
    }
    return *this;
  }

  ~HashMap() { map_size = 0;}

  HashMap& operator=(HashMap&& other)
  {
     if(this != &other)
     {
        hash_function=other.hash_function;
        map_size= other.map_size;
        for( size_t i = 0; i< t_size; ++i)
        {
            hash_node[i]= std::move( other.hash_node[i] );
        }
    }
    return *this;
  }

  bool isEmpty() const
  {
    return !map_size;
  }

  mapped_type& operator[](const key_type& key)
  {
     auto it=find(key);
     if( it != cend())  return (*it).second;
     int nr_index= hash_function(key) % t_size;
     add_new_element( key , nr_index);
     return (*(hash_node[nr_index].rbegin())).second;

  }

  const mapped_type& valueOf(const key_type& key) const
  {
    auto it= find(key);
    if(it == cend() ) throw std::out_of_range("There is no node");
    return (*it).second;

  }

  mapped_type& valueOf(const key_type& key)
  {
    auto it= find(key);
    if(it == cend() ) throw std::out_of_range("There is no node");
    return (*it).second;
  }

  const_iterator find(const key_type& key) const
  {
     int nr_index= hash_function(key) % t_size;
     for(auto it= hash_node[nr_index].begin(); it != hash_node[nr_index].end(); ++it  )
     {
        if( (*it).first == key  ) return const_iterator(this,  it, nr_index);
     }
     return cend();
  }

  iterator find(const key_type& key)
  {
    return static_cast<const HashMap<KeyType, ValueType>*>(this)->find(key);
  }

  void remove(const key_type& key)
  {
    remove(find((key)));
  }

  void remove(const const_iterator& it)
  {
    if(it == end()) throw std::out_of_range("Out Of Range: Can't remove  element that doesn't exist ");
     int erase_from= it.index;
    // hash_node[erase_from].remove( (*it) );
     hash_node[erase_from].erase( it.value_iterator );
     --map_size;
  }

  size_type getSize() const
  {
    return map_size;
  }

  bool operator==(const HashMap& other) const
  {
    if(map_size != other.map_size) return false;
    auto other_it= other.begin();
    for(auto it = begin(); it!= end(); ++it, ++other_it)
    {
        if( *it != *other_it) return false;
    }
    return true;
  }

  bool operator!=(const HashMap& other) const
  {
    return !(*this == other);
  }

  iterator begin()
  {
    return cbegin();
  //  return cbegin();
  }

  iterator end()
  {
    return iterator (this, hash_node[t_size -1].end(), t_size-1 );
  }

  const_iterator cbegin() const
  {
    if(map_size == 0 ) return cend();
    for( size_t i =0; i< t_size ; i++ )
    {
        if(hash_node[i].begin() != hash_node[i].end() )
        {
            return const_iterator(this, hash_node[i].begin(), i );
        }
    }
    return cend();
  }

  const_iterator cend() const
  {
    return const_iterator(this, hash_node[t_size -1].end(), t_size-1 );
  }

  const_iterator begin() const
  {
    return cbegin();
  }

  const_iterator end() const
  {
    return cend();
  }
};

template <typename KeyType, typename ValueType>
class HashMap<KeyType, ValueType>::ConstIterator
{
public:
  using reference = typename HashMap::const_reference;
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename HashMap::value_type;
  using pointer = const typename HashMap::value_type*;

private:
        const HashMap *currentMap;
        typename std::list< value_type >::const_iterator value_iterator;
        size_type index;
        friend void HashMap<KeyType, ValueType>::remove(const const_iterator&);
        friend mapped_type& HashMap<KeyType, ValueType>::operator[](const key_type& key);

public:


  explicit ConstIterator()
  {}

  ConstIterator(const HashMap * new_map,  typename std::list< value_type >::const_iterator new_iterator, size_type new_index ):
     currentMap(new_map), value_iterator(new_iterator), index(new_index)
  {}

  ConstIterator(const ConstIterator& other): ConstIterator(other.currentMap, other.value_iterator, other.index)
  { }

  ConstIterator& operator++()
  {
    if(currentMap->map_size == 0 || *this == currentMap->end() ) throw std::out_of_range("nothing to decrement");
    auto it= currentMap->hash_node[index].end();
    --it;
    if(it != value_iterator)
    {
        ++value_iterator;

    }
    else
    {
        do
        {
            ++index;
        }
        while(currentMap->hash_node[index].begin() == currentMap->hash_node[index].end()  && index< t_size-1 );

       value_iterator= currentMap->hash_node[index].begin();
    }

    return *this;
  }

  ConstIterator operator++(int)
  {
        auto result = *this;
        operator++();
        return result;
  }

  ConstIterator& operator--()
  {
    if(currentMap->map_size == 0) throw std::out_of_range("nothing to decrement");
    if(currentMap->hash_node[index].begin() != value_iterator)
    {
        --value_iterator;

    }
    else
    {
        while(currentMap->hash_node[index].end() == currentMap->hash_node[index].begin()  )
        {
            --index;
            if(index< 0 ) throw std::out_of_range("no more elements");
        }
       value_iterator= currentMap->hash_node[index].end();
        --value_iterator;
    }
    return *this;

  }

  ConstIterator operator--(int)
  {
        auto result = *this;
        operator--();
        return result;
  }

  reference operator*() const
  {
    if(value_iterator == currentMap->hash_node[t_size -1].end()) throw std::out_of_range("no data");
    return *value_iterator;
  }

  pointer operator->() const
  {
    return &this->operator*();
  }

  bool operator==(const ConstIterator& other) const
  {
     return ( currentMap == other.currentMap   && index == other.index  && value_iterator== other.value_iterator  );
  }

  bool operator!=(const ConstIterator& other) const
  {
    return !(*this == other);
  }
};

template <typename KeyType, typename ValueType>
class HashMap<KeyType, ValueType>::Iterator : public HashMap<KeyType, ValueType>::ConstIterator
{
public:
  using reference = typename HashMap::reference;
  using pointer = typename HashMap::value_type*;

  explicit Iterator()
  {}

  Iterator(const HashMap * new_map,  typename std::list< value_type >::const_iterator new_iterator, size_type new_index) : ConstIterator(new_map, new_iterator, new_index) {}

  Iterator(const ConstIterator& other)
    : ConstIterator(other)
  {}

  Iterator& operator++()
  {
    ConstIterator::operator++();
    return *this;
  }

  Iterator operator++(int)
  {
    auto result = *this;
    ConstIterator::operator++();
    return result;
  }

  Iterator& operator--()
  {
    ConstIterator::operator--();
    return *this;
  }

  Iterator operator--(int)
  {
    auto result = *this;
    ConstIterator::operator--();
    return result;
  }

  pointer operator->() const
  {
    return &this->operator*();
  }

  reference operator*() const
  {
    // ugly cast, yet reduces code duplication.
    return const_cast<reference>(ConstIterator::operator*());
  }
};

}

#endif /* AISDI_MAPS_HASHMAP_H */

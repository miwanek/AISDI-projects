#ifndef AISDI_LINEAR_LINKEDLIST_H
#define AISDI_LINEAR_LINKEDLIST_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace aisdi
{

template <typename Type>
class LinkedList
{
public:
  using difference_type = std::ptrdiff_t;
  using size_type = std::size_t;
  using value_type = Type;
  using pointer = Type*;
  using reference = Type&;
  using const_pointer = const Type*;
  using const_reference = const Type&;

  class ConstIterator;
  class Iterator;
  using iterator = Iterator;
  using const_iterator = ConstIterator;

  struct element
  {
      pointer data;
      element* next;
      element* previous;

      element( )
      {
          next= nullptr;
          previous= nullptr;
          data= nullptr;
      }
      element( Type item)
      {
          next= nullptr;
          previous=nullptr;
          data= new Type(item);
      }

      ~element()
      {
          next= nullptr;
          previous= nullptr;
          delete data;
      }

  };

private:
    element* head;
    element* tail;
    size_type length;

public:

  LinkedList()
  {
    length = 0;
    head= new element;
    tail= new element;
    head->next= nullptr;
    head->previous= tail;
    tail->next= head;
    tail->previous= nullptr;
   // tail->data=nullptr;
   // head->data=nullptr;
  }

  LinkedList(std::initializer_list<Type> l): LinkedList()
  {
    for( auto i= l.begin(); i!=l.end(); i++)
    {
        append(*i);
    }
  }

  LinkedList(const LinkedList& other): LinkedList()
  {
    for( auto i = other.begin(); i!= other.end(); ++i)
    {
        append(*i);
    }
  }

  LinkedList(LinkedList&& other)
  {
    head= other.head;
    tail= other.tail;
    length= other.length;  //przenosimy dane z tymczasowej listy

    other.head= nullptr;
    other.tail=nullptr;
    other.length= 0;
  }

  ~LinkedList()
  {
    while(isEmpty() == false)
    {
        erase(begin());
    }
    delete tail;
    delete head;
  }

  LinkedList& operator=(const LinkedList& other)
  {
    if( this == &other)
    {
       return *this;
    }
    erase(begin(),end());
    for( auto it= other.begin(); it!= other.end(); ++it)
    {
        append(*it);
    }
    return *this;
  }

  LinkedList& operator=(LinkedList&& other)
  {
    erase(begin(),end()); // usuwamy wszystkie dnae z naszej listy
    delete head;
    delete tail;

    head= other.head;
    tail= other.tail;
    length= other.length;  //przenosimy dane z tymczasowej listy

    other.head= nullptr;
    other.tail=nullptr;
    other.length= 0;
    return *this;
  }

  bool isEmpty() const
  {
    //if(length== 0) return true;
    //else return false;
    return !length;
  }

  size_type getSize() const
  {
    return length;
  }

  void append(const Type& item)
  {
    element* pom= new element(item);
    pom->previous= head->previous;
    pom->next= head;
    head->previous->next= pom;
    head->previous= pom;
    ++length;
  }

  void prepend(const Type& item)
  {
    element* pom= new element(item);
    pom->next= tail->next;
    pom->previous= tail;
    tail->next->previous = pom;
    tail->next = pom;
    ++length;
  }

  void insert(const const_iterator& insertPosition, const Type& item)
  {
    if( insertPosition == begin() )
    {
        prepend(item);
    }
    else if( insertPosition == end() )
    {
        append(item);
    }
    else
    {
        element* pom= new element(item);
        pom->previous= insertPosition.current->previous;
        pom->next= insertPosition.current;
        insertPosition.current->previous->next = pom;
        insertPosition.current->previous= pom;
        ++length;
    }

  }
  Type popFirst()
  {
    //if( isEmpty()== true) throw std::out_of_range("Nothing to pop");
    Type deleted = *(begin());
    erase(begin() );
    return deleted;
  }

  Type popLast()
  {
    if( isEmpty()== true) throw std::out_of_range("Nothing to pop");
    Type deleted = *(--end());
    erase(--end() );
    return deleted;
  }

  void erase(const const_iterator& possition)
  {
    if( possition.current == head || possition.current == tail ) throw std::out_of_range("Nothing to erase");
    possition.current->previous->next = possition.current->next;
    possition.current->next->previous = possition.current->previous;
    delete possition.current;
    --length;

  }

  void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded)
  {
    auto i= firstIncluded;
    while(i!= lastExcluded)
    {
        i++;
        erase(i-1);
    }
  }

  iterator begin()
  {
    return iterator(tail->next);
  }

  iterator end()
  {
    return iterator(head) ;
  }

  const_iterator cbegin() const
  {
    return const_iterator(tail-> next);
  }

  const_iterator cend() const
  {
    return const_iterator(head);
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

template <typename Type>
class LinkedList<Type>::ConstIterator
{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename LinkedList::value_type;
  using difference_type = typename LinkedList::difference_type;
  using pointer = typename LinkedList::const_pointer;
  using reference = typename LinkedList::const_reference;
private:
    element* current;
    friend void LinkedList <Type>::erase(const const_iterator&);
    friend void LinkedList <Type>::insert(const const_iterator& insertPosition, const Type& item);
public:

  explicit ConstIterator(element* point= nullptr ) : current( point )
  {}



  reference operator*() const
  {
    if(current->next == nullptr || current->previous == nullptr  ) throw std::out_of_range("Out of range.");
    return *(current->data);
   // throw std::runtime_error("TODO");
  }

  ConstIterator& operator++()
  {
    if(current->next == nullptr) throw std::out_of_range("Out of range.");
    current= current->next;
    return *this;
    //throw std::runtime_error("TODO");
  }

  ConstIterator operator++(int)
  {
    ConstIterator last= *this;
    operator++();
    return last;
    //throw std::runtime_error("TODO");
  }

  ConstIterator& operator--()
  {
    if(current->previous->previous == nullptr  ) throw std::out_of_range("Out of range.");
    current= current->previous;
    return *this;
  }

  ConstIterator operator--(int)
  {
    ConstIterator last= *this;
    operator--();
    return last;
   // throw std::runtime_error("TODO");
  }

  ConstIterator operator+(difference_type d) const // Sprawdzamy czy dana nam liczba jest ujemna czy dodatnia a potem przesuwamy się tyle razy po liście
  {
    auto result = *this;
    if(d >= 0)
    {
        for(int i = 0; i < d; ++i )
        {
            ++result;
        }
    }
    else
    {
        for(int i = 0; i > d; --i )
        {
            --result;
        }
    }
    return result;

    //throw std::runtime_error("TODO");
  }

  ConstIterator operator-(difference_type d) const // Zamieniamy liczbe na przeciwną i odsyłamy do operacji plus
  {

    d= -d;
    return operator+( d );

    //throw std::runtime_error("TODO");
  }

  bool operator==(const ConstIterator& other) const
  {
     return this->current == other.current;
    //  (void)other;
   // throw std::runtime_error("TODO");
  }

  bool operator!=(const ConstIterator& other) const
  {
    return this->current != other.current;
  }
};

template <typename Type>
class LinkedList<Type>::Iterator : public LinkedList<Type>::ConstIterator
{
public:
  using pointer = typename LinkedList::pointer;
  using reference = typename LinkedList::reference;

  explicit Iterator( element* added = nullptr): const_iterator(added)
  { }


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

  Iterator operator+(difference_type d) const
  {
    return ConstIterator::operator+(d);
  }

  Iterator operator-(difference_type d) const
  {
    return ConstIterator::operator-(d);
  }

  reference operator*() const
  {
    // ugly cast, yet reduces code duplication.
    return const_cast<reference>(ConstIterator::operator*());
  }
};

}

#endif // AISDI_LINEAR_LINKEDLIST_H

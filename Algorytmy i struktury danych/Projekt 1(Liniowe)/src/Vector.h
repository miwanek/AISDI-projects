#ifndef AISDI_LINEAR_VECTOR_H
#define AISDI_LINEAR_VECTOR_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>

#define Initial_capacity 10
namespace aisdi
{

template <typename Type>
class Vector
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
private:
    size_t capacity;
    size_t length;
    Type* data;
    Type* last;

  void resize(size_t i= 1)
  {
    if(length + i <= capacity) return ;
    else
    {


        while(capacity< length+ i)
        {
            capacity*= 2 ;
        }
        Type* pom= new Type[capacity];
        Type* j=pom;

      const_iterator it = cbegin();

      for(; it != cend(); ++j, ++it)
      {
          *j = *it;
      }
        delete [] data;
      data = pom;
      last = j;

    }
  }
  void Rshift(const const_iterator& position )
   {
    if(isEmpty())
    {
      ++last;
      return;
    }

    iterator ite = end();
    ++last;
    for(; ite != position; --ite)
    {
        *(ite) = *(ite-1);
    }
  //  *(ite+1) = *ite;

   }

  void Rshift( int position )
   {
    if(isEmpty())
    {
      ++last;
      return;
    }

    ++last;
    for( int i= length; i>=position; --i)
    {
        data[i] = data[i-1];
    }
   }
 void Lshift( const const_iterator& position_from, const const_iterator& position_to )
  {
    iterator to = iterator(position_to.pointed, *this);

    for( const_iterator from = position_from ; from != cend(); ++to, ++from)
    {
            *to = *from;
    }
    last = to.pointed;
  }

public:
  Vector()
  {
    length=0;
    capacity= Initial_capacity;
    last = data = new Type[Initial_capacity];
  }

  Vector(size_t to_alloc)
  {
    length=0;
    capacity= to_alloc;
    last = data = new Type[to_alloc];
  }

  Vector(std::initializer_list<Type> l)
  {
    length=0;
    capacity=l.size();
    last = data = new Type[capacity];
    for( auto i= l.begin(); i!=l.end(); i++ )
    {
        append(*i);
    }
  }

  Vector(const Vector& other):Vector()
  {
    for(const_iterator ite = other.cbegin(); ite != other.cend(); ++ite )
    {
              append(*ite);
    }
  }

  Vector(Vector&& other)
  {
     data= other.data;
     last= other.last;
     length= other.length;
     capacity= other.capacity;
     other.data= nullptr;
     other.last= nullptr;
     other.length= 0;
     other.capacity= Initial_capacity;
  }

  ~Vector()
  {
    last = nullptr;
    length = 0;
    capacity = 0;
    delete[] data;
    data = nullptr;
  }


  Vector& operator=(const Vector& other)
  {
    if( this == &other)
    {
       return *this;
    }
    erase(cbegin(), cend());
    for(const_iterator ite = other.cbegin(); ite != other.cend(); ++ite )
    {
              append(*ite);
    }
    return *this;

  }

  Vector& operator=(Vector&& other)
  {
     delete [] data;
     data= other.data;
     last= other.last;
     length= other.length;
     capacity= other.capacity;
     other.data= nullptr;
     other.last= nullptr;
     other.length= 0;
     other.capacity= Initial_capacity;
     return *this;
  }

  bool isEmpty() const
  {
    return !length;
  }

  size_type getSize() const
  {
    return length;
  }

  void append(const Type& item)
  {
    resize();
    *(last) = item;
    ++last;
    ++length;
  }

  void prepend(const Type& item)
  {
    resize();
    Rshift(cbegin());
    *data = item;
    ++length;
  }

  void insert(const const_iterator& insertPosition, const Type& item)
  {
    if(insertPosition == cend())
    {
      append(item);
      return;
    }
    if(insertPosition == cbegin())
    {
      prepend(item);
      return;
    }
    size_t loop=0;
    if(capacity-length == 0)
    {
        for(auto it= begin(); it!= insertPosition; ++it)
        {
            ++loop;
        }
        resize();
        Rshift(loop);
        data[loop]= item;
    }
    else
    {
        Rshift(insertPosition);
     *( (iterator)insertPosition ) = item;
    }
    ++length;

  }

  Type popFirst()
  {
    if(isEmpty()) throw std::logic_error("Nothing to pop.");
    Type removed = *data;
    Lshift(cbegin()+1, cbegin());
    --length;
    return removed;
  }

  Type popLast()
  {
    if(isEmpty()) throw std::logic_error("Nothing to pop.");
    --length;
    return *(--last);
  }

  void erase(const const_iterator& possition)
  {
    if(isEmpty()) throw std::out_of_range("Nothing to erase.");

    if(possition == cend()) throw std::out_of_range("Wrong position");

    if(possition == cend()-1)
    {
      popLast();
      return;
    }
    Lshift(possition+1, possition);
    --length;
  }

  void erase(const const_iterator& firstIncluded, const const_iterator& lastExcluded)
  {
    if(isEmpty()) throw std::out_of_range("Erasing in an empty vector.");

    if(firstIncluded == lastExcluded) return;

    length -= lastExcluded.pointed - firstIncluded.pointed;
    Lshift(lastExcluded, firstIncluded);
  }

  iterator begin()
  {
    return iterator(data,  *this);
  }

  iterator end()
  {
    return iterator(last, *this);
  }

  const_iterator cbegin() const
  {
    return const_iterator( data,  *this  );
  }

  const_iterator cend() const
  {
    return const_iterator( last, *this );
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
class Vector<Type>::ConstIterator
{
public:
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename Vector::value_type;
  using difference_type = typename Vector::difference_type;
  using pointer = typename Vector::const_pointer;
  using reference = typename Vector::const_reference;

private:
    const Vector<Type>& vect;
    Type* pointed;
    friend class Vector;
    //friend void Vector<Type>::erase(const const_iterator& , const const_iterator& );
  //  friend void Vector<Type>::Lshift( const const_iterator& position_from, const const_iterator& position_to );
public:
  explicit ConstIterator(Type* point, const Vector<Type>& v ): vect(v),pointed(point)
  {}

  reference operator*() const
  {
    if(this->pointed == vect.last ) throw std::out_of_range("Out of range.");
    return *pointed;
  }

  ConstIterator& operator++()
  {
    if(pointed == vect.last) throw std::out_of_range("Out of range.");
    ++pointed;
    return *this;
  }

  ConstIterator operator++(int)
  {
    if(pointed == vect.last) throw std::out_of_range("Out of range.");
    ConstIterator pom= *this;
    ++pointed;
    return pom;
  }

  ConstIterator& operator--()
  {
    if(pointed == vect.data) throw std::out_of_range("Out of range.");
    --pointed;
    return *this;
  }

  ConstIterator operator--(int)
  {
    if(pointed == vect.data) throw std::out_of_range("Out of range.");
    ConstIterator pom= *this;
    --pointed;
    return pom;
  }

  ConstIterator operator+(difference_type d) const
  {
    if(pointed + d > vect.last) throw std::out_of_range("Out of range.");

    return ConstIterator(pointed + d, vect );
  }

  ConstIterator operator-(difference_type d) const
  {
    if(pointed - d < vect.data ) throw std::out_of_range("Out of range.");

    return ConstIterator(pointed - d, vect );
  }

  bool operator==(const ConstIterator& other) const
  {
        if(pointed== other.pointed) return true;
        else return false;
  }

  bool operator!=(const ConstIterator& other) const
  {
        if(pointed != other.pointed) return true;
        else return false;
  }

};

template <typename Type>
class Vector<Type>::Iterator : public Vector<Type>::ConstIterator
{
public:
  using pointer = typename Vector::pointer;
  using reference = typename Vector::reference;

  explicit Iterator(Type *point, const Vector<Type>& v): ConstIterator(point, v)
  {}

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

#endif // AISDI_LINEAR_VECTOR_H

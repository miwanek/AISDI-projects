#ifndef AISDI_MAPS_TREEMAP_H
#define AISDI_MAPS_TREEMAP_H

#include <cstddef>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <queue>

namespace aisdi
{

template <typename KeyType, typename ValueType>
class TreeMap
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


  struct node
  {
      value_type data;
      node* parent;
      node* left;
      node* right;

     // node( key_type d ): data.first(d),  parent(nullptr), left(nullptr), right(nullptr)
    //   { }
      node( value_type d ): data(d), parent(nullptr), left(nullptr), right(nullptr) {}

     // node( value_type d , node* p): data(d), parent(nullptr), left(nullptr), right(nullptr) {}

    //  node( value_type d , node* l, node* r ): data(d), parent(nullptr), left(l), right(r) {}

    //  node( value_type d , node* p, node* l, node* r ): data(d), parent(nullptr), left(l), right(r) {}

      ~node()
      {

          left= nullptr;
          right= nullptr;
          parent= nullptr;
      }

  };


private:

    node* root;
    size_t tree_size;

    void erase_all(node* to_delete)
    {
      /*  if(!to_delete) return;
        erase_all(to_delete->left);
        erase_all(to_delete->right);
        delete to_delete;
        --tree_size; */

        std::queue<node*> que;
        node* pom;

      que.push(to_delete);
      while(!que.empty())
      {
        pom = que.front();
        que.pop();
        if( pom != nullptr )
         {
          que.push( pom->left );
          que.push( pom->right );
          delete pom;
          --tree_size;
         }
        }

    }

     node* search_node(const key_type& key) const
     {
        node* pom= root;
        while( pom != nullptr)
        {
            if(pom->data.first == key ) return pom;
            if(pom->data.first > key) pom=pom->left;
            else
            {
                pom=pom->right;
            }
        }
        return nullptr;
     }
     void insert_node(node* new_node)
     {
        ++tree_size;
        if(root == nullptr)
        {
            root= new_node;
            return;

        }
        node* pom= root;
        while( true )
        {
            if(new_node->data.first> pom->data.first)
            {
                if (pom->right == nullptr)
                 {
                    pom->right = new_node;
                    new_node->parent = pom;
                    break;
                }
                else
                {
                    pom=pom->right;
                }
            }
            else
            {
                if (pom->left == nullptr)
                 {
                    pom->left = new_node;
                    new_node->parent = pom;
                    break;
                }
                else
                {
                    pom=pom->left;
                }
            }
        }
     }


public:

  TreeMap(): root(nullptr), tree_size(0)
  {}

  TreeMap(std::initializer_list<value_type> list):TreeMap()
  {
    for( auto i= list.begin(); i!=list.end(); ++i)
    {
        insert_node(new node(*i)  );
    }
  }

  ~TreeMap()
  {
        if(root!=nullptr) erase_all(root);
        tree_size=0;
        root=nullptr;
  }


  TreeMap(const TreeMap& other):TreeMap()
  {
      std::queue<node*> que;
      node* pom;

      que.push(other.root);
      while(!que.empty())
      {
        pom = que.front();
        que.pop();
        if( pom != nullptr ) {
          que.push( pom->left );
          que.push( pom->right );
          insert_node( new node( pom->data) );
        }
      }
  }

  TreeMap(TreeMap&& other)
  {
    if( &other != this)
    {
        root = other.root;
        other.root = nullptr;
        tree_size = other.tree_size;
        other.tree_size = 0;
    }
  }

  TreeMap& operator=(const TreeMap& other)
  {
     if( this != &other)
     {
      erase_all(root);
      root=nullptr;
      std::queue<node*> que;
      node* pom;

      que.push(other.root);
      while(!que.empty())
      {
        pom = que.front();
        que.pop();
        if( pom != nullptr ) {
          que.push( pom->left );
          que.push( pom->right );
          insert_node( new node( pom->data) );
        }
      }
    }
    return *this;
  }

  TreeMap& operator=(TreeMap&& other)
  {
        erase_all(root);
        root = other.root;
        other.root = nullptr;
        tree_size = other.tree_size;
        other.tree_size = 0;
        return *this;
  }

  bool isEmpty() const
  {
    return !tree_size;
  }

  mapped_type& operator[](const key_type& key)
  {
    auto it = find(key);
    if(it == end())
    {
        node* new_node=new node(value_type(key, mapped_type{}) );
        insert_node(new_node);
        it= const_iterator(new_node,this);

    }
    return (*it).second;
  }

  const mapped_type& valueOf(const key_type& key) const
  {
    const_iterator cit = find(key);
    if(cit == cend()) throw std::out_of_range("Out of range");
    return (*cit).second;
  }

  mapped_type& valueOf(const key_type& key)
  {
    auto it = find(key);
    if(it == end()) throw std::out_of_range("Out Of Range");
    return (*it).second;
  }

  const_iterator find(const key_type& key) const
  {
    return ConstIterator(search_node(key), this);
  }

  iterator find(const key_type& key)
  {
    return Iterator(search_node(key), this);
  }

  void remove(const key_type& key)
  {
    remove(find(key));
  }

  void remove(const const_iterator& it)
  {
    if(it == end()) throw std::out_of_range("Out Of Range");

    node* current = it.current_node;

    if (current->left == nullptr && current-> right == nullptr) // no children
    {
       if( current->parent )
       {
            if(current->parent->left== current )
            {
                current->parent->left= nullptr;
            }
            else
            {
                current->parent->right= nullptr;
            }
        }
        else
        {
            root=nullptr;
        }
    }
    else if( current->left == nullptr && current-> right != nullptr ) /// one children -> right
    {
        if( current->parent )
        {
            if(current->parent->right== current )
            {
                current->parent->right= current->right;
            }
            else
            {
                current->parent->left= current->right;
            }
            current->right->parent= current->parent;
        }
        else
        {
            root= current->right;
            current->right->parent= nullptr;
        }
    }
    else if( current->left != nullptr && current-> right == nullptr ) /// one children -> left
    {
        if( current->parent )
        {
            if(current->parent->left== current )
            {
                current->parent->left= current->left;
            }
            else
            {
                current->parent->right= current->left;
            }
            current->left->parent= current->parent;
        }
        else
        {
            root= current->left;
            current->left->parent= nullptr;
        }
    }
    else /// two children
    {
        node* pom= current->right;
        while(pom->left != nullptr)
        {
            pom=pom->left;
        }
        pom->parent->left= nullptr;
        pom->right= current->right;
        pom->left= current->left;
        pom->right->parent= pom;
        pom->left->parent= pom;
        if(current->parent)
        {
            if(current->parent->right == current )
            {
                current->parent->right=pom;
            }
            else
            {
                current->parent->left=pom;
            }

        }
        pom->parent= current->parent;
        if(current == root ) root = pom;
    }
    current->left = current->right = current->parent = nullptr;
    delete current;
    tree_size--;
    if(tree_size == 0) root= nullptr;
  }

  size_type getSize() const
  {
    return tree_size;
  }

  bool operator==(const TreeMap& other) const
  {
        if (other.getSize() != getSize()) return false;
        for (auto iterator = begin(); iterator != end(); iterator++)
        {
            if (other.valueOf((*iterator).first) != (*iterator).second) return false;
        }
        return true;
  }

  bool operator!=(const TreeMap& other) const
  {
    return !(*this == other);
  }

  iterator begin()
  {
    return cbegin();
  }

  iterator end()
  {
    return cend();
  }

  const_iterator cbegin() const
  {
    if(tree_size == 0 )  return cend();
    node* pom= root;
    while(pom->left)
    {
        pom= pom->left;
    }
    return const_iterator(pom, this);
  }

  const_iterator cend() const
  {
    return const_iterator(nullptr, this);
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
class TreeMap<KeyType, ValueType>::ConstIterator
{
public:
  using reference = typename TreeMap::const_reference;
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = typename TreeMap::value_type;
  using pointer = const typename TreeMap::value_type*;


private:
     node* current_node;
    const TreeMap* current_tree;
    friend void TreeMap<KeyType, ValueType>::remove(const const_iterator& it);

public:

  explicit ConstIterator()
  {}

  ConstIterator(  node* current , const TreeMap*  tree ): current_node(current), current_tree(tree) {}

  ConstIterator(const ConstIterator& other)
  {
    current_node= other.current_node;
    current_tree= other.current_tree;
  }

  ConstIterator& operator++()
  {
    if( current_node == nullptr || current_tree== nullptr )  throw std::out_of_range("Can't increment NULL");

    if(current_node->right )
    {
        current_node = current_node->right;
        while(current_node->left!= nullptr)
        {
            current_node = current_node->left;
        }
    }
    else
    {   // idziemy do góry aż trafimy aż trafimy na rodzica dla którego węzeł był lewym dzieckiem

        node* par= current_node->parent;
        while(  par != nullptr && par->right == current_node )
        {
            current_node= par;
            par= par->parent;
        }
        current_node=par;

    }

    return *this;
  }

  ConstIterator operator++(int)
  {
    auto pom= *this;
    operator++();
    return pom;
  }

  ConstIterator& operator--()
  {
    if( current_tree->root == nullptr || current_tree== nullptr )  throw std::out_of_range("Can't decrement NULL");

    if( current_node == nullptr)
    {
        current_node= current_tree->root;
        while(current_node->right)
        {
            current_node=current_node->right;
        }
        return *this;
    }
   // node* pom= current_node->;
    if(current_node->left )
    {
        current_node = current_node->left;
        while(current_node->right != nullptr)
        {
            current_node = current_node->right;
        }
    }
    else
    {   // idziemy do góry aż trafimy aż trafimy na rodzica dla którego węzeł był lewym dzieckiem

        node* par= current_node->parent;
        while( par->left == current_node )
        {
            if(par == nullptr ) throw std::out_of_range("Already smallest element");
            current_node= par;
            par= par->parent;
        }
        current_node=par;
    }
    return *this;
  }

  ConstIterator operator--(int)
  {
    auto pom= *this;
    operator--();
    return pom;
  }

  reference operator*() const
  {
    if (current_node == nullptr) throw std::out_of_range("There is no such node ");
    return current_node->data;
  }

  pointer operator->() const
  {
    return &this->operator*();
  }

  bool operator==(const ConstIterator& other) const
  {
    return (current_node == other.current_node);
  }

  bool operator!=(const ConstIterator& other) const
  {
    return (current_node != other.current_node);
  }
};

template <typename KeyType, typename ValueType>
class TreeMap<KeyType, ValueType>::Iterator : public TreeMap<KeyType, ValueType>::ConstIterator
{
public:
  using reference = typename TreeMap::reference;
  using pointer = typename TreeMap::value_type*;

  explicit Iterator()
  {}

  Iterator(node* current , TreeMap*  tree ) : ConstIterator( current , tree ) {}

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

#endif /* AISDI_MAPS_MAP_H */

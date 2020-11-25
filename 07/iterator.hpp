#pragma once

template<class Container>
class Iterator : public std::iterator<std::forward_iterator_tag, typename Container::value_type>
{
public:
    using pointer = typename Container::value_type *;
    using value_type = typename Container::value_type;  

private:
    pointer current_;
    
    friend Container;
    
    Iterator(pointer); 
    
public:
    Iterator(const Iterator &);
    
    bool operator ==(const Iterator &) const;
    bool operator !=(const Iterator &) const;
    
    typename Iterator<Container>::value_type &operator *() const;
    Iterator &operator ++();
    Iterator operator ++(int);
    
};


template<class Container>
class ReverseIterator : public std::iterator<std::forward_iterator_tag, typename Container::value_type>
{
public:
    using pointer = typename Container::value_type *;
    using value_type = typename Container::value_type;  

private:
    pointer current_;
    
    friend Container;
    
    ReverseIterator(pointer); 
    
public:
    ReverseIterator(const ReverseIterator &);
    
    bool operator ==(const ReverseIterator &) const;
    bool operator !=(const ReverseIterator &) const;
    
    typename ReverseIterator<Container>::value_type &operator *() const;
    ReverseIterator &operator ++();
    ReverseIterator operator ++(int);
    
};

#include "iterator.tpp"


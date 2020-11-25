#pragma once


/* Forward */
template<class Container>
Iterator<Container>::Iterator(pointer p) : current_{p} {}


template<class Container>
Iterator<Container>::Iterator(const Iterator &it) : current_{it.current_} {}
    
template<class Container>
bool Iterator<Container>::operator ==(const Iterator &other) const {
    return current_ == other.current_;
}

template<class Container>
bool Iterator<Container>::operator !=(const Iterator &other) const {
    return current_ != other.current_;
}


template<class Container>
typename Iterator<Container>::value_type &Iterator<Container>::operator *() 
        const {
    return *current_;
}

template<class Container>
Iterator<Container> &Iterator<Container>::operator ++() {
    ++current_;
    return *this;
}

template<class Container>
Iterator<Container> Iterator<Container>::operator ++(int) {
    Iterator tmp(*this);
    ++current_;
    return tmp;
}


/* Reverse */
template<class Container>
ReverseIterator<Container>::ReverseIterator(pointer p) : current_{p} {}


template<class Container>
ReverseIterator<Container>::ReverseIterator(const ReverseIterator &it) : current_{it.current_} {}
    
template<class Container>
bool 
ReverseIterator<Container>::operator ==(const ReverseIterator &other) const {
    return current_ == other.current_;
}

template<class Container>
bool 
ReverseIterator<Container>::operator !=(const ReverseIterator &other) const {
    return current_ != other.current_;
}


template<class Container>
typename ReverseIterator<Container>::value_type &
ReverseIterator<Container>::operator *() const {
    return *current_;
}

template<class Container>
ReverseIterator<Container> &ReverseIterator<Container>::operator ++() {
    --current_;
    return *this;
}

template<class Container>
ReverseIterator<Container> ReverseIterator<Container>::operator ++(int) {
    ReverseIterator tmp(*this);
    --current_;
    return tmp;
}


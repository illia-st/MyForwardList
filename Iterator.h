#pragma once

#include <cstddef>
#include <iterator>
#include "Core.h"
// It would be nice to create class ConstIterator for cbegin() cend()
template <class T>
class Iterator{
private:
    using difference_type   = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using node = Node<value_type>;
    using pointer = node*;
    using reference = value_type&;
    using iterator_type = Iterator<value_type>;

    friend MyForwardList<value_type>;
public:
    explicit Iterator(pointer ptr = nullptr): m_ptr(ptr), before_begin(false) { }
    Iterator(const iterator_type& iterator){
        *this = iterator;
    }
    Iterator(iterator_type&& iterator) noexcept{
        *this = iterator;
    }
    virtual ~Iterator() = default;
    Iterator& operator = (const iterator_type& iterator){
        this->m_ptr = iterator.m_ptr;
        return *this;
    }
    Iterator& operator = (iterator_type&& iterator) noexcept{
        this->m_ptr = iterator.m_ptr;
        iterator.m_ptr = nullptr;
        return *this;
    }
    bool operator == (const iterator_type& iterator) const{
        return this->m_ptr == iterator.m_ptr;
    }
    bool operator != (const iterator_type& iterator) const{
        return this->m_ptr != iterator.m_ptr;
    }
    iterator_type& operator ++(){
        if(m_ptr == nullptr){
            std::string error{"Your iterator is out of range, please check your code at line " +
                              std::to_string(__LINE__) + ", file " + __FILE__};
            throw std::out_of_range(error);
        }
        // before begin is not implemented well due to the lack of time
        m_ptr = m_ptr->next;
        return *this;
    }
    const iterator_type operator ++(int){
        if(m_ptr == nullptr){
            std::string error{"Your iterator is out of range, please check your code at line " +
                              std::to_string(__LINE__) + ", file " + __FILE__};
            throw std::out_of_range(error);
        }
        iterator_type temp(*this);
        m_ptr = m_ptr->next;

        return temp;
    }
    reference operator *() const{
        if(m_ptr == nullptr){
            std::string error{"Your iterator is out of range, please check your code at line " +
                              std::to_string(__LINE__) + ", file " + __FILE__};
            throw std::out_of_range(error);
        }
        return m_ptr->val;
    }

protected:
    pointer m_ptr;
    bool before_begin;
};
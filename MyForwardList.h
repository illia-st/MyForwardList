#pragma once
#include <memory>
#include <functional>
#include "Core.h"
#include "Node.h"
#include "Iterator.h"

// I prefer to use Raw pointers in such tasks to reduce overhead
// anyway I will have to write a custom destructor and periodically use reset


template <class T>
class MyForwardList final{


    using value_type = T;
    using node = Node<value_type>;
    using pointer = node*;
    using iterator = Iterator<value_type>;
    using size_type = std::size_t;

    using SplitPredicate = std::function<bool(const value_type&)>;

public:
    MyForwardList(): ptr(nullptr), m_size(0) { }

    MyForwardList(const MyForwardList& other): ptr(nullptr), m_size(0){
        *this = other;
    }
    MyForwardList(MyForwardList&& other) noexcept: ptr(nullptr), m_size(0){
        *this = std::move(other);
    }
    MyForwardList(std::initializer_list<value_type> init): ptr(nullptr), m_size(0){
        *this = init;
    }
    ~MyForwardList(){
        clear();
    }
    MyForwardList& operator = (const MyForwardList& other){
        if(other.ptr == nullptr) return *this;
        pointer temp = other.ptr;
        ptr = new node(temp->val);
        pointer this_temp = ptr;
        while(temp->next != nullptr){
            this_temp->next = new node(temp->next->val);
            temp = temp->next;
        }
        this->m_size = other.m_size;
        return *this;
    }
    MyForwardList& operator = (MyForwardList&& other) noexcept{
        this->ptr = other.ptr;
        this->m_size = other.m_size;
        other.ptr = nullptr;
        other.m_size = 0;
        return *this;
    }
    MyForwardList& operator = (std::initializer_list<value_type> init){
        if(!init.size()){
            this->clear();
            return *this;
        }
        pointer temp = nullptr;
        bool first_element {true};
        for(const auto& value: init){
            if(first_element){
                temp = new node(std::move(value));
                first_element = false;
                ptr = temp;
            }else{
                temp->next = new node(std::move(value));
                temp = temp->next;
            }
        }
        this->m_size = init.size();
        return *this;
    }
    void clear(){
        while(ptr != nullptr){
            pointer temp_ptr = ptr;
            ptr = ptr->next;
            delete temp_ptr;
        }
    }
    void push_front(const T& value){
        if(ptr == nullptr){
            ptr = new node(value);
        }else{
            pointer new_head = new node(value, ptr);
            ptr = new_head;
        }
        ++m_size;
    }
    void push_front(T&& value){
        if(ptr == nullptr){
            ptr = new node(std::move(value));
        }else{
            pointer new_head = new node(std::move(value), ptr);
            ptr = new_head;
        }
        ++m_size;
    }
    iterator insert_after( const iterator& pos, const T& value ){
        if(pos.m_ptr == nullptr){
            std::string error{"Your iterator is out of range, please check your code at line " +
                              std::to_string(__LINE__) + ", file " + __FILE__};
            throw std::out_of_range(error);
        }
        if(pos.m_ptr->next == nullptr){
            pos.m_ptr->next = new node(value);
        }else{
            pointer after_inserted = pos.m_ptr->next;
            pos.m_ptr->next = new node(value, after_inserted);
        }
        ++m_size;
        return iterator(pos.m_ptr->next);
    }

    iterator insert_after( const iterator& pos, T&& value ){
        if(pos.m_ptr == nullptr){
            std::string error{"Your iterator is out of range, please check your code at line " +
                              std::to_string(__LINE__) + ", file " + __FILE__};
            throw std::out_of_range(error);
        }
        if(pos.m_ptr->next == nullptr){
            pos.m_ptr->next = new node(std::move(value));
        }else{
            pointer after_inserted = pos.m_ptr->next;
            pos.m_ptr->next = new node(std::move(value), after_inserted);
        }
        ++m_size;
        return iterator(pos.m_ptr->next);
    }

    void pop_front(){
        if(ptr == nullptr){
            std::string error{"Your forward list is empty, please check your code at line " +
                              std::to_string(__LINE__) + ", file " + __FILE__};
            throw std::out_of_range(error);
        }
        pointer temp = ptr;
        ptr = ptr->next;
        delete temp;
    }
    // this method can invalidate iterators
    MyForwardList<value_type> split_when(const SplitPredicate& predicate){
        MyForwardList<value_type> ans;

        if(this->m_size == 0) return ans;

        bool first_iteration = true;
        pointer temp_ptr = ptr, tail = nullptr;
        size_type diff {};
        while(temp_ptr != nullptr && !predicate(temp_ptr->val)){
            tail = temp_ptr;
            temp_ptr = temp_ptr->next;
            ++diff;
        }
        // no elements have returned true
        if(temp_ptr == nullptr){
            return ans;
        }
        // first element has returned true
        if(tail == nullptr) {
            ptr = nullptr;
        }else{
            tail->next = nullptr;
        }

        ans.ptr = temp_ptr;
        ans.m_size = this->m_size - diff;
        this->m_size = diff;

        return ans;
    }
    std::size_t size() const{
        return m_size;
    }
    bool empty() const{
        return m_size == 0;
    }
    iterator begin(){
        return iterator(ptr);
    }
    iterator end(){
        return iterator(nullptr);
    }
    iterator before_begin(){
        iterator it(nullptr);
        it.before_begin = true;
        return it;
    }
    iterator erase_after(const iterator& pos){
        // to make erase_after work correctly we need to implement before_begin iterator
        if(pos.m_ptr == nullptr){
            std::string error{"Your iterator is out of range, please check your code at line " +
                              std::to_string(__LINE__) + ", file " + __FILE__};
            throw std::out_of_range(error);
        }
        if(pos.m_ptr->next == nullptr){
            return end();
        }
        pointer temp = pos.m_ptr->next;
        pos.m_ptr->next = temp->next;

        delete temp;
        temp = nullptr;

        return iterator(pos.m_ptr->next);
    }

private:
    pointer ptr;
    size_type m_size;
};

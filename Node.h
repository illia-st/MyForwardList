#pragma once

template <class T>
struct Node{
    using pointer = Node*;
    using value_type = T;
    explicit Node(const value_type& value, pointer next_ = nullptr): val(value), next(next_) { }
    explicit Node(value_type&& value, pointer next_ = nullptr): val(std::move(value)), next(next_) { }
    pointer next {nullptr};
    T val {};
};
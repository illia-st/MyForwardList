#include <iostream>
#include <forward_list>
#include "MyForwardList.h"

// quick testing

int main() {
    MyForwardList<int> l{1,3,4};
    l.insert_after(++(++l.begin()), 2);
    for(const auto& el: l){
        std::cout << el << " ";
    }
    std::cout << std::endl;
    auto l2 = l.split_when([](int i){return i == 3;});
    for(const auto& el: l2){
        std::cout << el << " ";
    }
    std::cout << std::endl;
    for(const auto& el: l){
        std::cout << el << " ";
    }
    std::cout << std::endl;
    l2.erase_after(l2.begin());
    l2.erase_after(l2.begin());
    l2.erase_after(l2.begin());
    l2.erase_after(l2.begin());
    l2.erase_after(l2.begin());
    l2.erase_after(l2.begin());
//    exception
//    l2.erase_after(l2.end());
    for(const auto& el: l2){
        std::cout << el << " ";
    }
    std::cout << std::endl;
    std::string line {"world"};
    MyForwardList<std::string> l3;
    l3.push_front(line);
    std::cout << line << std::endl;
    line = "Hello";
    l3.push_front(std::move(line));
    std::cout << line << std::endl;
    for(const auto& el: l3){
        std::cout << el << " ";
    }
    std::cout << std::endl << l3.size() << std::endl;
    l3.pop_front();
    l3.pop_front();
    line = "Hello";
    l3.push_front(line);
    std::cout << line << std::endl;
    line = "world";
    l3.insert_after(l3.begin(), std::move(line));
    std::cout << line << std::endl;
    for(const auto& el: l3){
        std::cout << el << " ";
    }
    std::cout << std::endl;

    auto l4 (std::move(l3));
    std::cout << "l3" << std::endl;
    for(const auto& el: l3){
        std::cout << el << " ";
    }
    std::cout << std::endl;
    std::cout << "l4" << std::endl;
    for(const auto& el: l4){
        std::cout << el << " ";
    }
    std::cout << std::endl;
    return 0;
}

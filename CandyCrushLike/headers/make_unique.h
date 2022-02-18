//
// Created by Daniel Chiquet on 18/02/2022.
//

#include <iostream>

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}


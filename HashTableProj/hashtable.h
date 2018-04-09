//
// Created by sinimawath on 31.03.18.
//

#ifndef HASHTABLEPROJ_HASHTABLE_H
#define HASHTABLEPROJ_HASHTABLE_H

#include <algorithm>

constexpr static int gcd();

// Переделать на шаблоны
template <class T>
class HashTable{
public:

    HashTable();
    HashTable(const HashTable& other) = delete;
    HashTable(HashTable&& other) noexcept { *this = std::move(other); }
    ~HashTable();

    HashTable& operator=(const HashTable& other) = delete;
    HashTable& operator=(HashTable&& other) noexcept ;

    bool Add(const T& value);
    bool Remove(const T& value);
    bool Has(const T& value) const;
    bool ReHash();

private:
    struct Node;

    Node** buffer_;
    int bufferSize_;
    int size_;

    void free();
};

#include "hashtable.hpp"
// Переделать на hpp
#endif //HASHTABLEPROJ_HASHTABLE_H

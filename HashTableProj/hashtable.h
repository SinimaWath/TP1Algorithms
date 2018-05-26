//
// Created by sinimawath on 31.03.18.
//

#ifndef HASHTABLEPROJ_HASHTABLE_H
#define HASHTABLEPROJ_HASHTABLE_H

#include <algorithm>

template <class T, class HashFunction>
class HashTable{
public:

    HashTable() = delete;

    HashTable(HashFunction hash);
    HashTable(const HashTable& other) = delete;
    HashTable(HashTable&& other) noexcept { *this = std::move(other); }
    ~HashTable() noexcept ;

    HashTable& operator=(const HashTable& other) = delete;
    HashTable& operator=(HashTable&& other) noexcept ;

    bool Add(const T& value);
    bool Remove(const T& value);
    bool Has(const T& value ) const;
    bool ReHash();

    void Show();

    HashFunction hash_;

private:
    int bufferSize_;
    int size_;
    T *buffer_;
    char *bufferCondition_;
    int a;

    inline int probing(int hash, int i) const;
    void free() noexcept ;
};


#include "hashtable.hpp"

#endif //HASHTABLEPROJ_HASHTABLE_H

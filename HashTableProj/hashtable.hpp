
#include <cstring>
#include <string>
#include <ostream>
#include <iterator>

template<class T, class HashFunction>
HashTable<T,HashFunction>::HashTable(HashFunction hash): bufferSize_(8), size_(0), buffer_(new T[bufferSize_]),
    hash_(hash), bufferCondition_(new char[bufferSize_]), a(3) {

    memset(bufferCondition_, 0, bufferSize_* sizeof(char));

}


template<class T, class HashFunction>
inline int HashTable<T, HashFunction>::probing(const int hash, int i) const {
    return hash + i % bufferSize_;
}


template<class T, class HashFunction>
bool HashTable<T, HashFunction>::Add(const T& value) {

    if (Has(value)){
        return false;
    }

    int hashKey = hash_(value, a, bufferSize_);

    // hash(k, 0) = hashKey
    int hashProb = hashKey;
    int i = 1;


    while (bufferCondition_[hashProb] != 0 && bufferCondition_[hashProb] != -1 && i < size_) {
        hashProb = probing(hashProb, i++) % bufferSize_;
    }

    buffer_[hashProb] = value;
    bufferCondition_[hashProb] = 1;

    size_++;

    if (static_cast<double>(size_)/bufferSize_ >= 0.75){
        ReHash();
        //std::cout << "HashTable size " << size_ << "buffer Size " << bufferSize_ << "\n";
    }

    return true;

}

template<class T, class HashFunction>
bool HashTable<T, HashFunction>::ReHash(){

    T* prevBuffer = buffer_;
    char* prevBufferCondition = bufferCondition_;

    delete[] buffer_;
    delete[] bufferCondition_;

    a*=3;
    bufferSize_<<=1;
    size_ = 0;

    buffer_ = new T[bufferSize_];
    bufferCondition_ = new char[bufferSize_];

    memset(bufferCondition_, 0, bufferSize_ * sizeof(char));

    for (int i = 0; i < bufferSize_>>1; i++)
        if (prevBufferCondition[i] == 1){
            Add(prevBuffer[i]);
        }

    delete[] prevBuffer;
    delete[] prevBufferCondition;
    return true;

}

template<class T, class HashFunction>
bool HashTable<T, HashFunction>::Remove(const T& value) {

    const int hashKey = hash_(value, a, bufferSize_);

    // hash(k, 0) = hashKey
    int hashProbe = hashKey;
    int i = 1;

    while(bufferCondition_[hashProbe] != 0){
        if (buffer_[hashProbe] == value && bufferCondition_[hashProbe] != -1){
            bufferCondition_[hashProbe] = -1;
            size_--;
            return true;
        }else
            hashProbe = probing(hashProbe, i++) % bufferSize_;
    }

    return false;
}

template<class T, class HashFunction>
bool HashTable<T, HashFunction>::Has(const T& value) const {
    const int hashKey = hash_(value, a, bufferSize_);

    int hashProb = hashKey;
    int i = 1;

    while (bufferCondition_[hashProb] != 0 && i < size_){
        if (buffer_[hashProb] == value && bufferCondition_[hashProb] != -1)
            return true;
        else
            hashProb = probing(hashProb, i++) % bufferSize_;
    }


    return false;
}

template<class T, class HashFunction>
HashTable<T, HashFunction>::~HashTable() noexcept {
    free();
}

template<class T, class HashFunction>
HashTable<T, HashFunction> &HashTable<T, HashFunction>::operator=(HashTable<T, HashFunction> &&other) noexcept {

    if (this == &other)
        return *this;

    free();

    buffer_ = other.buffer_;
    bufferSize_ = other.bufferSize_;
    size_ = other.size_;

    hash_ = other.hash_;
    other.hash_ = nullptr;
    other.buffer_ = nullptr;

    return *this;
}

template<class T, class HashFunction>
void HashTable<T, HashFunction>::Show() {

    for (int i = 0; i < bufferSize_; i++)
        if (bufferCondition_[i] == 1)
            std::cout << i << ") " << buffer_[i] << "\n";

}


template<class T, class HashFunction>
void HashTable<T, HashFunction>::free() noexcept{
    delete[] bufferCondition_;
    delete[] buffer_;
}


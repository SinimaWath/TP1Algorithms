
#include <cstring>
#include <string>

//TODO: переделать на шаблоны
//TODO: вместо hash использовать std::hash - это функтор
// HashTable<T>::methods
// TODO: resize buffer



template <class T>
struct HashTable<T>::Node{
    T value;
    Node* next = nullptr;

    explicit Node(const T& valueOther): value(std::move(valueOther)) {}
};

template<class T>
HashTable<T>::HashTable(): bufferSize_(8), size_(0) {
    buffer_ = new Node*[bufferSize_];

    memset(buffer_, 0, bufferSize_ * sizeof(Node*));

}

template <class T>
bool HashTable<T>::Add(const T& value) {
    if (Has(value)){
        return false;
    }

    const int hashKey = std::hash<T>()(value) % bufferSize_;

    //while (buffer_[hashKey++ % bufferSize_] != nullptr) {}

    //buffer_[hashKey] = Node(value);

    Node* newNode = new Node(value);

    newNode->next = buffer_[hashKey];
    buffer_[hashKey] = newNode;

    //TODO: проверка на переполнение
    size_++;

    if (static_cast<double>(size_)/bufferSize_ > 0.75){
        ReHash();
    }

    return true;

}

template<class T>
bool HashTable<T>::ReHash(){

}

template <class T>
bool HashTable<T>::Remove(const T& value) {
    // TODO: проверить

    const int hashKey = std::hash<T>()(value) % bufferSize_;

    if (buffer_[hashKey] == nullptr)
        return false;

    Node* node = buffer_[hashKey];

    if (node->value == value){
        buffer_[hashKey] = node->next;

        delete node;
        return true;

    }


    while ( node->next != nullptr){
        if (node->next->value == value) {

            Node* next = node->next;
            node->next = next->next;
            size_--;

            delete next;
            return true;
        }
        node = node->next;
    }

}

template <class T>
bool HashTable<T>::Has(const T& value) const {
    const int hashKey = std::hash<T>()(value) % bufferSize_;
    const Node* node = buffer_[hashKey];

    while ( node != nullptr){
        if (node->value == value)
            return true;

        node = node->next;
    }

    return false;
}

template <class T>
HashTable<T>::~HashTable(){
    free();
}

template <class T>
HashTable<T> &HashTable<T>::operator=(HashTable<T> &&other) noexcept {

    if (this == &other)
        return *this;

    free();

    buffer_ = other.buffer_;
    bufferSize_ = other.bufferSize_;
    size_ = other.size_;

    other.buffer_ = nullptr;

    // TODO: Дописать
    return *this;
}

/*template<class T>
void HashTable<T>::free() noexcept{
    for (int i = 0; i < bufferSize_; i++)
        delete buffer_[i];

    delete[] buffer;
}*/

template <class T>
void HashTable<T>::free(){
    for ( int i = 0; i < bufferSize_; i++){
        while( buffer_[i] != nullptr){
            Node* toDelete = buffer_[i];
            buffer_[i] = toDelete->next;
            delete toDelete;
        }
    }

    delete buffer_;
}

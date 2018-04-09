#include<iostream>
#include<cassert>

using namespace std;
class Heap{
public:
    Heap();
    Heap(int size);
    Heap(int* src, const int size);
    ~Heap();
    Heap(const Heap&);
    Heap& operator=(const Heap&);
    Heap(Heap&&) noexcept;
    Heap& operator=(Heap&&) noexcept;

    int extractMin();
    void insert(int);
    int size() const;
    void displayHeap() const;
    bool isEmpty() const;
    static Heap createHeap(int*, const int);
private:
    int* heapBuffer_;
    int heapRealSize_;
    int bufferSize_; 

    static int getParent(const int index);
    static int getLeftChild(const int index);
    static int getRightChild(const int index);

    void siftUp(int index);
    void siftDown(int index);
};

Heap::Heap(): heapRealSize_(0), bufferSize_(16) {
    heapBuffer_ = nullptr;
}

Heap::Heap(int size): heapRealSize_(0), bufferSize_(size){
    heapBuffer_ = new int[bufferSize_];
}

Heap::Heap(int* arr, const int size): heapRealSize_(size), bufferSize_(size){ 
    
    heapBuffer_ = new int[bufferSize_];
    std::copy(arr, arr + bufferSize_, heapBuffer_ );
}

Heap::Heap(const Heap& other): heapRealSize_(other.heapRealSize_), bufferSize_(other.bufferSize_){
    heapBuffer_ = new int[bufferSize_];
    std::copy(other.heapBuffer_, other.heapBuffer_ + bufferSize_, heapBuffer_);
}

Heap::Heap(Heap&& other) noexcept : heapRealSize_(other.heapRealSize_), bufferSize_(other.bufferSize_) {
    delete[] heapBuffer_;
    heapBuffer_ = other.heapBuffer_;
    other.heapBuffer_ = nullptr;

}

Heap& Heap::operator=(const Heap& other){
    if (this == &other)
        return *this;

    delete[] heapBuffer_;
    heapRealSize_ = other.heapRealSize_;
    bufferSize_ = other.bufferSize_;
    heapBuffer_ = new int[bufferSize_];
    std::copy(other.heapBuffer_, other.heapBuffer_ + bufferSize_, heapBuffer_);

    return *this;    
}

Heap& Heap::operator=(Heap&& other) noexcept{
    if (this == &other)
        return *this;

    delete[] heapBuffer_;
    heapRealSize_ = other.heapRealSize_;
    bufferSize_ = other.bufferSize_;
    heapBuffer_ = other.heapBuffer_;
    
    other.heapBuffer_ = nullptr;

    return *this;
}

Heap::~Heap(){
    delete[] heapBuffer_;
}

Heap Heap::createHeap( int* array, const int length){
    Heap heap(array, length);
    for(int i = heap.size() / 2 ; i >=0 ; --i )
        heap.siftDown(i);

    return heap;
}

int Heap::extractMin(){
    int tmp = heapBuffer_[0];
    heapBuffer_[0] = heapBuffer_[--heapRealSize_];
    siftDown(0);

    return tmp;
}

void Heap::insert(int element){
    heapRealSize_++;
    heapBuffer_[heapRealSize_ - 1] = element;
    siftUp(heapRealSize_ - 1);
}

int Heap::getParent(const int index){
    assert(index >= 0);
    return (index - 1)/2;
}

int Heap::getLeftChild(const int index){
    assert(index >= 0);
    return 2 * index + 1;
}

int Heap::getRightChild(const int index){
    assert(index >= 0);
    return 2*index + 2;
}

void Heap::displayHeap() const{
    if (isEmpty())
        cout << "isEmpty";
    for (int i = 0; i < heapRealSize_; i++)
        cout << heapBuffer_[i] << " ";
}

bool Heap::isEmpty() const{
    return (bufferSize_ == 0 || heapRealSize_ == 0);
}

// 5 2 3 4 6
// 5
// 5 2  7
// 5 2 3 17
// 5 4 3 2 
// 6 5 3 2 4 
// 6 5 3 6

void Heap::siftDown(int index){
    int leftChild = 0, rightChild = 0;
    
    while (2*index + 1 < heapRealSize_){
        leftChild = getLeftChild(index);
        rightChild = getRightChild(index);
        int smallestChild = leftChild;

        if ( rightChild < heapRealSize_ && heapBuffer_[leftChild] > heapBuffer_[rightChild])
            smallestChild = rightChild;

        if (heapBuffer_[index] <= heapBuffer_[smallestChild])
            break;

        std::swap(heapBuffer_[index], heapBuffer_[smallestChild]);

        index = smallestChild;
    }
}

void Heap::siftUp(int index){
    int parent = 0;

    while ( index > 0){
        parent = getParent(index);
        if (heapBuffer_[index] >= heapBuffer_[parent])
            return;
        std::swap(heapBuffer_[index], heapBuffer_[parent]);
        index = parent;
    }    
}

int Heap::size() const{
    return heapRealSize_;
}

int findBestTime(Heap heap){
    int bestTime = 0, currentSum = 0;

    while (heap.size() > 1){
        currentSum = heap.extractMin();
        currentSum += heap.extractMin();
        bestTime += currentSum;
        heap.insert(currentSum);
    }

    return bestTime;
}

int main(){
    int n;
    cin >> n;
    assert(n >= 0);
    Heap heap(n);
    int *inputArr = new int[n];
    ASD;
    for (int i = 0; i < n; i++)
        cin >> inputArr[i];
    
    cout << findBestTime(Heap::createHeap(inputArr, n));

    delete[] inputArr;

    return 0;
}

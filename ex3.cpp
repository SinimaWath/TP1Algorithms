#include<iostream>
#include<cassert>
#include<iterator>
#include<algorithm> 
using namespace std;

class CDeque{
public:
    ~CDeque();
    CDeque(int size):bufferSize_(size), head_(0),tail_(0){
        buffer_ = new int[bufferSize_]; 
    }

    CDeque():bufferSize_(16), head_(0), tail_(0){
        buffer_ = new int[bufferSize_]; }

    CDeque(const CDeque& other);
    CDeque& operator=(const CDeque& other);
    CDeque(CDeque&& other) noexcept;
    CDeque& operator=(CDeque&& other) noexcept;
    
    bool isEmpty(){ return head_ == tail_; }

    void push_back(int element);
    void push_front(int element);
    int pop_back();
    int pop_front();
    void display();
private:    
    int bufferSize_;
    int head_;
    int tail_;
    int *buffer_;

    void resizeBuffer();
};

CDeque& CDeque::operator=(const CDeque& other){
    
    if (this == &other)
        return *this;

    bufferSize_ = other.bufferSize_;
    head_ = other.head_;
    tail_ = other.tail_;
    
    delete[] buffer_;
    
    buffer_ = new int[bufferSize_];
    std::copy(other.buffer_, other.buffer_ + bufferSize_, buffer_);

    return *this;
}

CDeque& CDeque::operator=(CDeque&& other) noexcept {
    
    if (this == &other)
        return *this;

    delete[] buffer_;
    buffer_ = other.buffer_;
    bufferSize_ = other.bufferSize_;
    head_ = other.head_;
    tail_ = other.tail_;

    other.buffer_ = nullptr;
    return *this;
}

CDeque::CDeque(CDeque&& other) noexcept {
    delete[] buffer_;
    buffer_ = other.buffer_;
    
    other.buffer_ = nullptr;
}

CDeque::~CDeque(){
    delete[] buffer_;    
}

CDeque::CDeque(const CDeque& other){
    bufferSize_ = other.bufferSize_;
    head_ = other.head_;
    tail_ = other.tail_;
    buffer_ = new int[bufferSize_];
    std::copy(other.buffer_, other.buffer_ + bufferSize_, buffer_);
}

void CDeque::resizeBuffer(){
    // head указывал на следующий за первый, теперь на первый
    // tail указывал на следующий за последним, теперь на последний

    int prevBufSize = bufferSize_;
    bufferSize_ <<=1;
    
    int *tmp = new int[bufferSize_];
    
    if (head_ > tail_){
        std::copy(buffer_, buffer_ + tail_,  tmp);
        
        for(int i = 0; i < ( prevBufSize - head_ ); i++){
            tmp[bufferSize_ - 1 - i] = buffer_[prevBufSize - 1 - i];
        }

        head_ = bufferSize_ - (prevBufSize - head_);

    }else if (head_ < tail_){
        std::copy(buffer_ + head_, buffer_ + tail_ , tmp + head_ );    
    }
    delete[] buffer_;
    buffer_ = tmp;
}

void CDeque::push_front(int element){
    assert(buffer_ != nullptr);

    if (head_ == (tail_ + 1)%bufferSize_){
        resizeBuffer();    
    }
    
    head_ = ( head_ - 1 + bufferSize_) % bufferSize_;
    buffer_[head_] = element;

}

void CDeque::push_back(int element){
    assert(buffer_ != nullptr);

    if (tail_ == (head_ - 1 + bufferSize_) % bufferSize_){
        resizeBuffer();
    }
    buffer_[tail_] = element;
    tail_ = (tail_ + 1) % bufferSize_;
    
}

int CDeque::pop_back(){
    tail_ = (tail_ - 1 + bufferSize_) % bufferSize_;
    return buffer_[tail_]; 
}

int CDeque::pop_front(){
    int res = buffer_[head_];
    head_ = (head_ + 1) % bufferSize_;
    return res;
}

void CDeque::display(){
    cout << "deq ------------------------" << endl;
    cout << "bufferSize_ : " << bufferSize_ << endl;
    cout << "head_ : " << head_ << "tail_: " << tail_ << endl;
    for(int i = 0; i < bufferSize_; i++)
        cout << i << ") " << buffer_[i] << endl;

    cout << "deq-------------------------" << endl;
}

int main(){

    int commandCount = 0;
    assert(commandCount >= 0);

    CDeque deq(4);
    deq.push_back(1);
    deq.display();
    deq.push_back(2);
    deq.display();
    deq.push_front(3);
    deq.display();
    deq.push_front(4);
    deq.display();
    cout << deq.pop_front() << " " << deq.pop_back();
    return 0;    
}





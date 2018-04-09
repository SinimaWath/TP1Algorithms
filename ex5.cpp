#include<iostream>
#include<vector>
#include<cassert>
#include<utility>

using namespace std;

template<typename T, class Compare>
void merge(const T* arrA, const size_t sizeA, const T* arrB,
        const size_t sizeB, T* result, Compare cmp){
    
    size_t currentIndexA = 0;
    size_t currentIndexB = 0;
    size_t currentIndexResult = 0;
    
    while(currentIndexA < sizeA && currentIndexB < sizeB){
        if (cmp(arrA[currentIndexA], arrB[currentIndexB])){
            result[currentIndexResult] = arrA[currentIndexA++];            
        }else{
            result[currentIndexResult] = arrB[currentIndexB++];
        }     
        
        currentIndexResult++;
    }

    if (currentIndexA < sizeA){
        std::copy(arrA + currentIndexA , arrA + sizeA, result + currentIndexResult);
    } else if (currentIndexB < sizeB){
        std::copy(arrB + currentIndexB , arrB + sizeB, result + currentIndexResult);
    }
}

template<typename T, class Compare>
void mergeSort(T* arr, size_t size, Compare cmp){
    if (size <= 1)
        return;

    int firstLen = size/2;
    int secondLen = size - firstLen;
    mergeSort(arr, firstLen, cmp);
    mergeSort(arr + firstLen, secondLen, cmp);
    T* tmp = new T[size];

    merge(arr, firstLen, arr + firstLen, secondLen, tmp, cmp);
    std::copy(tmp, tmp + size, arr);

    delete[] tmp;

}

void test(int* arr, int size){
    cout << arr[size - 1] << endl;
}

class Date{
public:
    Date() = default;
    
    Date(const Date&) = default;
    Date(Date&&) = default;
    Date& operator=(const Date&) = default;
    Date& operator=(Date&&) = default;

    Date(int day, int month, int year): day_(day), month_(month), year_(year){}
    ~Date(){}  

    void setYear(int year);
    void setDay(int day);
    void setMonth(int month);
    int getYear();
    int getDay();
    int getMonth();
    friend ostream& operator<<(ostream& os, Date& dt);   
    friend istream& operator>>(istream& is, Date& dt);
    friend bool operator<=(const Date&, const Date&);
    friend bool operator<(const Date&, const Date&);
    friend bool operator>=(const Date&, const Date&);
    friend bool operator>(const Date&, const Date&);
    friend bool operator==(const Date&, const Date&);

private:
    int day_, month_, year_;
};

ostream& operator<<(ostream& os, Date& dt){
    os << dt.day_ << " " << dt.month_ << " " << dt.year_;
    return os;
}

istream& operator>>(istream& is, Date& dt){
    is >> dt.day_ >> dt.month_ >> dt.year_;
    return is;
}

bool operator<(const Date& a, const Date& b){
    if (a.year_ < b.year_){
        return true;
    }else if ( a.year_ == b.year_ && a.month_ < b.month_ ){
        return true;
    }else if (a.year_ == b.year_ && a.month_ == b.month_ && a.day_ < b.day_)
        return true;

    return false;
}
bool operator<=(const Date& a, const Date& b){
    if (a.year_ < b.year_){
        return true;
    }else if (a.year_ == b.year_ && a.month_ < b.month_){
        return true;
    }else if (a.year_ == b.year_ && a.month_ == b.month_ && a.day_ <= b.day_)
        return true;

    return false;
 
}

bool operator>(const Date& a, const Date& b){
    if (a.year_ > b.year_){
        return true;
    }else if (a.year_ == b.year_ && a.month_ > b.month_){
        return true;
    }else if (a.year_ == b.year_ && a.month_ == b.month_ && a.day_ > b.day_){
        return true;
    }

    return false;
}

bool operator>=(const Date& a, const Date& b){
    if (a.year_ > b.year_){
        return true;
    }else if (a.year_ == b.year_ && a.month_ > b.month_){
        return true;
    }else if (a.year_ == b.year_ && a.month_ == b.month_ && a.day_ >= b.day_){
        return true;
    }

    return false;
}
bool operator==(const Date& a, const Date& b){
    return a.year_ == b.year_ && a.month_ == b.month_ && a.day_ == b.day_;
}

void Date::setYear(int year){
    year_ = year;
}

int Date::getYear(){
    return year_;
}

int Date::getDay(){
    return day_;
}

int Date::getMonth(){
    return month_;
}

struct PointDate{
    Date point;
    int type;
};

int findMaxContemporaryNumber(vector<pair<Date, Date>> peopleDates){        
    PointDate* dateArray = new PointDate[peopleDates.size() * 2];
    size_t currentIndexDateArr = 0;
    for (decltype(peopleDates.size()) i = 0; i < peopleDates.size(); i++){
        Date birthDay =  peopleDates[i].first;
        Date endDay = peopleDates[i].second;
        Date leftDay(birthDay.getDay(), birthDay.getMonth(), birthDay.getYear() + 18);
        Date rightDay(birthDay.getDay(), birthDay.getMonth(), birthDay.getYear() + 80);

        if (endDay <= leftDay)
            continue;
        if (endDay < rightDay)
            rightDay = endDay;
        
        dateArray[currentIndexDateArr++] = {leftDay, 1};
        dateArray[currentIndexDateArr++] = {rightDay, -1};

    }


    mergeSort(dateArray, currentIndexDateArr,[](const PointDate& a, 
                const PointDate& b){ return a.point <= b.point; });


    int currentMaxNumber = 0;
    int maxNumber = 0;
    for (int i = 0; i < currentIndexDateArr; i++){
        currentMaxNumber+= dateArray[i].type;
        if (currentMaxNumber > maxNumber)
            maxNumber = currentMaxNumber;
    }

    for (decltype(peopleDates.size()) i = 0; i < peopleDates.size()*2;i++){
        cout << dateArray[i].point << " " << dateArray[i].type << endl;
    }
    return maxNumber;
}

int main(){
    int numberOfPeople;
    cin >> numberOfPeople;

    assert(numberOfPeople >= 0);
    
    vector<pair<Date, Date>> peopleDates(numberOfPeople);

    for (int i = 0; i < numberOfPeople; i++)
        cin >> peopleDates[i].first >> peopleDates[i].second;

    int contemporaryNumber = findMaxContemporaryNumber(peopleDates);

    cout << contemporaryNumber;

    return 0;
}

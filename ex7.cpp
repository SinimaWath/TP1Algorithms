#include<iostream>
#include<cmath>
#include<cassert>

using namespace std;


template<class T>
void printArr(T* arr, size_t size){
    for(size_t i = 0; i < size; i++)
        cout << arr[i] << " " ;
}

template<class T>
void readArray(T* arr, size_t size){
    for(size_t i = 0; i < size; i++)
        cin >> arr[i];
}



void countingSortByByte(long long* arr, size_t size, int byte){
    long long *tmpC = new long long[256];
    for(int i = 0; i < 256; i++)
        tmpC[i] = 0;

    for(int i = 0; i < size; i++){
        tmpC[ arr[i]>>(8 * byte) & 255 ]++; // get byte       
    }

    for(int i = 1; i < 256; i++){
        tmpC[i]+=tmpC[i - 1];
    }

    long long* tmpB = new long long[size];

    for(int i = size - 1; i >= 0; --i){
       tmpB[--tmpC[arr[i] >> (8 * byte) &255 ]] = arr[i];
    }


    std::copy(tmpB, tmpB + size, arr);
    delete[] tmpC;
    delete[] tmpB;

}

void LSD(long long* arr, size_t size){

    int bytes = 8;
    for (int i = 0; i < bytes; i++){
        countingSortByByte(arr, size, i);
    }
}


int main(){
    int arrayLength;
    cin >> arrayLength;
    assert( arrayLength >= 0 );

    long long* array = new long long[arrayLength];
    readArray(array, arrayLength);

    LSD(array, arrayLength);

    printArr(array, arrayLength);

    delete[] array;
    return 0;
}

#include<iostream>
#include<cassert>
#include<random>
#include<ctime>

using namespace std;

template<class T>
void readArray(T* arr, int size){
    for(int i = 0; i < size; i++){
        cin >> arr[i];
    }
}

template<class T>
void printArray(T* arr, size_t size){
    for(size_t i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
}

template<class T, class Compare>
int partition(T* arr, int left, int right, Compare cmp){
    mt19937 gen(time(0));
    std::uniform_int_distribution<> uid(left, right - 1);
    int pivot = uid(gen);

    cout << pivot << endl;
    std::swap(arr[left], arr[pivot]);
    pivot = left;

    int i = right - 1;

    for (int j = right - 1; j>left;){
        if (cmp(arr[j], arr[pivot])){
            j--;
        }else{
            if (j != i)
                std::swap(arr[j], arr[i]);
            j--;
            i--;
        }
    }

    if (pivot != i)
        std::swap(arr[pivot], arr[i]);

    return i;

}

template<class T, class Compare>
int kStatistic(T* arr, int size, int k, Compare cmp){
    int left = 0, right = size;

    while(true){
        int pivot = partition(arr, left, right, cmp);

        if (pivot == k){
            return arr[pivot];
        }else if (k < pivot){
            right = pivot;
        }else {
            left = pivot + 1;
        }
    }
}

int main(){
    int lengthArray;
    int kStatRes;

    cin >> lengthArray >> kStatRes;

    assert(lengthArray >= 0 && kStatRes >= 0);

    int* array = new int[lengthArray];

    readArray(array, lengthArray);
    printArray(array, lengthArray);
    cout << endl;
    kStatRes = kStatistic(array, lengthArray, kStatRes, [](const int& a, const int& b){ return a < b;  });
    
    delete[] array;
    cout << "k:" << kStatRes;
    return 0;
}

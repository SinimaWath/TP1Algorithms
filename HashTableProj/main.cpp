#include <iostream>
#include "hashtable.h"

using namespace std;

// TODO: Протестировать
struct Operation{
    enum class TTYpe{
        Add, Remove, Has, None
    };
    TTYpe id;
    std::string value;
};



istream& operator>>(istream& in, Operation::TTYpe& value){
    char intId = '\0';

    in >> intId;

    if (intId == '+'){
        value = Operation::TTYpe::Add;
    }else if (intId == '-'){
        value = Operation::TTYpe::Remove;
    }else if (intId == '?'){
        value = Operation::TTYpe::Has;
    }else{
        value = Operation::TTYpe::None;
    }


    return in;
}

int main() {

    auto hashFunc = [](const string& str, int a, int m){

        int hash = 0;
        for(const auto& ch: str){
            hash = (hash * a + ch) % m;
        }
        return hash;

    };

    HashTable<string, decltype(hashFunc)> table(hashFunc);



    Operation op{};
    while(cin >> op.id ) {
        cin >> op.value;

        // TODO: проверить
        switch (op.id) {
            case Operation::TTYpe::Add:
                cout << (table.Add(op.value)? "OK": "FAIL");
                break;
            case Operation::TTYpe::Remove:
                cout << (table.Remove(op.value)? "OK": "FAIL");
                break;
            case Operation::TTYpe::Has:
                cout << (table.Has(op.value) ? "OK" : "FAIL");
                break;
            default:
                cout << "Invalid command";
                break;
        }

        cout << "\n";

    }


    return 0;
}
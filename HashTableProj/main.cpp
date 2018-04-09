#include <iostream>
#include <string>

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
        value = Operation::TTYpe::Add;
    }else{
        value = Operation::TTYpe::None;
        if (in.eof()){
            cout << "Is here EOF\n";
        }
    }


    return in;
}

int main() {
    HashTable<string> table;

    Operation op{};
    while(cin >> op.value ) {
        cin >> op.id;

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
    }

    return 0;
}
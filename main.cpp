#include "files.hpp"
#include <iostream>
using namespace std;

int main() {
    cout << "Program Started: Type 'END' to finish." << endl;
    Files data_store;
    while (true) {
        if (!data_store.interface()) break;
    }
    cout << "Program End" << endl;
    return 0;
}
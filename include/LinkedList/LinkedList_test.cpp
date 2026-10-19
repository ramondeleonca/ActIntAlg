// David Alonso Cantú Delgado
// A00189239
#include <iostream>
using namespace std;
#include "LinkedList.h"

int main() {

    LinkedList<string> list;
    list.push_back("b");
    list.push_back("a");
    list.push_back("@");
    list.push_back("&");
    list.print();


    return 0;
}
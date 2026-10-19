// David Alonso Cantú Delgado
// A00189239
#include <iostream>
using namespace std;

#include "Node.h"


int main() {

    Node<int>* node1;
    node1 = new Node<int>(10); 
    node1->data = 20;
    cout << node1->data << endl;   

    

    return 0;
}
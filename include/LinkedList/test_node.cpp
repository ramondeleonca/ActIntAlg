// David Alonso Cantú Delgado
// A00189239
#include <iostream>
using namespace std;

#include "Node.h"

int main() {

    auto node1 = std::make_unique<Node<int>>(20);

    cout << "node1 data: " << node1->data << endl;

    auto node2 = std::make_unique<Node<int>>(10, std::move(node1));

    cout << "node1 data: " << node2->next->data << endl;
    
    

    


    return 0;
}
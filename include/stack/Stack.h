#if !defined(Stack_h)
#define Stack_h

#include "Node.h"
template <typename T>
class Stack {
private:
    Node<T>* topNode;
public:
    Stack() : topNode(nullptr) {}
    void pop();
    void push(T data);
    T top();
    bool isEmpty();
};

template <typename T>
void Stack<T>::pop() {
    // validamos que no este vacío
    if (topNode != nullptr) {
        // creamos un apuntador auxiliar a topNode
        Node<T>* aux = topNode;
        // actualizamos topNode al siguiente
        topNode = topNode->next;
        // borramos aux
        delete aux;
    }
}

template <typename T>
void Stack<T>::push(T data) {
    // creamos un nuevo nodo que apunta al tope actual
    Node<T>* newNode = new Node<T>(data, topNode);
    // actualizamos topNode al nuevo nodo
    topNode = newNode;
}

template <typename T>
T Stack<T>::top() {
    // retornamos el dato del tope
    return topNode->data;
}

template <typename T>
bool Stack<T>::isEmpty() {
    return topNode == nullptr;
}

#endif // Stack_h

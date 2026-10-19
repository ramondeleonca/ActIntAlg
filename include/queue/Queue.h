#if !defined(Queue_h)
#define Queue_h

#include "Node.h"
template <typename T>
class Queue {
private:
    Node<T>* head;
    Node<T>* tail;
public:
    Queue() : head(nullptr), tail(nullptr) {}
    void pop();
    void push(T data);
    T front() const { return head->data; }
    bool isEmpty() const { return head == nullptr; }
};

template <typename T>
void Queue<T>::pop() {
    // validamos que no este vacío
    if (head != nullptr) {
        // validamos si solo hay un elemento
        if (head == tail) {
            // creamos un apuntador auxiliar a head
            Node<T>* aux = head;
            // borramos aux
            delete aux;
            // inicializamos head y tail
            head = nullptr;
            tail = nullptr;
        } else {
            // creamos un apuntador auxiliar a head
            Node<T>* aux = head;
            // actualizamos head
            head = head->next;
            // borramos aux
            delete aux;
        }
    }
}

template <typename T>
void Queue<T>::push(T data) {
    // validamos que no este vacía
    if (head != nullptr) {
        // actualizamos el next de tail con un nodo nuevo
        tail->next = new Node<T>(data);
        // actualizamos tail con tail->next
        tail = tail->next;
    } else {
        // apunto head a un nuevo nodo
        head = new Node<T>(data);
        // apunto tail a head
        tail = head;
    }
}


#endif // Queue_h

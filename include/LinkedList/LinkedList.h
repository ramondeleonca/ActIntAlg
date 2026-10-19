// David Alonso Cantú Delgado
// A00189239
#ifndef LinkedList_h
#define LinkedList_h

#include "Node.h"

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;
public:
    LinkedList() : head(nullptr), size(0) {}
    void push_front(T data);
    void push_back(T data);
    void print();
    void insert(int index, T data);
};

template <typename T>
void LinkedList<T>::push_front(T data) {
    // crear un nodo nuevo
    Node<T>* node = new Node<T>(data);
    // actualizo el next del nodo nuevo para que apunte a head
    node->next = head;
    // actualizo head
    head = node;
}

template <typename T>
void LinkedList<T>::push_back(T data) {
    // validamos si la lista vacía
    if (head != nullptr) {
        // la lista no esta vacía
        // creamos un apuntador auxiliar que apunte a head
        Node<T>* aux = head;
        // recorremos la lista mientras aux->next sea diferente de nullptr
        while (aux->next != nullptr) {
            // recorremos aux a aux->next
            aux = aux->next;
        }
        // agregamos el nodo nuevo después de aux
        aux->next = new Node<T>(data);
    } else {
        // la lista esta vacía
        head = new Node<T>(data);    
    }
    // incrementamos size
    size++;
}

template <typename T>
void LinkedList<T>::insert(int index, T data) {
    // validamos que la posición exista
    if (index >= 0 && index < size) {
        // creamos un índice auxiliar
        int auxIndex = 0;
        // creamos nodo auxiliar
        Node<T>* aux = head;
        // recorremos la lista hasta encontrar la posición donde vamos a hacer el insert
        while (auxIndex < index) {
            // recorremos aux
            aux = aux->next;
            // incrementamos el indice auxiliar
            auxIndex++;
        }
        // insertamos el nuevo nodo
        aux->next = new Node<T>(data, aux->next);
        // incrementamos size
        size++;
    } else {
        // error
        throw out_of_range("la posición no existe en la lista")
    }

}

template <typename T>
void LinkedList<T>::deleteData(T data) {
    // validamos que la lista no este vacía
    if (head != nullptr) {
        // la lista no esta vacía
        // valido si el primer elemento es el que quiero borrar
        if (head->data == data) {
            // quiero borrar el primer elemento
            // creamos un elemento aux igual a head
            Node<T>* aux = head;
            // recorremos head a head->next
            head = head->next;
            // borramos el primer elemento
            delete aux;
            // decrementamos size
            size--;
        } else {
            // creamos un elemento auxPrev igual a head
            Node<T>* auxPrev = head;
            // creamos un elemento aux igual a head->next
            Node<T>* aux = head->next;
            // recorremos la lista
            while (aux != nullptr) {
                // validamos si el valor de aux es el que quiero borrar
                if (aux->data == data) {
                    // 
                    auxPrev->next = aux->next;
                    // borro aux
                    delete aux;
                    // decrmenatmos size
                    size--;
                    // return
                }
                // recorremos los apuntadores
                auxPrev = aux;
                aux = aux->next;
            }
            // no lo encontre
            throw out_of_range("no se encontró el dato a borrar")
        }
    } else {
        throw out_of_range("La lista esta vacía")
    }
}

template <typename T>
void LinkedList<T>::print() {
    // creamos un apuntador auxiliar que apunte a head
    Node<T>* aux = head;
    // recorremos la lista mientras aux sea diferente de nullptr
    while (aux != nullptr) {
        cout << aux->data;
        aux = aux->next;
        if (aux != nullptr) {
            cout << "-";
        }
    }
    cout << endl;
}










#endif /* LinkedList_h */
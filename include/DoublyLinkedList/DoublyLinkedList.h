// David Alonso Cantú Delgado
// A00189239
#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include "NodeD.h"
#include <stdexcept>
using namespace std;

template <typename T>
class DoublyLinkedList {
private:    
    NodeD<T>* head;
    NodeD<T>* tail;
    int size = 0;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    void addFirst(T data);
    void addLast(T data);
    void insert(int index, T data);
    bool deleteAt(int index);
    int findData(T data);
    bool deleteData(T data);

    // Accesores internos para algoritmos de ordenamiento externos
    NodeD<T>* getHead() const { return head; }
    NodeD<T>* getTail() const { return tail; }
    void setHead(NodeD<T>* node) { head = node; }
    void setTail(NodeD<T>* node) { tail = node; }
    int getSize() const { return size; }
    void setSize(int s) { size = s; }
    bool isEmpty() const { return head == nullptr; }
};

template <typename T>
void DoublyLinkedList<T>::addFirst(T data) {
    // validamos si la lista está vacía
    if (head == nullptr) {
        // si está vacía la lista
        // apunto head a un nuevo nodo con data
        head = new NodeD<T>(data);
        // apunto tail a head
        tail = head;
        // incremento size
        size++;
    } else {
        // la lista no está vacía
        // creamos un nuevo nodo
        NodeD<T>* aux = new NodeD<T>(data);
        // apuntamos el next de aux a head
        aux->next = head;
        // apuntamos el prev de head a aux
        head->prev = aux;
        // apuntamos head a aux
        head = aux;
        // incrementamos size
        size++;
    }
}

template <typename T>
void DoublyLinkedList<T>::addLast(T data) {
    // validamos si la lista está vacía
    if (head == nullptr) {
        // si está vacía la lista
        // apunto head a un nuevo nodo con data
        head = new NodeD<T>(data);
        // apunto tail a head
        tail = head;
        // incremento size
        size++;
    } else {
        // la lista no está vacía
        // creamos un nuevo nodo
        NodeD<T>* aux = new NodeD<T>(data);
        // apuntamos el prev de aux a tail
        aux->prev = tail;
        // apuntamos el next de tail a aux
        tail->next = aux;
        // apuntamos tail a aux
        tail = aux;
        // incrementamos size
        size++;
    }
}

template <typename T>
void DoublyLinkedList<T>::insert(int index, T data) {
    // validamos que él índice sea válido
    if (index >= 0 && index <= size-1) {
        // validamos que el indice sea desde 0 hasta el penúltimo
        if (index != size-1) {
            // el index es desde 0 hasta el penúltimo (en medio)
            // creamos un indice auxiliar igual a 0
            int auxIndex = 0;
            // creamos un apuntador auxiliar igual a head
            NodeD<T>* aux = head;
            // iteramos hasta encontrar el índice dato
            while (auxIndex < index) {
                // recorremos aux
                aux = aux->next;
                // incrementamos el indice auxiliar
                auxIndex++;
            }
            // creamos un nodo nuevo
            NodeD<T>* auxNew = NodeD<T>(data);
            // el prev del nuevo lo apuntamos a aux
            auxNew->prev = aux;
            // el next del nuevo lo apuntamos a aux->next
            auxNew->next = aux->next;
            // el prev del siguiente de aux lo apuntamos al nuevo
            aux->next->prev = auxNew;
            // apuntamos aux next al nuevo
            aux->next = auxNew;
            // incrmenetamos size
            size++;
        } else {
            // el index es igual a size -1
            // hacemos como si fuera addLast
            // creamos un nuevo nodo
            NodeD<T>* aux = new NodeD<T>(data);
            // apuntamos el prev de aux a tail
            aux->prev = tail;
            // apuntamos el next de tail a aux
            tail->next = aux;
            // apuntamos tail a aux
            tail = aux;
            // incrementamos size
            size++;
        }
    } else {
        throw out_of_range("Índice inválido");
    }
}

template <typename T>
bool DoublyLinkedList<T>::deleteAt(int index) {
    // validamos si el índice es válido
    if (index >= 0 && index < size) {
        // índíce válido
        // validamos si solo hay un elemento
        if (head->next != nullptr) {
            // solo hay un elemento
            // creamos un nodo auxiliar que apunte a head
            NodeD<T>* aux = head;
            // apuntamos a nulos head y tail
            head = nullptr;
            tail = nullptr;
            // liberamos aux
            delete aux;
            // decrementamos size
            size--;
            // retornamos verdadero
            return true;
        } else {
            // hay más de un elemento
            // validamos si queremos borrar el primero
            if (index == 0) {
                // queremos borrar el primero
                // creamos un nodo auxiliar que apunte a head
                NodeD<T>* aux = head;  
                // apuntamos head al siguiente elemento
                head = head->next;
                // actualizamos el apuntador prev de head
                head->prev = nullptr;
                // liberamos aux
                delete aux;
                // decrementamos size
                size--;
                // retornamos verdadero
                return true; 
            } else {
                // validamos si queremos borrar el último elemento
                if (index == size - 1) {
                    // borramos el último
                    // creamos un nodo auxiliar que apunte a tail
                    NodeD<T>* aux = tail;  
                    // apuntamos tail al elemento previo
                    tail = tail->prev;
                    // actualizamos el apuntador prev de head
                    tail->next = nullptr;
                    // liberamos aux
                    delete aux;
                    // decrementamos size
                    size--;
                    // retornamos verdadero
                    return true; 
                } else {
                    // borramos el de en medio
                    // revisamos por donde empezamos a recorrer la lista
                    if (index <= (size-1)/2) {
                        // recorremos por la izquierda
                        // creamos un indice auxliar = 1
                        int auxIndex = 1;
                        // creamos un apuntador auxiliar igual a head->next
                        NodeD<T>* aux = head->next;
                        // recorremos la lista mientras auxIndex < index
                        while (auxIndex < index) {
                            // recorremos aux
                            aux = aux->next;
                            // incrementamos auxIndex
                            auxIndex++;
                        }
                        // ya llegue al nodo deseado
                        // actualizamos el next de aux->prev que apunte a aux->next
                        aux->prev->next = aux->next;
                        // actualizamos el prev de aux->next que apunte a aux->prev
                        aux->next->prev = aux->prev;
                        // libero aux
                        delete aux;
                        // decremento size
                        size--;
                        // regreso true
                        return true;
                    } else {
                        // recorremos por la derecha
                        // creamos un indice auxliar = size -2
                        int auxIndex = size - 2;
                        // creamos un apuntador auxiliar igual a tail->prev
                        NodeD<T>* aux = tail->prev;
                        // recorremos la lista mientras indez < auxIndex
                        while (index < auxIndex) {
                            // recorremos aux
                            aux = aux->prev;
                            // decrementamos auxIndex
                            auxIndex--;
                        }
                        // ya llegue al nodo deseado
                        // actualizamos el next de aux->prev que apunte a aux->next
                        aux->prev->next = aux->next;
                        // actualizamos el prev de aux->next que apunte a aux->prev
                        aux->next->prev = aux->prev;
                        // libero aux
                        delete aux;
                        // decremento size
                        size--;
                        // regreso true
                        return true;
                    }
                }
            }
        }
    } else {
        // índice inválido
        return false;
    }
}

template <typename T>
int DoublyLinkedList<T>::findData(T data) {
    // creamos un apuntador auxiliar
    NodeD<T>* aux = head;
    // incializamos un indice auxialiar en 0
    int auxIndex = 0;
    // recorremos la lista mientras sea diferente
    while (auxIndex < size) {
        // validamos si lo encontramos
        if (aux->data == data) {
            // si lo encontramos
            return auxIndex;
        }
        // recorremos aux e incrmentamos auxIndex
        auxIndex++;
        aux = aux->next;
    }
    // data no se encuentra en la lista
    return -1;
}

template <typename T>
bool DoublyLinkedList<T>::deleteData(T data) {
    // find Data
    // creamos un apuntador auxiliar
    NodeD<T>* aux = head;
    // incializamos un indice auxialiar en 0
    int auxIndex = 0;
    // recorremos la lista mientras sea diferente
    while (auxIndex < size) {
        // validamos si lo encontramos
        if (aux->data == data) {
            // si lo encontramos, hay que borrarlo
            // valiamos si es el único
            if (head == tail) {
                // apuntamos a nulos head y tail
                head = nullptr;
                tail = nullptr;
                // liberamos aux
                delete aux;
                // decrementamos size
                size--;
                // retornamos verdadero
                return true;
            } else {
                // validamos si vamos a borrar head
                if (aux == head) {
                    // si es el primer elemento
                    // apuntamos head al siguiente elemento
                    head = head->next;
                    // actualizamos el apuntador prev de head
                    head->prev = nullptr;
                    // liberamos aux
                    delete aux;
                    // decrementamos size
                    size--;
                    // retornamos verdadero
                    return true; 
                } else {
                    // validamos si el último elemento
                    if (aux == tail) {
                        // si es el último elemento
                        // apuntamos tail al elemento previo
                        tail = tail->prev;
                        // actualizamos el apuntador prev de head
                        tail->next = nullptr;
                        // liberamos aux
                        delete aux;
                        // decrementamos size
                        size--;
                        // retornamos verdadero
                        return true; 
                    } else {
                        // boramos el de en medio
                        // actualizamos el next de aux->prev que apunte a aux->next
                        aux->prev->next = aux->next;
                        // actualizamos el prev de aux->next que apunte a aux->prev
                        aux->next->prev = aux->prev;
                        // libero aux
                        delete aux;
                        // decremento size
                        size--;
                        // regreso true
                        return true;
                    }
                }
            }
        }
        // recorremos aux e incrmentamos auxIndex
        auxIndex++;
        aux = aux->next;
    }
    // data no se encuentra en la lista
    return false;

}

#endif /* DoublyLinkedList_h */
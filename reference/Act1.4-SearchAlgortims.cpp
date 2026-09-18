// David Alonso Cantú Delgado
// A00189239
#include <iostream>
using namespace std;

// Búsqueda secuencial
int seqSearch(vector<int> &list, int data) {
    for (int i=0; i<list.size(); i++) {
        if (list[i] == data) {
            return i;
        }
    }
    throw out_of_range("no se encontró el valor");
}

// Búsueda binaria (La lista ya esta ordenada)
template <typename T>
int binarySearch(vector<T> &list, T data) {
    // obtenemos left
    int left = 0;
    // obtenemos right
    int right = list.size() - 1;
    // buscamos el elemento mientras left <= right
    while (left <= right) {
        // obtenemos la mitad
        int mid = (left + right) / 2;
        // comparamos el valor buscado con el valor de la mitad
        if (data == list[mid]) {
            // regresamoe el valor de mid que es el índice del valor encontrado
            return mid;
        } else {
            // preguntamos si el valor buscado es menor que el valor de mid
            if (data < list[mid]) {
                // si es menor
                right = mid - 1;
            } else {
                // es mayor
                left = mid + 1;
            }
            // data < list[mid] ? right = mid - 1 : left = mid + 1;
        }
    }
    // no lo encontramos
    throw out_of_range("No se econtró el valor");
}

int main() {

    vector<int> list = {3, 5, 6, 8, 11, 12, 13, 16, 27, 35};
    try {
        int index = binarySearch(list, 14);
        cout << "El valor se encuentra en: " << index << endl;
    } catch (const out_of_range &e) {
        cout << e.what() << endl;
    }
    return 0;
}
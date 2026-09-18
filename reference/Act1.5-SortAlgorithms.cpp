// David Alonso Cantú Delgado
// A00189239
#include <iostream>
#include <vector>
using namespace std;



template <typename T>
void swap(vector<T> &list, int i, int j) {
    if (i != j) {
        // creamos una variable temporal
        T aux = list[i];
        // cambiamos i por j
        list[i] = list[j];
        // cambiamos j por aux
        list[j] = aux;
    }
}

template <typename T>
void swapSort(vector<T> &list) {
    // iteramos todos los elementos de la lista hasta el penultimo
    for (int i=0; i < list.size()-1; i++) {
        for (int j=i+1; j<list.size(); j++) {
            // comparamos el valor de j con el valor de i para determinar si es menor
            if (list[j] < list[i]) {
                // si es menor
                // intercambiamos los valores
                swap(list, i, j);
            }
        }
    }
}

template <typename T>
void bubbleSort(vector<T> &list) {
    // definimos un booleano como verdadero
    bool change = true;
    // iterar desde n hasta 1
    for (int i=list.size()-1; i>0 && change; i--) {
        // cambio el valor de change a falso
        change = false;
        // iteramos desde 0 hasta qu sea menor que i
        for (int j=0; j<i; j++) {
            // comparamos el valor de j con el valor de j+1 para determinar si es mayor
            if (list[j] > list[j+1]) {
                // si es mayor
                // cambiamos change a verdadero
                change = true;
                // intercambiamos los valores
                swap(list, j, j+1);
            }
        }
    }
}

// Selection Sort
template <typename T>
void selectionSort(vector<T> &list) {
    // iteramos toda la lista desde el principio hasta uno antes del final
    for (int i=0; i<list.size()-1; i++) {
        // hacemos el indice de la posición i como el más chico
        int min = i;
        // iteramos desde el siguiente índice hasta el final
        for (int j=i+1; j<list.size(); j++) {
            // comparamos el valor de j contra min
            if (list[j] < list[min]) {
                // si es menor
                // Actualizamos el valor de min
                min = j;
            }
        }
        // intercambiamos el valor de min por el valor de i
        swap(list, min, i);
    }
}

// Selection Sort
template <typename T>
void insertionSort(vector<T> &list) {
    // iteramos la lista desde la segunda posición hasta el final
    for (int i=1; i<list.size(); i++) {
        // iteramos desde i hasta 0
        bool exit = false;
        for (int j=i; j>0 && !exit; j--) {
            if (list[j] < list[j-1]) {
               swap(list, j, j-1); 
            } else {
                exit = true;
            }
        }
        // declaramos un contador para ver donde vamos  
        // int j = i;
        // while (j>0 && list[j] < list[j-1]) {
        //     // Intercambiamos j con j-1
        //     swap(list, j, j-1);
        //     // decrementamos j
        //     j--;
        // }
    }
}

template <typename T>
int getPivot(vector<T> &list, int left, int right) {
    // creamos una variable auxiliar con el valor de left - 1
    int aux = left - 1;
    // creamos una variable pivot con el valor de right
    int pivot = right;
    // iteramos desde left hasta pivot - 1 (< pivot)
    for (int i=left; i<pivot; i++) {
        // comparamos si el valor de pivot > al valor de i
        if (list[pivot] > list[i]) {
            // incrementamos el valor de i
            aux++;
            // intercambiamos aux con i
            swap(list, aux, i);
        }
    }
    // incrementamos aux
    aux++;
    // intercambiamos aux con pivot
    swap(list, aux, pivot);
    // regresamos aux
    return aux;
}

template <typename T>
void quickSort(vector<T> &list, int left, int right) {
    // se ejectua la recursividad si left < right
    if (left < right) { // condición de control
        int pivot = getPivot(list, left, right);
        // ordenamos la lista del lado izq de pivote
        quickSort(list, left, pivot - 1);
        // ordenamos la lista del lado der de pivote
        quickSort(list, pivot + 1, right);
    }
}

template <typename T>
void merge(vector<T> &list, int left, int mid, int right) {
    // generamos la lista de left a mid
    // creamos una list para los valores del lado izquierdo
    vector<T> leftList;
    // iteramos la lista de left hasta a mid
    for (int i=left; i<=mid; i++) {
        leftList.push_back(list[i]);
    }
    // generamos la lista de mid+1 a right
    vector<T> rightList;
    // iteramos la lista de left hasta a mid
    for (int j=mid+1; j<=right; j++) {
        rightList.push_back(list[j]);
    }
    // combinamos las dos listas
    // creamos una variable index que contenga el indice a actualizar
    int index = left;
    // inicializamos el indice del lado izquierdo
    int i=0;
    // inicializamos el indice del lado derecho
    int j=0;
    // iteramos mientras no se acaben las listas
    while (i<leftList.size() && j<rightList.size()) {
        // comparamos el valor de i de la listaizq con el valor de j de la lista der
        if (leftList[i] < rightList[j]) {
            // actualizamos list en index con el valor de listLeft en i
            list[index] = leftList[i];
            // incrementamos i;
            i++;
        } else {
            // actualizamos list en index con el valor de listright en j
            list[index] = rightList[j];
            // incrementamos j;
            j++;
        }
        // incrementamos index
        index++;
    }
    // vaciamos la lista del lado izquierdo
    while (i<leftList.size()) {
        // actualizamos list en index con el valor de listLeft en i
        list[index] = leftList[i];
        // incrementamos i;
        i++;
        // incrementamos index
        index++;
    }
    // vaciamos la lista del lado derecho
    while (j<rightList.size()) {
        // actualizamos list en index con el valor de listLeft en i
        list[index] = rightList[j];
        // incrementamos i;
        j++;
        // incrementamos index
        index++;
    }
}

template <typename T>
void mergeSort(vector<T> &list, int left, int right) {
    // la condición de control es que left < right
    if (left < right) {
        // calculamos mid
        int mid = (left + right) / 2;
        // ordenamos de left a mid 
        mergeSort(list, left, mid);
        // ordenamos de mid+1 a right 
        mergeSort(list, mid+1, right);
        // combinamos las dos partes de la lista
        merge(list, left, mid, right);
    }
}


template <typename T>
void print(vector<T> &list) {
    for (int i=0; i<list.size(); i++) {
        cout << list[i] << " ";
    }
    cout << endl;
}

int main() {
    const vector<int> listOriginal = {15, 7, 3, 9, 12, 5, 2};

    cout << "========================================" << endl;
    cout << "     DEMOSTRADOR DE ALGORITMOS SORT     " << endl;
    cout << "========================================" << endl;

    // Esta función lambda evita repetir el mismo código para probar cada algoritmo.
    // [&] captura por referencia las variables declaradas fuera de la lambda; así puede
    // acceder a listOriginal sin recibirlo como parámetro ni crear otra copia aquí.
    // nombre contiene el texto que se mostrará y ordenar recibe la función de ordenamiento.
    auto probarAlgoritmo = [&](const string &nombre, auto ordenar) {
        // Cada algoritmo trabaja con una copia nueva para comenzar con los mismos datos.
        vector<int> list = listOriginal;

        cout << "\n--- " << nombre << " ---" << endl;
        cout << "Lista original:  ";
        print(list);

        // Ejecuta la función de ordenamiento recibida sobre la copia de la lista.
        ordenar(list);

        cout << "Lista ordenada:  ";
        print(list);
        // Devuelve la lista ordenada para poder usar el resultado fuera de esta lambda.
        return list;
    };

    // [] indica que esta lambda no captura variables externas. Recibe la lista por
    // referencia y llama al algoritmo específico que probarAlgoritmo debe ejecutar.
    probarAlgoritmo("Swap Sort", [](vector<int> &list) {
        swapSort(list);
    });

    // Lambda adaptadora para ejecutar Bubble Sort sobre la lista recibida.
    probarAlgoritmo("Bubble Sort", [](vector<int> &list) {
        bubbleSort(list);
    });

    // Lambda adaptadora para ejecutar Selection Sort sobre la lista recibida.
    probarAlgoritmo("Selection Sort", [](vector<int> &list) {
        selectionSort(list);
    });

    // Guarda el valor devuelto para demostrar que también puede usarse después de la prueba.
    vector<int> insertionResult = probarAlgoritmo(
        "Insertion Sort", [](vector<int> &list) {
            insertionSort(list);
        }
    );
    cout << "Último elemento: " << insertionResult.back() << endl;

    // Quick Sort necesita además los índices inicial y final del rango que ordenará.
    probarAlgoritmo("Quick Sort", [](vector<int> &list) {
        quickSort(list, 0, list.size() - 1);
    });

    // Merge Sort también recibe los límites de toda la lista.
    probarAlgoritmo("Merge Sort", [](vector<int> &list) {
        mergeSort(list, 0, list.size() - 1);
    });

    cout << "\n========================================" << endl;
    cout << "       PRUEBAS COMPLETADAS CON ÉXITO     " << endl;
    cout << "========================================" << endl;

    return 0;
}

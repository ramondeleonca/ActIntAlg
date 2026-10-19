#include <iostream>
#include <fstream>
#include <string>

#include "../include/LogEntry.hpp"
#include "../include/DoublyLinkedList/DoublyLinkedList.h"
#include "../include/Queue/Queue.h"
#include "../include/Stack/Stack.h"
#include "../include/SortingAlgorithms.hpp"
#include "../include/termcolor.hpp"

using namespace std;

// ─────────────────────────────────────────────
//  Definiciones de funciones
// ─────────────────────────────────────────────

void saveToFile(const string& filename, const DoublyLinkedList<LogEntry>& lista) {
    // TODO: Guardar datos en archivo
}

bool loadFile(const string& filename, DoublyLinkedList<LogEntry>& lista) {
    // TODO: Cargar datos desde archivo a Queue y luego a DoublyLinkedList
    return true;
}

void opcionOrdenar(DoublyLinkedList<LogEntry>& lista) {
    cout << "\n--- 1. Ordenar (Merge Sort / Quick Sort) ---\n";
    // TODO: Implementar medición de tiempo y algoritmo de ordenamiento
}

void opcionBuscarDia(DoublyLinkedList<LogEntry>& lista) {
    cout << "\n--- 2. Buscar registros por día ---\n";
    // TODO: Implementar búsqueda por fecha (Mmm DD AAAA)
}

void opcionDescendente(DoublyLinkedList<LogEntry>& lista) {
    cout << "\n--- 3. Ver día en orden descendente con Pila ---\n";
    // TODO: Implementar push y pop con Stack
}

void opcionEstadisticas(DoublyLinkedList<LogEntry>& lista) {
    cout << "\n--- 4. Estadísticas ---\n";
    // TODO: Implementar cálculo de estadísticas básicas
}

// ─────────────────────────────────────────────
//  CLI Principal
// ─────────────────────────────────────────────

int main() {
    cout << termcolor::green << "\n=== Evidencia 2 — Procesador de Log de Red ===" << termcolor::reset << "\n";
    cout << "1. data/log608-1.txt (casi ordenado)\n";
    cout << "2. data/log608-2.txt (desordenado)\n";
    cout << "Elige un archivo (1/2): ";

    int fileChoice;
    if (!(cin >> fileChoice)) return 0;

    string filename = (fileChoice == 2) ? "data/log608-2.txt" : "data/log608-1.txt";
    DoublyLinkedList<LogEntry> lista;

    if (!loadFile(filename, lista)) return 1;

    bool running = true;
    while (running) {
        cout << termcolor::cyan << "\nMenu:\n" << termcolor::reset;
        cout << "1. Ordenar (Merge Sort / Quick Sort)\n";
        cout << "2. Buscar registros por dia\n";
        cout << "3. Ver dia en orden descendente (usando Pila)\n";
        cout << "4. Estadisticas\n";
        cout << "5. Salir\n";
        cout << "Opcion: ";

        int opcion;
        if (!(cin >> opcion)) break;

        switch (opcion) {
            case 1:
                opcionOrdenar(lista);
                break;
            case 2:
                opcionBuscarDia(lista);
                break;
            case 3:
                opcionDescendente(lista);
                break;
            case 4:
                opcionEstadisticas(lista);
                break;
            case 5:
                running = false;
                cout << termcolor::green << "¡Hasta luego!\n" << termcolor::reset;
                break;
            default:
                cout << termcolor::red << "Opcion invalida.\n" << termcolor::reset;
                break;
        }
    }

    return 0;
}

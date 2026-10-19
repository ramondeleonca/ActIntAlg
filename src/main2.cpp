#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <cmath>

#include "../include/LogEntry.hpp"
#include "../include/DoublyLinkedList/DoublyLinkedList.h"
#include "../include/Queue/Queue.h"
#include "../include/Stack/Stack.h"
#include "../include/SortingAlgorithms.hpp"
#include "../include/termcolor.hpp"

using namespace std;
using namespace std::chrono;

void saveToFile(const string& filename, const DoublyLinkedList<LogEntry>& lista) {
    ofstream out(filename);
    for (NodeD<LogEntry>* cur = lista.getHead(); cur != nullptr; cur = cur->next) {
        out << cur->data.originalLine << "\n";
    }
}

string parseDayKey(const string& dayStr) {
    if (dayStr.length() < 11) return "";
    string monthInt = LogEntry::monthToIntString(dayStr.substr(0, 3));
    return dayStr.substr(7, 4) + monthInt + dayStr.substr(4, 2);
}

bool loadFile(const string& filename, DoublyLinkedList<LogEntry>& lista) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << termcolor::red << "Error al abrir el archivo " << filename << termcolor::reset << "\n";
        return false;
    }

    Queue<string> fila;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) fila.push(line);
    }
    file.close();

    int cargados = 0;
    while (!fila.isEmpty()) {
        LogEntry entry(fila.front());
        fila.pop();
        if (entry.isValid()) {
            lista.addLast(entry);
            cargados++;
        }
    }

    cout << termcolor::green << "Cargados: " << cargados << termcolor::reset << "\n";
    return true;
}

bool isSorted(DoublyLinkedList<LogEntry>& lista) {
    for (NodeD<LogEntry>* cur = lista.getHead(); cur != nullptr && cur->next != nullptr; cur = cur->next) {
        if (cur->data > cur->next->data) return false;
    }
    return true;
}

int main() {
    cout << termcolor::green << "\n=== Evidencia 2 — Procesador de Log de Red ===" << termcolor::reset << "\n";
    cout << "1. data/log608-1.txt (casi ordenado)\n";
    cout << "2. data/log608-2.txt (desordenado)\n";
    cout << "Elige un archivo (1/2): ";

    int fileChoice;
    if (!(cin >> fileChoice)) return 0;

    string filename = (fileChoice == 2) ? "data/log608-2.txt" : "data/log608-1.txt";
    DoublyLinkedList<LogEntry> lista;

    cout << "Cargando " << filename << "...\n";
    if (!loadFile(filename, lista)) return 1;

    bool yaOrdenada = false;
    string ultimoDiaBuscado = "";
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
            case 1: {
                if (yaOrdenada || isSorted(lista)) {
                    cout << termcolor::yellow << "La lista ya esta ordenada.\n" << termcolor::reset;
                    yaOrdenada = true;
                    break;
                }

                cout << termcolor::cyan << "\nAlgoritmos:\n" << termcolor::reset;
                cout << "1. Merge Sort (estable)\n";
                cout << "2. Quick Sort (mediana de tres)\n";
                cout << "Elige un algoritmo (1/2): ";
                int algChoice;
                cin >> algChoice;

                cout << "Prediccion (Escribe en milisegundos cuanto crees que tardara): ";
                long long prediccion;
                cin >> prediccion;

                long long comparaciones = 0;
                int maxDepth = 0;
                string algName = (algChoice == 2) ? "Quick Sort" : "Merge Sort";

                auto start = high_resolution_clock::now();
                if (algChoice == 2) {
                    quickSort(lista, comparaciones, maxDepth);
                } else {
                    mergeSort(lista, comparaciones, maxDepth);
                }
                auto end = high_resolution_clock::now();
                long long tiempoMs = duration_cast<milliseconds>(end - start).count();

                yaOrdenada = true;
                saveToFile("out/output608.out", lista);

                cout << termcolor::magenta << "\nAlgoritmo: " << algName << termcolor::reset << "\n";
                cout << termcolor::magenta << "Archivo: " << filename << termcolor::reset << "\n";
                cout << termcolor::magenta << "N registros: " << lista.getSize() << termcolor::reset << "\n";
                cout << termcolor::yellow  << "Tiempo de ejecucion: " << tiempoMs << " ms" << termcolor::reset << "\n";
                cout << termcolor::yellow  << "Comparaciones: " << comparaciones << termcolor::reset << "\n";
                cout << termcolor::yellow  << "Profundidad max: " << maxDepth << termcolor::reset << "\n";
                cout << termcolor::red     << "Error de prediccion: " << abs(prediccion - tiempoMs) << " ms" << termcolor::reset << "\n";

                if (algChoice == 2) {
                    cout << "Pivote: mediana de tres (head, medio, tail)\n";
                }
                cout << termcolor::green << "Datos ordenados guardados en out/output608.out" << termcolor::reset << "\n";
                break;
            }

            case 2: {
                if (!yaOrdenada) {
                    cout << termcolor::red << "Error: debes ordenar primero (opcion 1).\n" << termcolor::reset;
                    break;
                }

                cout << "Ingresa el dia a buscar (ej. Sep 14 2024): ";
                string m, d, y;
                cin >> m >> d >> y;
                string dayStr = m + " " + d + " " + y;
                string dk = parseDayKey(dayStr);
                ultimoDiaBuscado = dayStr;

                int total = 0;
                bool encontrado = false;
                for (NodeD<LogEntry>* cur = lista.getHead(); cur != nullptr; cur = cur->next) {
                    string curDk = cur->data.dayKey();
                    if (curDk > dk) break;
                    if (curDk == dk) {
                        if (!encontrado) {
                            cout << termcolor::cyan << "\nRegistros del " << dayStr << ":\n" << termcolor::reset;
                            encontrado = true;
                        }
                        cout << "  " << cur->data.originalLine << "\n";
                        total++;
                    }
                }

                if (!encontrado) {
                    cout << termcolor::yellow << "No se encontraron registros para el " << dayStr << termcolor::reset << "\n";
                } else {
                    cout << termcolor::green << "Total: " << total << " registro(s)" << termcolor::reset << "\n";
                }
                break;
            }

            case 3: {
                if (!yaOrdenada) {
                    cout << termcolor::red << "Error: debes ordenar primero (opcion 1).\n" << termcolor::reset;
                    break;
                }

                string dayStr = ultimoDiaBuscado;
                if (dayStr.empty()) {
                    cout << "Ingresa el dia a buscar (ej. Sep 14 2024): ";
                    string m, d, y;
                    cin >> m >> d >> y;
                    dayStr = m + " " + d + " " + y;
                } else {
                    cout << "(Usando dia de la ultima busqueda: " << dayStr << ")\n";
                }

                string dk = parseDayKey(dayStr);
                Stack<string> pila;
                for (NodeD<LogEntry>* cur = lista.getHead(); cur != nullptr; cur = cur->next) {
                    string curDk = cur->data.dayKey();
                    if (curDk > dk) break;
                    if (curDk == dk) {
                        pila.push(cur->data.originalLine);
                    }
                }

                if (pila.isEmpty()) {
                    cout << termcolor::yellow << "No se encontraron registros para el " << dayStr << termcolor::reset << "\n";
                    break;
                }

                cout << termcolor::cyan << "\nRegistros del " << dayStr << " (orden descendente):\n" << termcolor::reset;
                int total = 0;
                while (!pila.isEmpty()) {
                    cout << "  " << pila.top() << "\n";
                    pila.pop();
                    total++;
                }
                cout << termcolor::green << "Total: " << total << " registro(s)" << termcolor::reset << "\n";
                break;
            }

            case 4: {
                if (lista.isEmpty()) {
                    cout << termcolor::red << "No hay registros cargados.\n" << termcolor::reset;
                    break;
                }

                int total = 0;
                string currentDay = "";
                int currentCount = 0;
                string maxDay = "";
                int maxCount = 0;

                for (NodeD<LogEntry>* cur = lista.getHead(); cur != nullptr; cur = cur->next) {
                    total++;
                    string d = cur->data.dayString();
                    if (d == currentDay) {
                        currentCount++;
                    } else {
                        if (currentCount > maxCount) {
                            maxCount = currentCount;
                            maxDay = currentDay;
                        }
                        currentDay = d;
                        currentCount = 1;
                    }
                }
                if (currentCount > maxCount) {
                    maxCount = currentCount;
                    maxDay = currentDay;
                }

                cout << termcolor::cyan << "\n=== Estadisticas ===" << termcolor::reset << "\n";
                cout << termcolor::magenta << "Total de registros: " << termcolor::reset << total << "\n";
                if (!maxDay.empty() && maxCount > 0) {
                    cout << termcolor::yellow << "Dia con mas incidentes: " << termcolor::reset
                        << maxDay << " (" << maxCount << " incidentes)\n";
                }
                break;
            }

            case 5:
                running = false;
                cout << termcolor::green << "¡Hasta luego!\n" << termcolor::reset;
                break;

            default:
                cout << termcolor::red << "Opcion invalida. Ingresa un numero del 1 al 5.\n" << termcolor::reset;
                break;
        }
    }

    return 0;
}

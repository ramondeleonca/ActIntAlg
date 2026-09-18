#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>

#include "../include/LogEntry.hpp"
#include "../include/SortingAlgorithms.hpp"
#include "../include/SearchAlgorithm.hpp"
#include "../include/termcolor.hpp"

using namespace std;
using namespace std::chrono;

void saveToFile(const string& filename, const vector<LogEntry>& data) {
    ofstream out(filename);
    for (const auto& entry : data) {
        out << entry.originalLine << "\n";
    }
}

void saveRangeToFile(const string& filename, const vector<LogEntry>& data, int startIdx, int endIdx) {
    ofstream out(filename);
    for (int i = startIdx; i < endIdx; ++i) {
        out << data[i].originalLine << "\n";
    }
}

int main() {
    bool running = true;
    while (running) {
        cout << termcolor::green << "\n=== Actividad Integradora ===" << termcolor::reset << "\n";
        cout << "1. log607-1.txt (Desordenado)\n";
        cout << "2. log607-2.txt (Casi ordenado)\n";
        cout << "Elige un archivo (1/2, 0 para salir): ";
        int fileChoice;
        if (!(cin >> fileChoice) || fileChoice == 0) break;

        string filename = (fileChoice == 1) ? "data/log607-1.txt" : "data/log607-2.txt";

        cout << termcolor::yellow << "\nAlgoritmos:\n" << termcolor::reset;
        cout << "1. Bubble Sort\n";
        cout << "2. Insertion Sort\n";
        cout << "3. Merge Sort\n";
        cout << "Elige un algoritmo: ";
        int algChoice;
        cin >> algChoice;

        cout << "\nPrediccion (Escribe en milisegundos cuanto crees que tardara): ";
        long long predictedMs;
        cin >> predictedMs;

        ifstream file(filename);
        if (!file.is_open()) {
            cout << termcolor::red << "Error al abrir el archivo " << filename << termcolor::reset << "\n";
            continue;
        }

        vector<LogEntry> logs;
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                logs.push_back(LogEntry(line));
            }
        }
        file.close();

        cout << termcolor::cyan << "\n[Archivo: " << filename << " | Tamano: " << logs.size() << " registros]" << termcolor::reset << "\n";
        cout << termcolor::cyan << "[Prediccion: " << predictedMs << " ms]" << termcolor::reset << "\n";

        auto start = high_resolution_clock::now();

        string algName = "";
        if (algChoice == 1) {
            algName = "Bubble Sort";
            bubbleSort(logs);
        } else if (algChoice == 2) {
            algName = "Insertion Sort";
            insertionSort(logs);
        } else if (algChoice == 3) {
            algName = "Merge Sort";
            mergeSort(logs);
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);

        cout << termcolor::magenta << "Algoritmo: " << algName << termcolor::reset << "\n";
        cout << termcolor::yellow << "Tiempo de ejecucion: " << duration.count() << " ms" << termcolor::reset << "\n";
        cout << termcolor::red << "Error de prediccion: " << std::abs(predictedMs - duration.count()) << " ms" << termcolor::reset << "\n";
        if (algChoice == 1) cout << "Complejidad teorica: O(N) mejor caso, O(N^2) peor caso\n";
        else if (algChoice == 2) cout << "Complejidad teorica: O(N) mejor caso, O(N^2) peor caso\n";
        else if (algChoice == 3) cout << "Complejidad teorica: O(N log N) mejor y peor caso\n";

        saveToFile("output607.txt", logs);
        cout << termcolor::green << "Datos ordenados guardados en output607.txt" << termcolor::reset << "\n";

        cout << termcolor::green << "\n=== Busqueda por rango ===" << termcolor::reset << "\n";
        cout << "Ingrese la fecha/hora de INICIO (ej. 2024:09:08-00:22:43) (YYYY:MM:DD-HH:MM:SS): ";
        string startKeyRaw;
        cin >> startKeyRaw;
        
        cout << "Ingrese la fecha/hora de FIN (ej. 2024:09:08-05:50:57) (YYYY:MM:DD-HH:MM:SS): ";
        string endKeyRaw;
        cin >> endKeyRaw;

        auto formatKey = [](const string& raw) {
            string res = "";
            for (char c : raw) {
                if (isdigit(c)) res += c;
            }
            return res;
        };

        string startKey = formatKey(startKeyRaw);
        string endKey = formatKey(endKeyRaw);

        int lowerIdx = binarySearchLowerBound(logs, startKey);
        int upperIdx = binarySearchUpperBound(logs, endKey);

        if (lowerIdx < upperIdx) {
            cout << termcolor::green << "Registros encontrados en el rango: " << (upperIdx - lowerIdx) << termcolor::reset << "\n";
            saveRangeToFile("range607.txt", logs, lowerIdx, upperIdx);
            cout << termcolor::green << "Resultados guardados en range607.txt" << termcolor::reset << "\n";
        } else {
            cout << termcolor::red << "No se encontraron registros en ese rango." << termcolor::reset << "\n";
        }
    }

    return 0;
}

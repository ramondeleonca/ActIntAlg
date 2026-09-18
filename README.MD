# Evidencia 1 - Actividad Integral de Conceptos Básicos y Algoritmos Fundamentales

## ¿Qué se hizo?

De acuerdo con el requerimiento de hacer un diseño minimalista usando archivos header y un `main.cpp` simplificado:

1. **Estructura de Datos y Parsing (`include/LogEntry.hpp`)**:
   - Se creó la clase `LogEntry` para almacenar tanto la línea original del log como una llave (`datetimeKey` en formato `YYYYMMDDHHMMSS`) para comparar y ordenar fácilmente los registros.
   - El parsing está encapsulado dentro del constructor `LogEntry(std::string)`, con métodos privados que extraen la información (mes, día, año, hora, minuto y segundo) del string del log y la convierten en el formato ordenable numéricamente.
   - Se sobrecargaron los operadores relacionales (`<`, `>`, `<=`, `>=`, `==`) para que la clase funcione de manera nativa con algoritmos de ordenamiento genéricos.

2. **Algoritmos de Ordenamiento (`include/SortingAlgorithms.hpp`)**:
   - Se adaptaron los algoritmos como se pedía, extrayéndolos del archivo base `Act1.5-SortAlgorithms.cpp`.
   - Estos se dejaron de forma genérica (con uso de `template <typename T>`) para que funcionen con los vectores de nuestra estructura `LogEntry`.
   - Se incluyeron **Bubble Sort**, **Insertion Sort** y **Merge Sort**.

3. **Algoritmos de Búsqueda (`include/SearchAlgorithm.hpp`)**:
   - Se extrajeron y adaptaron los algoritmos del archivo `Act1.4-SearchAlgortims.cpp`.
   - Se adaptó la búsqueda binaria para no solo devolver un índice exacto (ya que puede haber duplicados), sino para que devuelva los "límites" inferior y superior usando lógica equivalente a `lower_bound` y `upper_bound` de C++.
   - `binarySearchLowerBound`: Encuentra el primer registro mayor o igual a la llave de inicio.
   - `binarySearchUpperBound`: Encuentra el primer registro estrictamente mayor a la llave de fin.
   (Gemini 3.1 Pro High ayudó en esto)

4. **Flujo y CLI (`src/main.cpp`)**:
   - Pregunta al usuario qué archivo usar (`log607-1.txt` o `log607-2.txt`).
   
   - Permite seleccionar el algoritmo de ordenamiento.
   - Realiza la medición precisa de los tiempos de ejecución mediante `std::chrono`.
   - Exporta automáticamente el resultado ordenado a `output607.txt` y, después de pedir el rango de fechas para buscar (con formato amigable `YYYYMMDDHHMMSS`), guarda los resultados encontrados en `range607.txt`.

## Instrucciones de Compilación y Ejecución

### Utilizando el script:
```bash
./scripts/run.sh
```
o
```bash
./scripts/test.sh
```

### Manualmente
Compila usando `g++` desde la terminal (especificando estándar C++20):

```bash
g++ -std=c++20 src/main.cpp -o out/main
```

Ejecuta el archivo binario:

```bash
./out/main
```

## Formato de Fechas Esperado (Para búsqueda)
Al ingresar fechas de inicio o fin, utiliza el formato **YYYY:MM:DD-HH:MM:SS** (por ejemplo, para el 8 de Septiembre de 2024 a las 00:22:43 escribe `2024:09:08-00:22:43`). El programa internamente filtrará los símbolos y formará la llave numérica `20240908002243` de forma transparente.

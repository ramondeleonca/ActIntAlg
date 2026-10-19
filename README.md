# Evidencia 2 — Procesador de Log de Red (608)

VIDEO: _(pendiente — agregar URL aquí)_

## ¿Qué se hizo?

### Parte A _(realizada en clase por el alumno, sin IA)_

- **Lista ligada simple** (`include/LinkedList/`): `pu`
- `sh_front`, `push_back`, `insert`, `deleteData`, `print`.
- **Lista doblemente ligada** (`include/DoublyLinkedList/`): `addFirst`, `addLast`, `insert`, `deleteAt`, `deleteData`, `findData`. Inserciones y eliminaciones en extremos en O(1).
- **Fila** (`include/Queue/`): sobre lista ligada simple con `push` (enqueue) y `pop` (dequeue), `front` e `isEmpty`.
- **Pila** (`include/Stack/`): sobre lista ligada simple con `push`, `pop`, `top` e `isEmpty`.

### Parte B _(código generado con asistencia de IA, revisado y probado por el alumno)_

1. **Pipeline de carga** (`src/main608.cpp`, función `loadFile`):

   - Lee líneas → las encola en `Queue<string>` → un procesador desencola, parsea con `LogEntry` y hace `addLast` en `DoublyLinkedList<LogEntry>`.
   - Líneas inválidas se reportan y se omiten.
2. **CLI de 5 opciones**:

   - **1. Ordenar**: elige algoritmo, pide predicción, muestra tiempo, comparaciones, profundidad, coincidencia; genera `out/output608.out`.
   - **2. Buscar por día**: formato `Mmm DD AAAA`; exige orden previo; corta recorrido al pasar el día.
   - **3. Descendente con Pila**: push al recorrer forward → pop al mostrar.
   - **4. Estadísticas**: total, día/evento/IP más frecuentes (todos los empatados)
   - **5. Salir**.

## Instrucciones de Compilación y Ejecución

### Con el script de test:

```bash
chmod +x scripts/test608.sh
./scripts/test608.sh
```

### Manualmente:

```bash
g++ -std=c++20 -I include src/main608.cpp -o out/main608
./out/main608
```

## Formato de Fechas Esperado

Para la búsqueda por día (opción 2), usa: **Mmm DD AAAA**

Ejemplos válidos:

- `Sep 08 2024`
- `Jan 27 2025`
- `Dec 31 2025`

El día debe ser de 2 dígitos (con cero si es necesario): `Sep 01 2024`, NO `Sep 1 2024`.

## Política de IA

La **Parte A** (lista ligada simple, lista doble, Pila y Fila) fue realizada íntegramente por el alumno en clase, sin asistencia de IA.

El código de la **Parte B** fue parcialmente generado con asistencia de **Antigravity (Google)**

- Definió los requerimientos y el plan de trabajo a partir de lo ya realizado.
- Generó tests automatizados.

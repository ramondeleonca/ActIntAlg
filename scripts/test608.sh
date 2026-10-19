#!/bin/bash

# Compilar
echo "Compilando..."
g++ -std=c++20 -I include src/main608.cpp -o out/main608
if [ $? -ne 0 ]; then
    echo "Error de compilación."
    exit 1
fi
echo "Compilación exitosa."
echo ""

# ── Test 1: Carga exitosa, Merge Sort, búsqueda, descendente, estadísticas ──
echo "=== Test 1: Flujo completo — log608-1.txt con Merge Sort ==="
./out/main608 << 'EOF'
1
1
1
50
2
Sep 08 2024
3

4
5
EOF

echo ""
echo "=== Test 2: log608-2.txt con Quick Sort ==="
./out/main608 << 'EOF'
2
1
2
300
5
EOF

echo ""
echo "=== Test 3: Buscar antes de ordenar (debe rechazar) ==="
./out/main608 << 'EOF'
1
2
5
EOF

echo ""
echo "=== Test 4: Día sin registros (rango vacío) ==="
./out/main608 << 'EOF'
1
1
1
50
2
Jan 01 1970
5
EOF

echo ""
echo "=== Test 5: Opción de menú inválida ==="
./out/main608 << 'EOF'
1
9
abc
5
EOF

echo ""
echo "=== Test 6: Ya ordenada (segunda vez) ==="
./out/main608 << 'EOF'
1
1
1
50
1
5
EOF

echo ""
echo "=== Verificación del output608.out (primeras/últimas 3 líneas) ==="
echo "Primeras:"
head -3 out/output608.out
echo "Últimas:"
tail -3 out/output608.out

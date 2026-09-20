#!/bin/bash

# Compilar primero
g++ -std=c++20 src/main.cpp -o out/main

echo "Corriendo Test 1: Rango vacío (Fechas en el futuro)"
./out/main _rango_vacio << EOF
1
1
2000
2026:01:01-00:00:00
2027:01:01-00:00:00
0
EOF

echo "Corriendo Test 2: Bordes de fechas (Desde 1970 hasta 2038)"
./out/main _bordes << EOF
1
3
20
1970:01:01-00:00:00
2038:01:01-00:00:00
0
EOF

echo "Corriendo Test 3: Formatos de entrada inválidos (letras en lugar de números)"
./out/main _invalido << EOF
1
2
1000
formato-invalido-1
formato-invalido-2
0
EOF

echo "Corriendo Test 4: Timestamps duplicados en log607-2.txt"
# Usamos una misma fecha exacta para inicio y fin para ver si atrapa los duplicados
./out/main _duplicados << EOF
2
3
20
2024:09:08-00:22:43
2024:09:08-00:22:43
0
EOF

echo "Corriendo Test 5: Rango invertido (Inicio mayor que el fin)"
./out/main _invertido << EOF
2
1
1500
2025:01:01-00:00:00
2024:01:01-00:00:00
0
EOF

echo "Corriendo Test 6: Rango de una hora específica"
./out/main _hora_especifica << EOF
2
2
10
2024:09:08-04:00:00
2024:09:08-05:00:00
0
EOF

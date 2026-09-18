#!/bin/bash

# Compilar primero
g++ -std=c++20 src/main.cpp -o out/main

# Correr programa con un Here-Document (EOF) que inyecta automáticamente las combinaciones:
./out/main << EOF
1
1
2000
2024:09:08-00:22:43
2024:09:08-05:50:57
1
2
1000
2024:09:08-00:22:43
2024:09:08-05:50:57
1
3
20
2024:09:08-00:22:43
2024:09:08-05:50:57
2
1
1500
2024:09:08-00:22:43
2024:09:08-05:50:57
2
2
10
2024:09:08-00:22:43
2024:09:08-05:50:57
2
3
20
2024:09:08-00:22:43
2024:09:08-05:50:57
0
EOF

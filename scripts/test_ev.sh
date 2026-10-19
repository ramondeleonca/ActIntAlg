#!/bin/bash
# Evidencia 2 (608) — Parte A + casos de borde del CLI de main2.
set -u

ROOT="$(cd "$(dirname "$0")/.." && pwd)"
BIN="$ROOT/out/main2"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

fallos=0
section() {
    printf '\n============================================================\n%s\n============================================================\n' "$1"
}
check() {
    if printf '%s\n' "$2" | grep -qF -- "$3"; then
        echo "  [OK] $1"
    else
        echo "  [FALLO] $1 — no se encontró: $3"
        fallos=$((fallos + 1))
    fi
}
check_absent() {
    if printf '%s\n' "$2" | grep -qF -- "$3"; then
        echo "  [FALLO] $1 — no debía aparecer: $3"
        fallos=$((fallos + 1))
    else
        echo "  [OK] $1"
    fi
}

section "Compilación (src/main2.cpp — Evidencia 2)"
cd "$ROOT" || exit 1
mkdir -p out
if ! g++ -std=c++20 -I include src/main2.cpp -o out/main2; then
    echo "Error de compilación."
    exit 1
fi
echo "Compilación exitosa."

section "Parte A — pruebas de estructuras de datos"
if [ -x out/test_a ]; then
    partA="$(./out/test_a)"
    printf '%s\n' "$partA"
    check "estructura vacía" "$partA" "isEmpty() = true"
    check "un solo elemento" "$partA" "head == tail: true"
    check "extremos" "$partA" "deleteAt(size - 1)"
    check "orden LIFO" "$partA" "LIFO comprobado"
    check "orden FIFO" "$partA" "FIFO comprobado"
    check "recorrido hacia adelante" "$partA" "head -> next"
    check "recorrido hacia atrás" "$partA" "tail -> prev"
else
    echo "  [FALLO] No existe out/test_a (programa de pruebas de la Parte A)."
    fallos=$((fallos + 1))
fi

section "Caso de borde 1 — Archivo inexistente"
mkdir -p "$TMP/sin_archivo"
out="$(
    cd "$TMP/sin_archivo" || exit 1
    "$BIN" <<'EOF'
2
1
5
EOF
)"
codigo=$?
printf '%s\n' "$out"
check "mensaje de archivo inexistente" "$out" "Error al abrir el archivo data/log608-2.txt"
if [ "$codigo" -ne 0 ]; then
    echo "  [OK] termina con código de error ($codigo)"
else
    echo "  [FALLO] debía terminar con código de error"
    fallos=$((fallos + 1))
fi

section "Caso de borde 2 — Línea con formato inválido"
mkdir -p "$TMP/invalidos/data" "$TMP/invalidos/out"
cat > "$TMP/invalidos/data/log608-2.txt" <<'EOF'
Jan 01 2024 10:00:00 10.0.0.1 Evento A
Jan 02 2024 11:00:00 10.0.0.2 Evento B
linea invalida
EOF
out="$(
    cd "$TMP/invalidos" || exit 1
    "$BIN" <<'EOF'
2
4
5
EOF
)"
printf '%s\n' "$out"
check "carga solo las líneas válidas" "$out" "Cargados: 2"
check "estadísticas solo con líneas válidas" "$out" "Total de registros: 2"

section "Caso de borde 3 — Día sin registros"
out="$(cd "$ROOT" && "$BIN" <<'EOF'
2
1
1
0
2
Jan 01 1970
5
EOF
)"
printf '%s\n' "$out"
check "día sin registros" "$out" "No se encontraron registros para el Jan 01 1970"

section "Caso de borde 4 — Formato de día inválido"
out="$(cd "$ROOT" && "$BIN" <<'EOF'
2
1
1
0
2
Foo 99 2024
2
Sep 1 2024
5
EOF
)"
printf '%s\n' "$out"
veces="$(printf '%s\n' "$out" | grep -cF "No se encontraron registros para el")"
if [ "$veces" -eq 2 ]; then
    echo "  [OK] ambos formatos inválidos se tratan como día sin registros"
else
    echo "  [FALLO] se esperaban 2 búsquedas sin registros; hubo $veces"
    fallos=$((fallos + 1))
fi

section "Caso de borde 5 — Buscar antes de ordenar"
out="$(cd "$ROOT" && "$BIN" <<'EOF'
2
2
5
EOF
)"
printf '%s\n' "$out"
check "exige ordenar primero" "$out" "Error: debes ordenar primero (opcion 1)."

section "Caso de borde 6 — Ordenar una lista ya ordenada"
out="$(cd "$ROOT" && "$BIN" <<'EOF'
2
1
1
0
1
5
EOF
)"
printf '%s\n' "$out"
check "detecta que ya está ordenada" "$out" "La lista ya esta ordenada."
if [ -s out/output608.out ]; then
    echo "  [OK] genera out/output608.out"
else
    echo "  [FALLO] no se generó out/output608.out"
    fallos=$((fallos + 1))
fi

section "Caso de borde 7 — Empates en las estadísticas"
mkdir -p "$TMP/empates/data" "$TMP/empates/out"
cat > "$TMP/empates/data/log608-2.txt" <<'EOF'
Jan 01 2024 10:00:00 10.0.0.1 Evento A
Jan 01 2024 11:00:00 10.0.0.2 Evento B
Feb 02 2024 10:00:00 10.0.0.3 Evento C
Feb 02 2024 11:00:00 10.0.0.4 Evento D
Mar 03 2024 10:00:00 10.0.0.5 Evento E
EOF
out="$(
    cd "$TMP/empates" || exit 1
    "$BIN" <<'EOF'
2
4
5
EOF
)"
printf '%s\n' "$out"
check "detecta el máximo entre días empatados" "$out" "Dia con mas incidentes: Jan 01 2024 (2 incidentes)"
check_absent "excluye días con menos incidentes" "$out" "Mar 03 2024"

section "Resumen"
if [ "$fallos" -eq 0 ]; then
    echo "Todas las pruebas pasaron."
    exit 0
else
    echo "Pruebas fallidas: $fallos"
    exit 1
fi

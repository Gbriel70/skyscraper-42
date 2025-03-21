#!/bin/bash

make

# Cores para output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Função para executar testes
run_test() {
    local input=$1
    local description=$2
    local expected=$3  # "success" ou "failure"
    
    echo -e "${YELLOW}Teste: $description${NC}"
    echo "Input: $input"
    echo -e "Resultado esperado: ${BLUE}$expected${NC}"
    
    # Executar programa e capturar saída
    output=$(./sky "$input" 2>&1)
    exit_code=$?
    
    # Verificar resultado
    if [ $exit_code -eq 0 ] && [[ ! "$output" =~ "Error" ]] && [[ ! "$output" =~ "Não foi possível" ]]; then
        if [ "$expected" == "success" ]; then
            echo -e "${GREEN}Resultado: SUCESSO (como esperado)${NC}"
        else
            echo -e "${RED}Resultado: SUCESSO (esperava falha)${NC}"
        fi
        echo "Solução encontrada:"
        echo "$output"
    else
        if [ "$expected" == "failure" ]; then
            echo -e "${GREEN}Resultado: FALHA (como esperado)${NC}"
        else
            echo -e "${RED}Resultado: FALHA (esperava sucesso)${NC}"
        fi
        echo "$output"
    fi
    echo "-------------------------------------"
}

# === TESTES QUE DEVEM FUNCIONAR ===
echo -e "\n${GREEN}=== TESTES QUE DEVEM FUNCIONAR ===${NC}"

# Combinações conhecidas com solução
run_test "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2" "Caso básico 1 - entrada conhecida" "success"
run_test "2 2 1 3 2 2 3 1 2 3 2 1 3 1 2 2" "Caso básico 2 - entrada conhecida" "success"
run_test "3 2 2 1 2 2 1 3 1 3 2 2 3 1 2 2" "Caso básico 3 - entrada conhecida" "success"
run_test "1 3 2 3 3 1 2 3 2 3 1 2 2 1 3 2" "Caso básico 4 - entrada conhecida" "success"

# === TESTES QUE DEVEM FALHAR ===
echo -e "\n${RED}=== TESTES QUE DEVEM FALHAR ===${NC}"

# Casos com valores inválidos
run_test "5 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2" "Valor inválido (5)" "failure"
run_test "0 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2" "Valor inválido (0)" "failure"

# Casos com contradições óbvias
run_test "4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4" "Contradição - todos 4s" "failure"
run_test "1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1" "Contradição - todos 1s" "failure"

# Casos com número incorreto de valores
run_test "1 2 3" "Poucos valores" "failure"
run_test "1 2 3 4 1 2 3 4 1 2 3 4 1 2 3 4 5" "Muitos valores" "failure"

# Contradições específicas
run_test "4 1 2 3 1 2 3 4 4 3 2 1 1 2 3 4" "Contradição nas restrições" "failure"
run_test "4 3 2 1 4 3 2 1 4 3 2 1 4 3 2 1" "Contradição complexa" "failure"

# === CASOS DE BORDA ===
echo -e "\n${BLUE}=== CASOS DE BORDA ===${NC}"

# Caso com restrições rigorosas mas válidas
run_test "2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2" "Todas restrições 2s" "failure"  # Provavelmente impossível

# Caso com apenas algumas restrições estritas
run_test "1 3 3 2 2 1 2 3 3 1 2 3 3 3 1 2" "Mistura de restrições" "success"

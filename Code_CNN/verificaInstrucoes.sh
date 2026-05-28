#!/bin/bash

# Verifica se o arquivo foi fornecido como argumento
if [ -z "$1" ]; then
    echo "Uso: $0 <arquivo.hex>"
    exit 1
fi

ARQUIVO="$1"

# Verifica se o arquivo existe
if [ ! -f "$ARQUIVO" ]; then
    echo "Arquivo não encontrado: $ARQUIVO"
    exit 1
fi

# Instruções RISC-V a serem procuradas
instrucoes=("fence" "fence.i" "ecall" "ebreak" "csrrw" "csrrs" "csrrc" "csrrwi" "csrrsi" "csrrci")

# Função para converter o arquivo HEX para um arquivo binário
convert_hex_to_bin() {
    xxd -r -p "$ARQUIVO" temp.bin
}

# Função para converter o arquivo binário para assembly RISC-V
disassemble_bin_to_asm() {
    ~/apps/riscv64/bin/riscv64-unknown-elf-objdump -D -b binary -m riscv:rv64 temp.bin > temp.asm
}

# Converte o arquivo HEX para binário
convert_hex_to_bin

# Desmonta o binário para obter o assembly RISC-V
disassemble_bin_to_asm

# Verifica a presença de cada instrução no arquivo assembly
for instrucao in "${instrucoes[@]}"; do
    if grep -q "\b$instrucao\b" temp.asm; then
        echo "Instrução encontrada: $instrucao"
    else
        echo "Instrução não encontrada: $instrucao"
    fi
done

# Limpa os arquivos temporários
rm temp.bin temp.asm

exit 0

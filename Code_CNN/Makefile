CC =        ~/apps/riscv64/bin/riscv64-unknown-elf-gcc
ELFSIZE =   ~/apps/riscv64/bin/riscv64-unknown-elf-size#/opt/riscv64/bin/riscv64-unknown-elf-size
OBJCOPY =   ~/apps/riscv64/bin/riscv64-unknown-elf-objcopy#/opt/riscv64/bin/riscv64-unknown-elf-objcopy

CFLAGS =  -Os -mabi=ilp32f -march=rv32if
LDFLAGS = -Tlink.ld -fno-builtin-printf --specs=nano.specs -nostartfiles -lm -Iheaders/sample0 -Iheaders/layers

SRCS =  main_cnn.c conv1D.c maxPool1D.c dense.c #main_original.c #main_original.c 


.PHONY: all
all: mem_init_generate

main.elf: $(SRCS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	$(ELFSIZE) $@

mem_init/sys_onchip_memory2_0.hex: main.elf
	$(OBJCOPY) -O binary --gap-fill 0 $< ../mem_init/sys_onchip_memory2_0.bin
	$(OBJCOPY) -O verilog --gap-fill 0 $< ../mem_init/sys_onchip_memory2_0.vh
	./bin2hex_2 ../mem_init/sys_onchip_memory2_0.bin ../mem_init/sys_onchip_memory2_0.hex

.PHONY: mem_init_generate
mem_init_generate: mem_init/sys_onchip_memory2_0.hex


.PHONY: clean
clean: 
	rm -f *.elf

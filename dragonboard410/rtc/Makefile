#compilador utilizado
CROSS_COMPILER_PREFIX = /opt/db410/toolchain/bin/aarch64-linux-gnu

#Arquivos fonte
C_SRCS = main.c

#Objeto gerado na compilação do fonte
OBJS = main.o 

LIBS := -lpthread

all: main

#Compila todos os fontes indicados
$(OBJS): $(C_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	$(CROSS_COMPILER_PREFIX)-gcc -Wall -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


# gera o arquivo executável
main: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	$(CROSS_COMPILER_PREFIX)-gcc -o main $(OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '


clean:
	$(RM) $(OBJS) main
	@echo ' '
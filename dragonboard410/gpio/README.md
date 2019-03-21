# Compilação na máquina de desenvolvimento

A compilação pode ser realizada na máquina de desenvolvimento usando um cross-compiler. Posteriormente, os programas compilados devem ser gravados na Dragonboard ou em um diretório compartilhado via rede.

> export CROSS_COMPILE= /opt/db410/toolchain/bin/aarch64-linux-gnu

> $(CROSS_COMPILE)-gcc output.c -o led

> $(CROSS_COMPILE)-gcc input.c -o btn

# Compilação na Dragonboard

A compilação pode ser realizada na Dragonboard usando o GCC

> gcc output.c -o led

> gcc input.c -o btn

# Executando os programas

Para executar o programa basta executá-lo com permissão de *superuser*.

> sudo ./led

> sudo ./btn
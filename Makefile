# Makefile para o segundo projeito de SCC 0224/0606 – Estruturas de Dados II
# 
# Alunos:
#		Carlos Henrique Craveiro Aquino Veras - NUSP 12547187
# 	Pedro Gudin - NUSP ??
# 	Arthur Weber - NUSP ?? 

# CONFIGURACOES DO PROJETO
MODO = RELEASE #(DEBUG/RELEASE)
DIR_FONTE = src
DIR_OBJ = obj
DIR_BIN = bin
DIR_FILE = files

# FIM DAS CONFIGURACOES DO PROJETO

# CONFIGURACAO DOS EXERCICIOS
CODIGOS_FONTES = $(shell find $(DIR_FONTE)/exercicio*.c)
OBJETOS = $(CODIGOS_FONTES:$(DIR_FONTE)/%.c=$(DIR_OBJ)/%.o)
BINARIOS = $(OBJETOS:$(DIR_OBJ)/%.o=$(DIR_BIN)/%.bin)
# FIM DA CONFIGURACAO DOS EXERCICIOS

# CONFIGURACOES DE DEPENDENCIAS DOS EXERCICIOS
exercicio1a_DEPS = \


exercicio1b_DEPS = \


exercicio1c_DEPS = \


exercicio1d_DEPS = \


exercicio2a_DEPS = \


exercicio2b_DEPS = \


exercicio2c_DEPS = \
# FIM DA CONFIGURACAO DE DEPENDENCIAS DOS EXERCICIOS

# CONFIGURACOES DO COMPILADOR
CC = gcc
C_FLAGS = -lm
ifeq ($(MODE),DEBUG)
	C_FLAGS += -Wall -g
endif
# FIM DAS CONFIGURACOES DO COMPILADOR

# REGRAS PARA CONSTRUCAO DOS EXERCICIOS
all	: $(BINARIOS)

$(DIR_BIN)/%.bin	:	$(DIR_OBJ)/%.o
	$(CC) $(C_FLAGS) -o $@ $< $($*_DEPS)

$(DIR_OBJ)/%.o	:	$(DIR_FONTE)/%.c
	$(CC) $(C_FLAGS) -o $@ -c $<

run	:
	./$(DIR_BIN)/$(filter-out $@,$(MAKECMDGOALS)).bin

%	:
		@:

clean	:
	rm -rf $(OBJETOS)
	rm -rf $(BINARIOS)

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
BINARIOS = $(CODIGOS_FONTES:$(DIR_FONTE)/%.c=$(DIR_BIN)/%.bin)
# FIM DA CONFIGURACAO DOS EXERCICIOS

# CONFIGURACOES DE DEPENDENCIAS DOS EXERCICIOS
exercicio1a_DEPS = \


exercicio1b_DEPS = \


exercicio1c_DEPS = \


exercicio1d_DEPS = \


exercicio2a_DEPS = \
										src/funcs_exercicio2.c \
										src/tabelaHash2ab.c \
										src/funcs_time.c

exercicio2b_DEPS = \
										src/funcs_exercicio2.c \
										src/tabelaHash2ab.c \
									 	src/funcs_time.c 


exercicio2c_DEPS = \
										src/funcs_exercicio2.c \
									 	src/funcs_time.c
#										src/tabelaHash2c.c 

OBJETOS += $(exercicio1a_DEPS:$(DIR_FONTE)/%.c=$(DIR_OBJ)/%.o)
OBJETOS += $(exercicio1b_DEPS:$(DIR_FONTE)/%.c=$(DIR_OBJ)/%.o)
OBJETOS += $(exercicio1c_DEPS:$(DIR_FONTE)/%.c=$(DIR_OBJ)/%.o)
OBJETOS += $(exercicio1d_DEPS:$(DIR_FONTE)/%.c=$(DIR_OBJ)/%.o)
OBJETOS += $(exercicio2a_DEPS:$(DIR_FONTE)/%.c=$(DIR_OBJ)/%.o)
OBJETOS += $(exercicio2b_DEPS:$(DIR_FONTE)/%.c=$(DIR_OBJ)/%.o)
OBJETOS += $(exercicio2c_DEPS:$(DIR_FONTE)/%.c=$(DIR_OBJ)/%.o)
# FIM DA CONFIGURACAO DE DEPENDENCIAS DOS EXERCICIOS

# CONFIGURACOES DO COMPILADOR
CC = gcc
C_FLAGS = -lm
ifeq ($(MODE),DEBUG)
	C_FLAGS += -Wall -g
endif
# FIM DAS CONFIGURACOES DO COMPILADOR

# REGRAS PARA CONSTRUCAO DOS EXERCICIOS
all	: $(OBJETOS) $(BINARIOS)

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

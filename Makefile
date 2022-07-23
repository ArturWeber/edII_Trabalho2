# Makefile para o segundo projeito de SCC 0224/0606 – Estruturas de Dados II
# 
# Alunos:
# 	Artur Brenner Weber - NUSP 12675451
#	Carlos Henrique Craveiro Aquino Veras - NUSP 12547187
# 	Pedro Borges Gudin - NUSP 12547997
 

# CONFIGURACOES DO PROJETO
MODO = RELEASE #(DEBUG/RELEASE)
DIR_FONTE = src
DIR_BIN = bin
DIR_FILE = files
DIR_NUSPS =12675451-12547187-12547997 
# FIM DAS CONFIGURACOES DO PROJETO

# CONFIGURACAO DOS EXERCICIOS
CODIGOS_FONTES = $(shell find $(DIR_FONTE)/exercicio*.c)
BINARIOS = $(CODIGOS_FONTES:$(DIR_FONTE)/%.c=$(DIR_BIN)/%.bin)
# FIM DA CONFIGURACAO DOS EXERCICIOS

# CONFIGURACOES DO COMPILADOR
CC = gcc
C_FLAGS = -lm
ifeq ($(MODE),DEBUG)
	C_FLAGS += -Wall -g
endif
# FIM DAS CONFIGURACOES DO COMPILADOR

# REGRAS PARA CONSTRUCAO DOS EXERCICIOS
all	: $(BINARIOS)

$(DIR_BIN)/%.bin	:	$(DIR_FONTE)/%.c
	$(CC) $(C_FLAGS) -o $@ $<

run	:
	./$(DIR_BIN)/$(filter-out $@,$(MAKECMDGOALS)).bin

%	:
		@:

clean	:
	rm -rf $(BINARIOS)

zip :
	make clean
	mkdir $(DIR_NUSPS) 
	cp --target-directory=$(DIR_NUSPS) -r $(DIR_FONTE) $(DIR_FILE) Makefile $(DIR_BIN)
	zip -r $(DIR_NUSPS).zip $(DIR_NUSPS)
	rm -rf $(DIR_NUSPS)

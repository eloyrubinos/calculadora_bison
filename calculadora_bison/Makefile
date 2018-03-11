CC= gcc -Wall
HEADER_FILES_DIR = .
INCLUDES = -I $(HEADER_FILES_DIR)
MAIN= calculadora
SRCS = gestionErrores.c ArbolBinario.c TablaSimbolos.c lex.yy.c anaSin.tab.c main.c
DEPS = $(HEADER_FILES_DIR)/Definiciones.h Funciones.h gestionErrores.h ArbolBinario.h  TablaSimbolos.h lex.yy.h anaSin.tab.h
OBJS = $(SRCS:.c=.o)
$(MAIN): $(OBJS)
	$(CC) -o $(MAIN) $(OBJS) -lm
	rm -f *.o *~
%.o: %.c $(DEPS)
	$(CC) -c $< $(INCLUDES)
cleanall: clean
	rm -f $(MAIN)
clean:
	rm -f *.o *~

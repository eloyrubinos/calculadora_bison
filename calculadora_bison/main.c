#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TablaSimbolos.h"
#include "lex.yy.h"
#include "anaSin.tab.h"
#include "Definiciones.h"

int main(int argc, char **argv) {

printf("\n----------------------------------------CALCULADORA CIENTIFICA----------------------------------------\n"
" - Si terminas las sentencias con \";\" se imprimirá en pantalla el resultado.\n"
" - Si no terminas con \";\" no te preocupes, las operaciones se están haciendo igual, pero no las ves.\n"
" - Puedes consultar los contenidos de las variables en todo momento escribiendo \"verEstado\".\n"
" - Puedes terminar la ejecución en todo momento escribiendo \"salir\".\n"
" - Se recomienda leer la ayuda, lanzando la calculadora con la opción -h o escribiendo \"verAyuda\".\n"
"\n                                           Ya puedes empezar.\n\n");

    iniciarTabla(); // Inicializo la tabla de símbolos, cargando las constantes y las funciones.

	if(argc > 2) { // Compruebo los argumentos.
		printf("El programa no acepta tantos argumentos!\n");
		return (EXIT_FAILURE);
	}
    else if(argc == 2){
		if(!strcmp(argv[1], "-h")) verAyuda();
		else leer(argv[1]);
	}

	yyparse(); // Ejecuto el analizador sintáctico.

	eliminarTabla(); // Libero memoria de la tabla de símbolos.
   	return (EXIT_SUCCESS);
}

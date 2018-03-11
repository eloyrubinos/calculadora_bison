#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "ArbolBinario.h"
#include "Funciones.h"
#include "gestionErrores.h"

void insertaConstante(char *cadena, float valor);
short insertaFuncion(char* cadena, void * fnc);

/* Tamaño de la cadena en que almaceno las lecturas de lexemas de la tabla de símbolos. Sé que el lexema más grande es de longitud 2
   porque el archivo de definiciones es un fichero estático que puedo comprobar en todo momento.
   Si en algún momento añadiese un lexema más grande, es fácil venir aquí y cambiar esta constante.*/
#define TAM 2 

abb tabla; // Mi tabla de símbolos. Un árbol binario.

/* Creo la tabla de símbolos y la relleno con constantes y funciones. */
void iniciarTabla(){
    size_t len = 100; // Longitud de la variable en que voy a almacenar las líneas leídas.
    char* line = (char*) malloc(len * sizeof(char)); // Variable en que almaceno líneas completas del fichero de definiciones.
    ssize_t lectura = 1; // Caracteres leídos por la función getline(), o EOF cuando llega al final del fichero o se produce algún error.
    char* lexemaDefs = (char*) malloc(TAM * sizeof(char)); // Variable para almacenar los lexemas cuando los recibo.  
    char* macro = (char*) malloc((TAM+1) * sizeof(char)); // Variable para almacenar las macros cuando las recibo. Tengo que almacenarlas aunque me den igual para leer con sscanf porque no son iguales siempre.
    int args, i; // Variable para almacenar el número de argumentos almacenados por sscanf().
    float valor; // Variable para almacenar el valor de las constantes.
    crea(&tabla);  // Inicializo la tabla de símbolos.
    
    FILE *defs;
    if((defs = fopen("Definiciones.h", "r")) == NULL){ // Intento abrir el documento de definiciones.
        errorIO("\nFallo al abrir el fichero de definiciones.\n");
    }
    else{ // Si se abre con éxito:
        while((lectura = getline(&line, &len, defs)) != -1){
            if((args = sscanf(line, "#define %s %f //%s", macro, &valor, lexemaDefs)) < 3) break;
            insertaConstante(lexemaDefs, valor);
        }
        if(lectura == -1) errorIO("Fallo al leer el fichero de definiciones.\n");
    }
    if(line != NULL){
        free(line);
        line = NULL;
    }
    if(lexemaDefs != NULL){
        free(lexemaDefs);
        lexemaDefs = NULL;
    }
    if(macro != NULL){
        free(macro);
        macro = NULL;
    }

	for(i = 0; arith_fncts[i].fname != 0; i++){
		insertaFuncion(arith_fncts[i].fname, arith_fncts[i].fnc);
	}
	
}


short esMiembro(char* cadena, short tipo){
    return (es_miembro(&tabla, cadena, tipo));
}

void insertaConstante(char *cadena, float valor){
    inserta_constante(&tabla, cadena, valor);
}

float insertaVariable(char *cadena, float valor){
    return (inserta_y_actualiza_variable(&tabla, cadena, valor));
}

float recuperaDato(char *cadena){
    return (recupera_dato(&tabla, cadena));
}

short insertaFuncion(char* cadena, void * fnc){
    return (inserta_funcion(&tabla, cadena, fnc));
}

float ejecutaFuncion(char* cadena, float entrada){
	return (ejecutar_funcion(&tabla, cadena, entrada));
}

float ejecutaFuncionDos(char* cadena, float entrada, float entrada2){
	return (ejecutar_funcion_dos(&tabla, cadena, entrada, entrada2));
}


void imprimirTabla(){
    printf("\n-----------------Tabla de simbolos-----------------\n");
    imprimirArbol(&tabla);
    printf("\n\n");
}

void imprimirEstado(){
	printf("\n-----------Espacio de trabajo-----------\n");
	imprimirVariables(&tabla);
	printf("\n");
}

void eliminarTabla(){
    destruye(&tabla);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Definiciones.h"

////////////////////////////////////////////////////////////
typedef struct {char* lexema; short tipo; float valor; double (*fnc)();} elemento;
typedef char* indice;
////////////////////////////////////////////////////////////////

struct celda {
    elemento info;
    struct celda *izq, *der;
};

typedef struct celda * abb;

void crea(abb *A) {
    *A = NULL;
}

void destruye(abb *A) {
    if (*A != NULL) {
        destruye(&(*A)->izq);
        destruye(&(*A)->der);
        free(*A);
        *A = NULL;
    }
}

unsigned esVacio(abb A) {
    return A == NULL;
}

short es_miembro(abb *A, char* cadena, short tipo){
    if (esVacio(*A)){
        return (0);
    }
    else if (strcmp(cadena,(*A)->info.lexema)==0){
        if((*A)->info.tipo == tipo) return (1);
        else return (0);
    }
    else if (strcmp(cadena,(*A)->info.lexema)<0){
        return (es_miembro(&(*A)->izq, cadena, tipo));
    }
    else{
        return (es_miembro(&(*A)->der, cadena, tipo));
    }
}

void inserta_constante(abb *A, char* cadena, float valor) {
    if (esVacio(*A)) {
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info.lexema = (char*) malloc(strlen(cadena) * sizeof(char));
        (*A)->info.lexema[0] = '\0';
        strncat((*A)->info.lexema, cadena, strlen(cadena));
        (*A)->info.tipo = _CONSTANTE;
	(*A)->info.valor = valor;
        (*A)->izq = NULL;
        (*A)->der = NULL;
    } else if (strcmp(cadena,(*A)->info.lexema)<0)
        inserta_constante(&(*A)->izq, cadena, valor);
    else
        inserta_constante(&(*A)->der, cadena, valor);
}

float inserta_y_actualiza_variable(abb *A, char* cadena, float valor){
    if (esVacio(*A)){
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info.lexema = (char*) malloc(strlen(cadena) * sizeof(char));
        (*A)->info.lexema[0] = '\0';
        strncat((*A)->info.lexema, cadena, strlen(cadena));
        (*A)->info.tipo = _VARIABLE;
        (*A)->info.valor = valor;
        (*A)->izq = NULL;
        (*A)->der = NULL;
        return (valor);
    }
    else if (strcmp(cadena,(*A)->info.lexema)==0){
        (*A)->info.valor = valor;
        return ((*A)->info.valor);
    }
    else if (strcmp(cadena,(*A)->info.lexema)<0){
        return (inserta_y_actualiza_variable(&(*A)->izq, cadena, valor));
    }
    else{
        return (inserta_y_actualiza_variable(&(*A)->der, cadena, valor));
    }
}

float recupera_dato(abb *A, char* cadena){
    if (strcmp(cadena,(*A)->info.lexema)==0){
        return ((*A)->info.valor);
    }
    else if (strcmp(cadena,(*A)->info.lexema)<0){
        return (recupera_dato(&(*A)->izq, cadena));
    }
    else{
        return (recupera_dato(&(*A)->der, cadena));
    }
}

short inserta_funcion(abb *A, char* cadena, void * fnc){
    if (esVacio(*A)){
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info.lexema = (char*) malloc(strlen(cadena) * sizeof(char));
        (*A)->info.lexema[0] = '\0';
        strncat((*A)->info.lexema, cadena, strlen(cadena));
        (*A)->info.tipo = _FNC;
        (*A)->info.fnc = fnc;
        (*A)->izq = NULL;
        (*A)->der = NULL;
        return (1);
    }
    else if (strcmp(cadena,(*A)->info.lexema)==0){
        return (0);
    }
    else if (strcmp(cadena,(*A)->info.lexema)<0){
        return (inserta_funcion(&(*A)->izq, cadena, fnc));
    }
    else{
        return (inserta_funcion(&(*A)->der, cadena, fnc));
    }
}

void* recupera_funcion(abb *A, char* cadena){
    if (strcmp(cadena,(*A)->info.lexema)==0){
        return ((*A)->info.fnc);
    }
    else if (strcmp(cadena,(*A)->info.lexema)<0){
        return (recupera_funcion(&(*A)->izq, cadena));
    }
    else{
        return (recupera_funcion(&(*A)->der, cadena));
    }
}

float ejecutar_funcion(abb *A, char* cadena, float entrada){
    if (strcmp(cadena,(*A)->info.lexema)==0){
        return ((*A)->info.fnc(entrada));
    }
    else if (strcmp(cadena,(*A)->info.lexema)<0){
        return (ejecutar_funcion(&(*A)->izq, cadena, entrada));
    }
    else{
        return (ejecutar_funcion(&(*A)->der, cadena, entrada));
    }
}

float ejecutar_funcion_dos(abb *A, char* cadena, float entrada, float entrada2){
    if (strcmp(cadena,(*A)->info.lexema)==0){
        return ((*A)->info.fnc(entrada, entrada2));
    }
    else if (strcmp(cadena,(*A)->info.lexema)<0){
        return (ejecutar_funcion_dos(&(*A)->izq, cadena, entrada, entrada2));
    }
    else{
        return (ejecutar_funcion_dos(&(*A)->der, cadena, entrada, entrada2));
    }
}

void imprimirArbol(abb *A){
    short i;
    char* tipo;

    if(!esVacio(*A)){
        if(&(*A)->izq != NULL)
            imprimirArbol(&(*A)->izq);
        
        printf("Nombre: %s", (*A)->info.lexema);
        for(i = 0; i < 12 - strlen((*A)->info.lexema); i++){
            printf(" ");
        }
	if((*A)->info.tipo == _VARIABLE) tipo = "Variable";
	else if((*A)->info.tipo == _CONSTANTE) tipo = "Constante";
	else if((*A)->info.tipo == _FNC) tipo = "Funcion";
        printf("Tipo: %s", tipo);
	if((*A)->info.tipo == _FNC) printf("\n");
	else{
		for(i = 0; i < 12 - strlen(tipo); i++){
		    printf(" ");
		}
		printf("Valor: %.4f\n", (*A)->info.valor);
	}
        
        if(&(*A)->der != NULL)
            imprimirArbol(&(*A)->der); 
    }
}

void imprimirVariables(abb *A){
	short i;

	if(!esVacio(*A)){
        if(&(*A)->izq != NULL)
            imprimirVariables(&(*A)->izq);
        
        if((*A)->info.tipo == _VARIABLE){
		printf("Nombre: %s", (*A)->info.lexema);
		for(i = 0; i < 12 - strlen((*A)->info.lexema); i++){
		    printf(" ");
		}
		printf("Valor: %.6f\n", (*A)->info.valor);
	}
        
        if(&(*A)->der != NULL)
            imprimirVariables(&(*A)->der); 
    }
}

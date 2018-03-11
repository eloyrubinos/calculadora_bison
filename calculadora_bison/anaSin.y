%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TablaSimbolos.h"
#include "Definiciones.h"
#include "lex.yy.h"

extern int yylex();
void yyerror(char* s);
void verAyuda();
%}

%union {
float	num;
char	*lexema;
}


%start input


%token <num> NUM
%token <lexema> IDENTIFICADOR
%token <lexema> ARCHIVO

%token ESTADO
%token TABLA
%token AYUDA
%token LEER


%token OP_SUMA_CMPX
%token OP_RESTA_CMPX
%token OP_MULT_CMPX
%token OP_DIV_CMPX


%right _OP_ASIG
%left '-' '+' OP_SUMA_CMPX OP_RESTA_CMPX
%left '*' '/' '%' OP_DIV_CMPX OP_MULT_CMPX
%left '>' '<'
%left NEG
%right '^'

%type <num> comparacion
%type <num> expresion
%type <num> operacion
%type <num> definicion
%type <num> fnc

%%
input:  /* vacío */
        | input line
;

line:   '\n'
        | expresion '\n' { printf("\n"); }
		| expresion ';' '\n' { printf (">%.2f\n\n",$1); }
		| error {yyclearin;}
;

expresion:		NUM	{$$ = $1;}
        		| IDENTIFICADOR		{ if(esMiembro($1, _VARIABLE) || esMiembro($1, _CONSTANTE)){ 
        								$$ = recuperaDato($1);
        							  } else yyerror("Parece que todavía no has inicializado esa variable.");  
        						    }
        		| definicion
                | comparacion
        		| fnc	
        		| '(' expresion ')' {$$ = $2;}
        		| operacion
            	| ESTADO {imprimirEstado();}
				| TABLA {imprimirTabla();}
            	| AYUDA {verAyuda();}
            	| LEER ARCHIVO {printf("Ejecutando...\n"); leer($2);}
;

definicion: 	IDENTIFICADOR _OP_ASIG expresion   { if(!esMiembro($1, _CONSTANTE)){
														insertaVariable($1, $3); 
														$$ = $3;
						    						} else yyerror("No puedes modificar una constante.");
												    }
				| IDENTIFICADOR OP_SUMA_CMPX expresion { if(esMiembro($1, _VARIABLE)){
															$$ = recuperaDato($1) + $3;
															insertaVariable($1, $$);
														  } else yyerror("Parece que todavía no has inicializado esa variable.");
														}
				| IDENTIFICADOR OP_RESTA_CMPX expresion { if(esMiembro($1, _VARIABLE)){
															$$ = recuperaDato($1) - $3;
															insertaVariable($1, $$);
														  } else yyerror("Parece que todavía no has inicializado esa variable.");
														}
				| IDENTIFICADOR OP_MULT_CMPX expresion { if(esMiembro($1, _VARIABLE)){
															$$ = recuperaDato($1) * $3;
															insertaVariable($1, $$);
														  } else yyerror("Parece que todavía no has inicializado esa variable.");
														}
				| IDENTIFICADOR OP_DIV_CMPX expresion { if(esMiembro($1, _VARIABLE)){
															$$ = recuperaDato($1) / $3;
															insertaVariable($1, $$);
														  } else yyerror("Parece que todavía no has inicializado esa variable.");
														}
;

comparacion:    expresion '>' expresion { if($1 > $3) printf("Verdadero\n");
                                          else printf("Falso\n");
                                        }
                | expresion '<' expresion { if($1 < $3) printf("Verdadero\n");
                                            else printf("Falso\n");
                                          }
;

fnc: 			IDENTIFICADOR '(' expresion ')' { if(esMiembro($1, _FNC)){  
        											$$ = ejecutaFuncion($1, $3);
        									   	  } else yyerror("No encuentro esa función..."); 
        										}
				| IDENTIFICADOR '(' expresion ',' expresion ')' { if(esMiembro($1, _FNC)){
																	$$ = ejecutaFuncionDos($1, $3, $5);
																   } else yyerror("No encuentro esa función...");
																}
				| expresion '^' expresion { if(esMiembro("^", _FNC)){
												$$ = ejecutaFuncionDos("pow", $1, $3);
											} else yyerror("No encuentro esa función...");
										   }
;

operacion:		expresion '+' expresion   {$$ = $1 + $3;}
        		| expresion '-' expresion {$$ = $1 - $3;}
        		| expresion '*' expresion {$$ = $1 * $3;}
        		| expresion '/' expresion {	if($3 != 0){
        										$$ = $1 / $3;
        									} else { 
        										yyerror("Quieres crear un agujero negro o qué >:("); 
        									} 
        								}
                | '-' expresion %prec NEG {$$ = -$2;}
            	| expresion '%' expresion {$$ = (int) $1 % (int) $3;}
;


%%

void yyerror(char* s){
  printf ("> Oops -> %s <\n\n", s);
}

void verAyuda(){
	FILE *ayuda;
	if((ayuda = fopen("AYUDA.txt", "r")) == NULL) yyerror("Parece que la ayuda se ha perdido. Buena suerte!");
	else{
		fclose(ayuda);
		system("cat AYUDA.txt");
	}
}

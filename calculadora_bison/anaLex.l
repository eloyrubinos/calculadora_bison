%{
#include "TablaSimbolos.h"
#include "Definiciones.h"
#include "gestionErrores.h"
#include "anaSin.tab.h"

void leer(char* file);
void cerrar();

%}

/* No proporciono definción para la función yywrap. */
%option noyywrap
 /* Para contar las líneas. */
%option yylineno

%option nounput
%option noinput


NEWLINE                       \n
ESPACIO                       [ ]
SEPARADOR                     (\t|\r|{ESPACIO})+
UNICODE_CHAR                  .
UNICODE_LETTER                [A-Za-z]
LETTER                        {UNICODE_LETTER}|_
DECIMAL_DIGIT                 [0-9]
UNICODE_DIGIT                 {DECIMAL_DIGIT}
SEMICOLON                     ;
COLON                         ,

DECIMAL_LIT                   [1-9]{DECIMAL_DIGIT}*
INT_LIT                       {DECIMAL_DIGIT}+

DECIMALS                      {DECIMAL_DIGIT}+
EXPONENT                      [eE][+-]?{DECIMALS}
FLOAT_LIT                     {DECIMALS}\.{DECIMALS}?{EXPONENT}?|{DECIMALS}{EXPONENT}|\.{DECIMALS}{EXPONENT}?

NUMERO                        {INT_LIT}|{FLOAT_LIT}


IDENTIFIER                    {LETTER}({LETTER}|{UNICODE_DIGIT})*


ARCHIVO                       ({LETTER}|{UNICODE_DIGIT}|\.)+


OP_PUNC                       [+*/%^,.!><()-]|{SEMICOLON}|{COLON}
OP_ASIG                       =
OP_SUMA_CMPX                  \+=
OP_RESTA_CMPX                 -=
OP_MULT_CMPX                  \*=
OP_DIV_CMPX                   \/=


%x LECTURA

%%

"salir"                         {yyterminate();}

"verEstado"		      		    return (ESTADO);

"verTabla"		      			 return (TABLA);

"verAyuda"                      return (AYUDA);

"leer "	                        { BEGIN(LECTURA); return (LEER); }

{NEWLINE}                       return ((int) *yytext);

{SEPARADOR}                      

<LECTURA>{ARCHIVO}              {yylval.lexema = (char *) malloc(sizeof (yytext));
                                 yylval.lexema = strdup(yytext);
                                 BEGIN(INITIAL); return (ARCHIVO);}

{IDENTIFIER}                   {yylval.lexema = (char *) malloc(sizeof (yytext));
             	                  yylval.lexema = strdup(yytext);
                                  return (IDENTIFICADOR);}

{NUMERO}                        {yylval.num=atof(yytext);
                                  return (NUM);}

{OP_SUMA_CMPX}                  return (OP_SUMA_CMPX);
{OP_RESTA_CMPX}                 return (OP_RESTA_CMPX);
{OP_MULT_CMPX}                  return (OP_MULT_CMPX);
{OP_DIV_CMPX}                   return (OP_DIV_CMPX);
{OP_ASIG}                       return (_OP_ASIG);
{OP_PUNC}                       return ((int) *yytext);
.                                {errorLexico(yylineno);}
<<EOF>>                         {cerrar(); yyrestart(stdin);}

%%

void leer(char* file){
    if((yyin = fopen(file, "r")) == NULL) {
		errorIO_noFatal("Fallo al abrir el archivo fuente.\n\n");
		yyin = stdin;
	}
}

void cerrar(){
    fclose(yyin);
}

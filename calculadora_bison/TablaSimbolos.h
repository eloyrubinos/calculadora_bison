/* Función que crea la tabla de símbolos y la rellena con las constantes y funciones. */
void iniciarTabla();
/* Función para imprimir la tabla de símbolos entera. */
void imprimirTabla();
/* Función para imprimir solo las variables. */
void imprimirEstado();
/* Función para liberar la memoria de la tabla de símbolos. */
void eliminarTabla();

/* Funciones varias para insertar y recuperar elementos de la tabla. */
short esMiembro(char* cadena, short tipo);
float insertaVariable(char *cadena, float valor);
float recuperaDato(char *cadena);
short insertaFuncion(char* cadena, void * fnc);
float ejecutaFuncion(char* cadena, float entrada);
float ejecutaFuncionDos(char* cadena, float entrada, float entrada2);

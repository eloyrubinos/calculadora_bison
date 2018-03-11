////////////////////////////////////////////////////////////////
typedef struct {char* lexema; short tipo; float valor; double (*fnc)();} elemento;

typedef char* indice;
////////////////////////////////////////////////////////////////
		
typedef void *abb; //tipo opaco

void crea(abb *A);
void destruye(abb *A);
unsigned esVacio(abb A);
short es_miembro(abb *A, char* cadena, short tipo);
void inserta_constante(abb *A, char* cadena, float valor);
float inserta_y_actualiza_variable(abb *A, char* cadena, float valor);
float recupera_dato(abb *A, char* cadena);
short inserta_funcion(abb *A, char* cadena, void * fnc);
double* recupera_funcion(abb *A, char* cadena);
float ejecutar_funcion(abb *A, char* cadena, float entrada);
float ejecutar_funcion_dos(abb *A, char* cadena, float entrada, float entrada2);
short busca_e_inserta(abb *A, char* cadena, short bloque);
void imprimirArbol(abb *A);
void imprimirVariables(abb *A);

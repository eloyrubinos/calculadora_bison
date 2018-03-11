// Función que marca el fin del programa y avisa de que se ha producido un error de lectura/escritura.
void errorIO();
// Igual que la anterior pero sin cerrar el programa.
void errorIO_noFatal(char* mensaje);
// Cuando me encuentre un error léxico puedo llamar a esta función para indicar la línea y el carácter que han dado el problema.
void errorLexico(int linea);

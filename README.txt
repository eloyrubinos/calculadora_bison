Para compilar la calculadora de 0 hay que seguir estos pasos:
	- Compilar con flex: flex --header-file="lex.yy.h" anaLex.l
	- Compilar con Bison: bison -d anaSin.y
	- Compilar el programa: asegúrate de que tienes el Makefile en la carpeta y ejecuta "make".

Listo! Solo queda ejecutarla con ./calculadora
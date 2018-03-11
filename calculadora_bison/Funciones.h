/* En este archivo guardo todas las funciones que voy a usar en la calculadora. Es muy simple añadir funciones nuevas. */
struct init
	{
		char *fname;
		double (*fnc)();
	};
struct init arith_fncts[]
	= { 
		"sin", sin,
		"cos", cos,
		"tan", tan,
		"asin", asin,
		"acos", acos,
		"atan", atan,
		"sinh", sinh,
		"cosh", cosh,
		"tanh", tanh,
		"log10", log10,
		"ln", log,
		"exp", exp,
		"sqrt", sqrt,
		"ceil", ceil,
		"floor", floor,
		"fabs", fabs,
		"pow", pow,
		"^", pow,
		"fmod", fmod,
		0, 0
	};

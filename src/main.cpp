/* ***************************************************************
Para correr este programa instalar la libreria libjsoncpp-dev
En Linux: sudo apt-get install libjsoncpp-dev
Y agregar el siguiente parametro de compilacion en gcc: -ljsoncpp
****************************************************************** */
#include <vector>
#include "Tabla.hpp"
#include "Registro.hpp"
#include "Analizador.hpp"

int main()
{
	// Tabla simbolos("Simbolos.json");
	// vector<Registro> separadores = simbolos.getTablaSimbolos();
	// for (int i = 0; i < separadores.size(); i++)
	// {
	// 	separadores.at(i).toString();
	// }
	Analizador an("Simbolos.json","Codigo.al");
	Tabla::toString(an.getSimbolos());
	// Tabla tb("Simbolos.json");
	// Tabla::toString(tb.getTablaSeparadores());
	// vector<Registro> separadores = an.tablaSeparadores;
	// for (int i = 0; i < separadores.size(); i++)
	// {
	// 	separadores.at(i).toString();
	// }
	return 0;
}
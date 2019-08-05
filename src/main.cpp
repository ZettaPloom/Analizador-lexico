/*
    Copyright @ZettaPloom
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,MA 02110-1301,USA.
*/

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
	Tabla::toString(an.getTablaSeparadores());
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

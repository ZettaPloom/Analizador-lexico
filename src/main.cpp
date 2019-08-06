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
    string rutaSimbolos, rutaCodigo;
    cout << "\nPor favor ingrese la ruta del archivo JSON de la tabla de simbolos" << endl;
    cin >> rutaSimbolos;
    cout << "\nPor favor ingrese la ruta del archivo que contiene el código" << endl;
    cin >> rutaCodigo;
    Analizador an(rutaSimbolos, rutaCodigo);
    int opciones;
etiqueta:
    cout << "\nPresione 1 para imprimir la tabla de simbolos" << endl
         << "Presione 2 para imprimir la tabla de separadores" << endl
         << "Presione 3 para imprimir el análisis léxico del código" <<endl
         << "Presione cualquier otro número para salir" << endl;
    cin >> opciones;
    cout << endl;
    switch (opciones)
    {
    case 1:
        Tabla::toString(an.getTablaSimbolos());
        goto etiqueta;
        break;
    case 2:
        Tabla::toString(an.getTablaSeparadores());
        goto etiqueta;
        break;
    case 3:
        Tabla::toString(an.getSimbolos());
        goto etiqueta;
        break;
    default:
        break;
    }
    return 0;
}

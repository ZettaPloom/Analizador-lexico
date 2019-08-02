#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "Registro.hpp"
#include "Tabla.hpp"
using namespace std;

class Analizador
{
private:
     vector<Registro> tablaSimbolos;
     vector<Registro> tablaSeparadores;
     vector<Registro> simbolos;
public:
    Analizador(string rutaSimbolos,string rutaCodigo);
    void identificarSimbolos(string rutaCodigo);
    bool esOperador(string simbolo);
};

Analizador::Analizador(string rutaSimbolos,string rutaCodigo)
{
    Tabla leerTabla(rutaSimbolos);
    tablaSeparadores=leerTabla.getTablaSeparadores();
    tablaSimbolos=leerTabla.getTablaSimbolos();
    identificarSimbolos(rutaCodigo);
}

void Analizador::identificarSimbolos(string rutaCodigo)
{
    char caracter;
    ifstream archivo(rutaCodigo);
    if(archivo.fail())
        cout<<"Error al abrir el archivo de código"<<endl;
    else
    {
        archivo.get(caracter);
        while (archivo.eof())
        {
            cout<<caracter<<endl;
            archivo.get(caracter);
        }
        archivo.close();
    }
}

bool Analizador::esOperador(string simbolo)
{
    while (true)
    {
        /* code */
    }
}

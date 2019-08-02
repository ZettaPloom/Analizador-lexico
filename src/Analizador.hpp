#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <utility>
#include "Registro.hpp"
#include "Tabla.hpp"
using namespace std;

class Analizador
{
private:
    vector<Registro> simbolos;
    vector<Registro> tablaSimbolos;
    vector<Registro> tablaSeparadores;
public:
    Analizador(string rutaSimbolos, string rutaCodigo);
    void identificarSimbolos(string rutaCodigo);
    bool esSeparador(char simbolo);
};

Analizador::Analizador(string rutaSimbolos, string rutaCodigo)
{
    Tabla leerTabla(rutaSimbolos);
    tablaSeparadores = leerTabla.getTablaSeparadores();
    tablaSimbolos = leerTabla.getTablaSimbolos();
    identificarSimbolos(rutaCodigo);
}

void Analizador::identificarSimbolos(string rutaCodigo)
{
    char caracter;
    string cadena("");
    int indexSeparadores=0;
    int indexSimbolos=0;
    Registro* r;
    pair<int,int> p;//El primero es la linea, el segundo la columna
    vector<pair<int,int>>;
    ifstream archivo(rutaCodigo);
    if (archivo.fail())
        cout << "Error al abrir el archivo de código" << endl;
    else
    {
        archivo.get(caracter);
        while (!archivo.eof())
        {
            if (caracter == '\n')
                cout << endl;
            else{
                cout << caracter;
                if(esSeparador(caracter)){
                    r=&tablaSeparadores.at(indexSeparadores);
                    while (r->getSimbolo().c_str().compare(caracter)==0)
                        indexSeparadores++;
                    
                }else{
                    cadena+=caracter;
                }
            }
            archivo.get(caracter);
        }
        archivo.close();
    }
}

bool Analizador::esSeparador(char simbolo)
{
    bool encontrado=false;
    int i=0;
    while (!encontrado)
    {
        if(tablaSeparadores.at(i).getSimbolo().c_str()==simbolo)
            encontrado=true;
        else
            i++;        
    }
    return encontrado;
}

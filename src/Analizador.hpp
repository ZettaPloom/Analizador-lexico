#ifndef Analizador_H
#define Analizador_H
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
    vector<Registro> tbSimbolos;
    char caracter;
    string cadena("");
    int index=0;
    //pair<int,int> p;//El primero es la linea, el segundo la columna
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
                    Registro r=tablaSeparadores.at(index);
                    while (index<tablaSeparadores.size()&&*r.getSimbolo().c_str()!=caracter)
                    {
                        index++;
                        r=tablaSeparadores.at(index);
                    }
                    tbSimbolos.push_back(r);
                    index=0;
                }else{
                    cadena+=caracter;
                    Registro r=tablaSimbolos.at(index);
                    while (index<tablaSimbolos.size()&&r.getSimbolo()!=cadena)
                    {
                        index++;
                        r=tablaSeparadores.at(index);//Aqui hay un error, se accede a un index por fuera del arreglo
                    }
                    tbSimbolos.push_back(r);
                    index=0;
                }
            }
            archivo.get(caracter);
        }
        archivo.close();
    }
    for (int i = 0; i < tbSimbolos.size(); i++)
    {
        tbSimbolos.at(i).toString();
    }
    
}

bool Analizador::esSeparador(char simbolo)
{
    bool encontrado=false;
    int i=0;
    while (i<tablaSeparadores.size()&&!encontrado)
    {
        if(*tablaSeparadores.at(i).getSimbolo().c_str()==simbolo)
            encontrado=true;
        else
            i++;        
    }
    return encontrado;
}
#endif

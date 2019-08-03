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
    void imprimirSimbolosEncontrados();
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
    int index = 0;
    int fila = 0;
    int columna = 0;
    pair<int, int> p; //El primero es la linea, el segundo la columna
    ifstream archivo(rutaCodigo);
    if (archivo.fail())
        cout << "Error al abrir el archivo de código" << endl;
    else
    {
        archivo.get(caracter);
        while (!archivo.eof())
        {
            if (caracter != '\n')
            {
                if (esSeparador(caracter))
                {
                    Registro r = tablaSeparadores.at(index);
                    while (index < tablaSeparadores.size() - 1 && *r.getSimbolo().c_str() != caracter)
                    {
                        index++;
                        r = tablaSeparadores.at(index);
                    }
                    index = 0;
                    if (*r.getSimbolo().c_str() == caracter)
                    {
                        p.first = fila;
                        p.second = columna;
                        if (!tbSimbolos.empty())
                        {
                            while (index < tbSimbolos.size() - 1 && tbSimbolos.at(index).getSimbolo().compare(r.getSimbolo()) != 0)
                                index++;
                            if (tbSimbolos.at(index).getSimbolo().compare(r.getSimbolo()) == 0)
                                tbSimbolos.at(index).setNuevaPosicion(p);
                            else
                            {
                                r.setNuevaPosicion(p);
                                tbSimbolos.push_back(r);
                            }

                            index = 0;
                        }
                        else
                        {
                            r.setNuevaPosicion(p);
                            tbSimbolos.push_back(r);
                            index = 0;
                        }
                    }
                    index = 0;
                    r = tablaSimbolos.at(index);
                    while (index < tablaSimbolos.size() - 1 && r.getSimbolo() != cadena)
                    {
                        index++;
                        r = tablaSimbolos.at(index);
                    }
                    index = 0;
                    if (r.getSimbolo() == cadena)
                    {
                        p.first = fila;
                        p.second = columna;
                        if (!tbSimbolos.empty())
                        {
                            while (index < tbSimbolos.size() - 1 && tbSimbolos.at(index).getSimbolo().compare(r.getSimbolo()) != 0)
                                index++;
                            if (tbSimbolos.at(index).getSimbolo().compare(r.getSimbolo()) == 0)
                                tbSimbolos.at(index).setNuevaPosicion(p);
                            else
                            {
                                r.setNuevaPosicion(p);
                                tbSimbolos.push_back(r);
                            }
                            index = 0;
                        }
                        else
                        {
                            r.setNuevaPosicion(p);
                            tbSimbolos.push_back(r);
                            index = 0;
                        }
                    }
                    else
                    {
                        p.first = fila;
                        p.second = columna;
                        if (!tbSimbolos.empty())
                        {
                            while (index < tbSimbolos.size() - 1 && tbSimbolos.at(index).getSimbolo().compare(cadena) != 0)
                                index++;
                            if (tbSimbolos.at(index).getSimbolo().compare(cadena) == 0)
                                tbSimbolos.at(index).setNuevaPosicion(p);
                            else
                            {
                                vector<string> v;
                                v.push_back("Identificador");
                                v.push_back("Variable");
                                Registro x("Variable", cadena, v);
                                x.setNuevaPosicion(p);
                                tbSimbolos.push_back(x);
                            }
                            index = 0;
                        }
                        else
                        {
                            vector<string> v;
                            v.push_back("Identificador");
                            v.push_back("Variable");
                            Registro x("Variable", cadena, v);
                            x.setNuevaPosicion(p);
                            tbSimbolos.push_back(x);
                            index = 0;
                        }
                    }
                    index = 0;
                    cadena = "";
                }
                else
                {
                    cadena += caracter;
                }
            }
            archivo.get(caracter);
            columna++;
            if (caracter == '\n')
            {
                columna = 0;
                fila++;
            }
        }
        archivo.close();
    }
    simbolos=tbSimbolos;
}

bool Analizador::esSeparador(char simbolo)
{
    bool encontrado = false;
    int i = 0;
    while (i < tablaSeparadores.size() && !encontrado)
    {
        if (*tablaSeparadores.at(i).getSimbolo().c_str() == simbolo)
            encontrado = true;
        else
            i++;
    }
    return encontrado;
}

void Analizador::imprimirSimbolosEncontrados()
{
    if(!simbolos.empty())
    for (int i = 0; i < simbolos.size(); i++)
    simbolos.at(i).toString();
    
}
#endif

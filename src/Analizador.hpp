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
    bool esSeparador(char simbolo, int fila, int columna);
    bool yaExiste(string simbolo, int fila, int columna);
    void agregarPosicionActual(string simbolo, int fila, int columna);
    void buscarAgregarSimbolo(string simbolo, int fila, int columna);
    vector<Registro> getSimbolos();
    vector<Registro> getTablaSimbolos();
    vector<Registro> getTablaSeparadores();
};

Analizador::Analizador(string rutaSimbolos, string rutaCodigo)
{
    Tabla leerTabla(rutaSimbolos);
    tablaSeparadores = leerTabla.getTablaSeparadores();
    tablaSimbolos = leerTabla.getTablaSimbolos();
    identificarSimbolos(rutaCodigo);
}

// void Analizador::identificarSimbolos(string rutaCodigo)
// {
//     vector<Registro> tbSimbolos;
//     char caracter;
//     string cadena("");
//     int index = 0;
//     int fila = 0;
//     int columna = 0;
//     pair<int, int> p; //El primero es la linea, el segundo la columna
//     ifstream archivo(rutaCodigo);
//     if (archivo.fail())
//         cout << "Error al abrir el archivo de código" << endl;
//     else
//     {
//         archivo.get(caracter);
//         while (!archivo.eof())
//         {
//             if (caracter != '\n')
//             {
//                 if (esSeparador(caracter))
//                 {
//                     Registro r = tablaSeparadores.at(index);
//                     while (index < tablaSeparadores.size() - 1 && *r.getSimbolo().c_str() != caracter)
//                     {
//                         index++;
//                         r = tablaSeparadores.at(index);
//                     }
//                     index = 0;
//                     if (*r.getSimbolo().c_str() == caracter)
//                     {
//                         p.first = fila;
//                         p.second = columna;
//                         if (!tbSimbolos.empty())
//                         {
//                             while (index < tbSimbolos.size() - 1 && tbSimbolos.at(index).getSimbolo().compare(r.getSimbolo()) != 0)
//                                 index++;
//                             if (tbSimbolos.at(index).getSimbolo().compare(r.getSimbolo()) == 0)
//                                 tbSimbolos.at(index).setNuevaPosicion(p);
//                             else
//                             {
//                                 r.setNuevaPosicion(p);
//                                 tbSimbolos.push_back(r);
//                             }

//                             index = 0;
//                         }
//                         else
//                         {
//                             r.setNuevaPosicion(p);
//                             tbSimbolos.push_back(r);
//                             index = 0;
//                         }
//                     }
//                     index = 0;
//                     r = tablaSimbolos.at(index);
//                     while (index < tablaSimbolos.size() - 1 && r.getSimbolo() != cadena)
//                     {
//                         index++;
//                         r = tablaSimbolos.at(index);
//                     }
//                     index = 0;
//                     if (r.getSimbolo() == cadena)
//                     {
//                         p.first = fila;
//                         p.second = columna;
//                         if (!tbSimbolos.empty())
//                         {
//                             while (index < tbSimbolos.size() - 1 && tbSimbolos.at(index).getSimbolo().compare(r.getSimbolo()) != 0)
//                                 index++;
//                             if (tbSimbolos.at(index).getSimbolo().compare(r.getSimbolo()) == 0)
//                                 tbSimbolos.at(index).setNuevaPosicion(p);
//                             else
//                             {
//                                 r.setNuevaPosicion(p);
//                                 tbSimbolos.push_back(r);
//                             }
//                             index = 0;
//                         }
//                         else
//                         {
//                             r.setNuevaPosicion(p);
//                             tbSimbolos.push_back(r);
//                             index = 0;
//                         }
//                     }
//                     else
//                     {
//                         p.first = fila;
//                         p.second = columna;
//                         if (!tbSimbolos.empty())
//                         {
//                             while (index < tbSimbolos.size() - 1 && tbSimbolos.at(index).getSimbolo().compare(cadena) != 0)
//                                 index++;
//                             if (tbSimbolos.at(index).getSimbolo().compare(cadena) == 0)
//                                 tbSimbolos.at(index).setNuevaPosicion(p);
//                             else
//                             {
//                                 vector<string> v;
//                                 v.push_back("Identificador");
//                                 v.push_back("Variable");
//                                 Registro x("Variable", cadena, v);
//                                 x.setNuevaPosicion(p);
//                                 tbSimbolos.push_back(x);
//                             }
//                             index = 0;
//                         }
//                         else
//                         {
//                             vector<string> v;
//                             v.push_back("Identificador");
//                             v.push_back("Variable");
//                             Registro x("Variable", cadena, v);
//                             x.setNuevaPosicion(p);
//                             tbSimbolos.push_back(x);
//                             index = 0;
//                         }
//                     }
//                     index = 0;
//                     cadena = "";
//                 }
//                 else
//                 {
//                     cadena += caracter;
//                 }
//             }
//             archivo.get(caracter);
//             columna++;
//             if (caracter == '\n')
//             {
//                 columna = 0;
//                 fila++;
//             }
//         }
//         archivo.close();
//     }
//     simbolos=tbSimbolos;
// }
void Analizador::identificarSimbolos(string rutaCodigo)
{
    ifstream archivo(rutaCodigo);
    if (archivo.fail())
        cout << "Error al abrir el archivo de código";
    else
    {
        string cadena;
        string simbolo = "";
        char caracter;
        int fila = 0;
        while (!archivo.eof())
        {
            fila++;
            getline(archivo, cadena);
            for (int i = 0; i < cadena.size(); i++) //el contador (i) de este ciclo es la posicion columna en el archivo
            {
                if (esSeparador(cadena.at(i), fila, i))
                {
                    if (!yaExiste(simbolo, fila, i))
                        buscarAgregarSimbolo(simbolo, fila, i);
                    else
                        agregarPosicionActual(simbolo, fila, i);
                    simbolo = "";
                }
                else
                    simbolo += cadena.at(i);
            }
        }
        archivo.close();
    }
}

void Analizador::buscarAgregarSimbolo(string simbolo, int fila, int columna)
{
    int i = 0;
    while (i < tablaSimbolos.size() && tablaSimbolos.at(i).getSimbolo() != simbolo)
        i++;
    if (i < tablaSimbolos.size())
    {
        Registro r = tablaSimbolos.at(i);
        pair<int, int> p(fila, columna);
        simbolos.push_back(r);
        simbolos.back().setNuevaPosicion(p);
    }
    else
    {
        vector<string> v;
        v.push_back("Identificador");
        v.push_back("Variable");
        Registro r("Variable", simbolo, v);
        pair<int, int> p(fila, columna);
        simbolos.push_back(r);
        simbolos.back().setNuevaPosicion(p);
    }
}

vector<Registro> Analizador::getSimbolos()
{
    return this->simbolos;
}

vector<Registro> Analizador::getTablaSimbolos()
{
    return this->tablaSimbolos;
}

vector<Registro> Analizador::getTablaSeparadores()
{
    return this->tablaSeparadores;
}

bool Analizador::esSeparador(char simbolo, int fila, int columna)
{
    bool encontrado = false;
    int i = 0;
    while (i < tablaSeparadores.size() && !encontrado)
        if (*tablaSeparadores.at(i).getSimbolo().c_str() == simbolo)
        {
            encontrado = true;
            if (!yaExiste(to_string(simbolo), fila, columna))
            {
                Registro r = tablaSeparadores.at(i);
                pair<int, int> p(fila, columna);
                simbolos.push_back(tablaSeparadores.at(i));
                simbolos.back().setNuevaPosicion(p);
            }
            else
                agregarPosicionActual(to_string(simbolo), fila, columna);
        }
        else
            i++;
    return encontrado;
}

void Analizador::agregarPosicionActual(string simbolo, int fila, int columna)
{
    int i = 0;
    while (i < simbolos.size() && simbolos.at(i).getSimbolo() != simbolo)
        i++;
    pair<int, int> p(fila, columna);
    simbolos.at(i).setNuevaPosicion(p);
}

bool Analizador::yaExiste(string simbolo, int fila, int columna)
{
    bool existe = false;
    int i = 0;
    while (i < simbolos.size() && !existe)
        if (simbolos.at(i).getSimbolo() == simbolo)
            existe = true;
        else
            i++;
    return existe;
}
#endif

#ifndef Analizador_H
#define Analizador_H
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
    vector<Registro> simbolos;
    vector<Registro> tablaSimbolos;
    vector<Registro> tablaSeparadores;

public:
    Analizador(string rutaSimbolos, string rutaCodigo);
    void identificarSimbolos(string rutaCodigo);
    bool esSeparador(char simbolo, int fila, int columna);
    bool yaExiste(string simbolo, int fila, int columna);
    void buscarAgregarSimbolo(string simbolo, int fila, int columna);
    void buscarAgregarSeparador(string simbolo, int fila, int columna);
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
        string caracter = "";
        int fila = 0;
        while (!archivo.eof())
        {
            fila++;
            getline(archivo, cadena);
            for (int i = 0; i < cadena.size(); i++) //el contador (i) de este ciclo es la posicion columna en el archivo
            {
                if (esSeparador(cadena.at(i), fila, i))
                {
                    caracter = cadena.at(i);
                    buscarAgregarSeparador(caracter, fila, i);
                    buscarAgregarSimbolo(simbolo, fila, i);
                    caracter = "";
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
    if (!yaExiste(simbolo, fila, columna))
    {
        while (i < tablaSimbolos.size() && tablaSimbolos.at(i).getSimbolo().compare(simbolo) != 0)
            i++;
        if (i < tablaSimbolos.size())
        {
            Registro r = tablaSimbolos.at(i);
            r.setNuevaPosicion(fila, columna);
            simbolos.push_back(r);
        }
        else
        {
            vector<string> v;
            v.push_back("Identificador");
            v.push_back("Variable");
            Registro r("Variable", simbolo, v);
            r.setNuevaPosicion(fila, columna);
            simbolos.push_back(r);
        }
    }
}

void Analizador::buscarAgregarSeparador(string simbolo, int fila, int columna)
{
    int i = 0;
    if (!yaExiste(simbolo, fila, columna))
    {
        while (i < tablaSeparadores.size() && tablaSeparadores.at(i).getSimbolo().compare(simbolo) != 0)
            // cout << tablaSeparadores.at(i).getSimbolo() << " " << tablaSeparadores.at(i).getSimbolo().compare(simbolo) << endl;
            i++;
        if (i < tablaSeparadores.size())
        {
            Registro r = tablaSeparadores.at(i);
            r.setNuevaPosicion(fila, columna);
            simbolos.push_back(r);
        }
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
            encontrado = true;
        else
            i++;
    return encontrado;
}

bool Analizador::yaExiste(string simbolo, int fila, int columna)
{
    bool existe = false;
    int i = 0;
    while (i < simbolos.size() && !existe)
        if (simbolos.at(i).getSimbolo().compare(simbolo) == 0)
        {
            existe = true;
            simbolos.at(i).setNuevaPosicion(fila, columna);
        }
        else
            i++;
    return existe;
}
#endif

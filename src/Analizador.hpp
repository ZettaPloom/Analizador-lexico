#ifndef Analizador_H
#define Analizador_H
#include <vector>
#include <fstream>
#include <string>
#include "Registro.hpp"
#include "Tabla.hpp"

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
    bool yaExiste(string simbolo, string fila, string columna);
    void buscarAgregarSimbolo(string simbolo, string fila, string columna);
    void buscarAgregarSeparador(string simbolo, string fila, string columna);
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
        int columna = 0;
        while (!archivo.eof())
        {
            fila++;
            getline(archivo, cadena);
            for (int i = 0; i < cadena.size(); i++) //el contador (i) de este ciclo es la posicion columna en el archivo
            {
                if (esSeparador(cadena.at(i)))
                {
                    columna = i + 1;
                    caracter = cadena.at(i);
                    buscarAgregarSeparador(caracter, to_string(fila), to_string(columna));
                    buscarAgregarSimbolo(simbolo, to_string(fila), to_string(columna));
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

void Analizador::buscarAgregarSimbolo(string simbolo, string fila, string columna)
{
    int i = 0;
    if (!yaExiste(simbolo, fila, columna))
    {
        while (i < tablaSimbolos.size() && tablaSimbolos.at(i).getSimbolo().compare(simbolo) != 0)
            i++;
        if (i < tablaSimbolos.size())
        {
            Registro r = tablaSimbolos.at(i);
            simbolos.push_back(r);
            simbolos.back().setNuevaPosicion(fila, columna);
        }
        else
        {
            vector<string> v;
            v.push_back("Identificador");
            v.push_back("Variable");
            Registro r("Variable", simbolo, v);
            simbolos.push_back(r);
            simbolos.back().setNuevaPosicion(fila, columna);
        }
    }
}

void Analizador::buscarAgregarSeparador(string simbolo, string fila, string columna)
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
            simbolos.push_back(r);
            simbolos.back().setNuevaPosicion(fila, columna);
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

bool Analizador::esSeparador(char simbolo)
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

bool Analizador::yaExiste(string simbolo, string fila, string columna)
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

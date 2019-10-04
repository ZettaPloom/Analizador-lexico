#ifndef Analizador_H
#define Analizador_H
#include <vector>
#include <fstream>
#include <string>
#include "Registro.hpp"
#include "Tabla.hpp"
#include "Gramatica.hpp"

class Analizador
{
private:
    vector<Registro> simbolos;
    vector<Registro> tablaSimbolos;
    vector<Registro> tablaSeparadores;
    vector<Registro> tablaTokens;
    vector<Registro> tokens;
    string rutaCodigoAux;

public:
    Analizador(string rutaSimbolos, string rutaCodigo);
    void identificarSimbolos(string rutaCodigo);
    bool esSeparador(char simbolo);
    bool yaExiste(string simbolo, string fila, string columna);
    bool yaExisteToken(string lexema);
    void buscarAgregarSimbolo(string simbolo, string fila, string columna);
    void buscarAgregarSeparador(string simbolo, string fila, string columna);
    void buscarAgregarToken(string lexema);
    vector<Registro> getSimbolos();
    vector<Registro> getTokens();
    vector<Registro> getTablaSimbolos();
    vector<Registro> getTablaSeparadores();
    vector<Registro> getTablaTokens();
    void AnalizarExpsAritmeticas();
};

Analizador::Analizador(string rutaSimbolos, string rutaCodigo)
{
    Tabla leerTabla(rutaSimbolos);
    tablaSeparadores = leerTabla.getTablaSeparadores();
    tablaSimbolos = leerTabla.getTablaSimbolos();
    tablaTokens = leerTabla.getTablaTokens();
    identificarSimbolos(rutaCodigo);
    this->rutaCodigoAux = rutaCodigo;
}

void Analizador::AnalizarExpsAritmeticas()
{
    ifstream archivo(rutaCodigoAux);
    if (archivo.fail())
        cout << "Error al abrir el archivo de código" << endl;
    else
    {
        string cadena;
        string cadenaAnalizar;
        bool lineaCompleta = true;
        Gramatica* g;
        while (!archivo.eof())
        {
            getline(archivo, cadena);
            for (int i = 0; i < cadena.size(); i++)
            {
                if (cadena.at(i) == '+' || cadena.at(i) == '-' || cadena.at(i) == '*'
                 || cadena.at(i) == '/' || cadena.at(i) == '%')
                {
                    for (int j = 0; j < cadena.size(); j++)
                    {
                        if(cadena.at(j) == '=')
                        {
                            for (int k = j + 1; k < cadena.size() - 1; k++)
                            {
                                lineaCompleta = false;
                                cadenaAnalizar+= cadena.at(k);
                            }
                        }
                    }
                    if (lineaCompleta)
                    {
                        cadenaAnalizar = cadena;
                    }
                }
            }
            if(!cadenaAnalizar.empty())
            {
                g = new Gramatica(cadenaAnalizar);
                cadenaAnalizar.clear();
                cout << endl;
            }
        }
    }
}

void Analizador::identificarSimbolos(string rutaCodigo)
{
    ifstream archivo(rutaCodigo);
    if (archivo.fail())
        cout << "Error al abrir el archivo de código" << endl;
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
                    buscarAgregarSimbolo(simbolo, to_string(fila), to_string(columna - simbolo.size()));
                    buscarAgregarSeparador(caracter, to_string(fila), to_string(columna));
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
            buscarAgregarToken(simbolo);
        }
        else
        {
            vector<string> v;
            v.push_back("Identificador");
            v.push_back("Variable");
            Registro r(simbolo, v);
            simbolos.push_back(r);
            simbolos.back().setNuevaPosicion(fila, columna);
            Registro t("Identificador variable", "36", simbolo);
            tokens.push_back(t);
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
            buscarAgregarToken(simbolo);
        }
    }
}

void Analizador::buscarAgregarToken(string lexema)
{
    int i = 0;
    while (i<tablaTokens.size()&&tablaTokens.at(i).getSimbolo().compare(lexema) != 0)
        i++;
    if(i<tablaTokens.size()){
        Registro t = tablaTokens.at(i);
        tokens.push_back(t);
    }
}

vector<Registro> Analizador::getSimbolos()
{
    return this->simbolos;
}

vector<Registro> Analizador::getTokens()
{
    return this->tokens;
}

vector<Registro> Analizador::getTablaSimbolos()
{
    return this->tablaSimbolos;
}

vector<Registro> Analizador::getTablaSeparadores()
{
    return this->tablaSeparadores;
}

vector<Registro> Analizador::getTablaTokens()
{
    return this->tablaTokens;
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

bool Analizador::yaExisteToken(string lexema)
{
    bool existe = false;
    int i = 0;
    while (i < tokens.size() && !existe)
        if (tokens.at(i).getSimbolo().compare(lexema) == 0)
            existe = true;
            // tokens.at(i).setNuevaPosicion(fila, columna);
        else
            i++;
    return existe;
}
#endif

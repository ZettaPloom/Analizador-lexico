#ifndef Registro_H
#define Registro_H
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Registro
{
private:
    string nombre;
    string simbolo;
    vector<string> tipo;
    vector<string> filas; //El primero es la linea, el segundo la columna
    vector<string> columnas;
    int cantidadSimbolos;

public:
    Registro(string nombre, string simbolo, vector<string> tipo)
    {
        this->nombre = nombre;
        this->simbolo = simbolo;
        this->tipo = tipo;
        cantidadSimbolos = 0;
    }
    Registro(const Registro &origen)
    {
        this->nombre = origen.nombre;
        this->simbolo = origen.simbolo;
        this->tipo = origen.tipo;
        this->cantidadSimbolos = origen.cantidadSimbolos;
        this->filas = origen.filas;
        this->columnas = origen.columnas;
    }
    void setNuevaPosicion(string fila, string columna)
    {
        this->filas.push_back(fila);
        this->columnas.push_back(columna);
        this->cantidadSimbolos++;
    }
    string getNombre()
    {
        return this->nombre;
    }
    string getSimbolo()
    {
        return this->simbolo;
    }
    vector<string> getTipo()
    {
        return this->tipo;
    }
    int getCantidadSimbolos()
    {
        return this->cantidadSimbolos;
    }
    string getPosiciones()
    {
        string result = "";
        for (int i = 0; i < filas.size(); i++)
        {
            result += this->filas.at(i) + "-" + this->columnas.at(i) + "; ";
        }
        return result;
    }
};
#endif

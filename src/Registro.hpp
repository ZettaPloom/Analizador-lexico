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
    vector<int> filas; //El primero es la linea, el segundo la columna
    vector<int> columnas;
    int cantidadSimbolos = filas.size();

public:
    Registro(string nombre, string simbolo, vector<string> tipo)
    {
        this->nombre = nombre;
        this->simbolo = simbolo;
        this->tipo = tipo;
    }
    Registro(const Registro &origen)
    {
        this->nombre = origen.nombre;
        this->simbolo = origen.simbolo;
        this->tipo = origen.tipo;
    }
    void setNuevaPosicion(int fila, int columna)
    {
        this->filas.push_back(fila);
        this->columnas.push_back(columna);
        cantidadSimbolos = filas.size();
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
            result += filas.at(i) + ", " + columnas.at(i);
            result += "; ";
        }
        return result;
    }
};
#endif

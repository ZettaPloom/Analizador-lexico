#ifndef Registro_H
#define Registro_H
#include <string>
#include <iostream>
#include <vector>
#include <utility>
using namespace std;

class Registro
{
private:
    string nombre;
    string simbolo;
    vector<string> tipo;
    int cantidadSimbolos;
    vector<pair<int, int>> posiciones; //El primero es la linea, el segundo la columna
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
    void setNuevaPosicion(pair<int,int> posicion){
        posiciones.push_back(posicion);
        cantidadSimbolos=posiciones.size();
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
    void toString()
    {
        // vector<pair<int,int>> tipos;
        // pair<int,int> p;
        // p.first=1;
        // p.second=1;
        // tipos.push_back(p);
        cout << nombre << "\t" << simbolo << "\t";
        for (int i = 0; i < tipo.size(); i++)
        {
            cout << tipo.at(i) << "\t";
        }
        cout << endl;
    }
};
#endif

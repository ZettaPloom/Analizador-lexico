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

public:
    Registro(string nombre, string simbolo, vector<string> tipo)
    {
        this->nombre = nombre;
        this->simbolo = simbolo;
        this->tipo = tipo;
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
        cout << nombre << "\t" << simbolo << "\t";
        for (int i = 0; i < tipo.size(); i++)
        {
            cout << tipo.at(i) << "\t";
        }
        cout << endl;
    }
};
#endif

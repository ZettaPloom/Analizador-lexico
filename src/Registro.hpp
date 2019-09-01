#ifndef Registro_H
#define Registro_H
#include <string>
#include <vector>
using namespace std;

class Registro
{
private:
    string token;
    string simbolo;
    vector<string> tipo;
    vector<string> filas;
    vector<string> columnas;
    int cantidadSimbolos;
    string IDToken;

public:
    Registro(string simbolo, vector<string> tipo)
    {
        this->simbolo = simbolo;
        this->tipo = tipo;
        cantidadSimbolos = 0;
    }
    Registro(string token, string IDToken, string lexema)
    {
        this->token = token;
        this->IDToken = IDToken;
        this->simbolo = lexema;
    }
    Registro(const Registro &origen)
    {
        this->token = origen.token;
        this->IDToken = origen.IDToken;
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
    string getToken()
    {
        return this->token;
    }
    string getSimbolo()
    {
        return this->simbolo;
    }
    string getIDToken()
    {
        return this->IDToken;
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

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include <boost/algorithm/string.hpp>
#include "Registro.hpp"
using namespace std;

class Tabla
{
private:
    vector<Registro> tablaSimbolos;
    vector<Registro> tablaSeparadores;

public:
    Tabla(string ruta);
    vector<Registro> setTablas(string ruta, bool leerSeparadores); //true es Separadores, false es Simbolos
    vector<Registro> getTablaSimbolos();
    vector<Registro> getTablaSeparadores();
};

Tabla::Tabla(string ruta)
{
    tablaSeparadores = setTablas(ruta, true);
    tablaSimbolos = setTablas(ruta, false);
}

vector<Registro> Tabla::setTablas(string ruta, bool leerSeparadores)
{
    ifstream fin(ruta);
    vector<Registro> tb;
    if (fin.fail())
        cout << "Error al abrir el archivo";
    else
    {
        Json::Reader reader;
        Json::Value obj;
        reader.parse(fin, obj);
        const Json::Value &campos = obj["Simbolos"];
        for (int i = 0; i < campos.size(); i++)
        {
            const Json::Value &camposTipos = campos[i]["Tipo"];
            if (campos[i]["EsSeparador"].asBool())
            {
                vector<string> tipos;
                for (int j = 0; j < camposTipos.size(); j++)
                {
                    tipos[i] = camposTipos[i].asString();
                }
                Registro r(campos[i]["Nombre"].asString(), campos[i]["Simbolo"].asString(), tipos);
                tb.push_back(r);
            }
            else
            {
                vector<string> tipos;
                for (int i = 0; i < camposTipos.size(); i++)
                {
                    tipos[i] = camposTipos[i].asString();
                }
                Registro r(campos[i]["Nombre"].asString(), campos[i]["Simbolo"].asString(), tipos);
                tb.push_back(r);
            }
        }
    }
    return tb;
}

vector<Registro> Tabla::getTablaSimbolos()
{
    return this->tablaSimbolos;
}

vector<Registro> Tabla::getTablaSeparadores()
{
    return this->tablaSeparadores;
}

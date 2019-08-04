#ifndef Tabla_R
#define Tabla_R
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <jsoncpp/json/json.h>
#include "Registro.hpp"
#include "TextTable.h"
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
    static void toString(vector<Registro> r);
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
    {
        vector<string> tipos;
        tipos.push_back("Error");
        Registro r("Error", "Error", tipos);
        tb.push_back(r);
        cout << "Error al abrir el archivo" << endl;
    }
    else
    {
        Json::Reader reader;
        Json::Value obj;
        reader.parse(fin, obj);
        vector<string> tipos;
        const Json::Value &campos = obj["Simbolos"];
        for (int i = 0; i < campos.size(); i++)
        {
            const Json::Value &camposTipos = campos[i]["Tipo"];
            if (campos[i]["EsSeparador"].asBool() && leerSeparadores)
            {
                for (int j = 0; j < camposTipos.size(); j++)
                {
                    tipos.push_back(camposTipos[j].asString());
                }
                Registro r(campos[i]["Nombre"].asString(), campos[i]["Simbolo"].asString(), tipos);
                tb.push_back(r);
                tipos.clear();
            }
            else if (!campos[i]["EsSeparador"].asBool() && !leerSeparadores)
            {
                for (int k = 0; k < camposTipos.size(); k++)
                {
                    tipos.push_back(camposTipos[k].asString());
                }
                Registro r(campos[i]["Nombre"].asString(), campos[i]["Simbolo"].asString(), tipos);
                tb.push_back(r);
                tipos.clear();
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

void Tabla::toString(vector<Registro> r)
{
    TextTable t('-', '|', '+');
    t.add("Nombre del simbolo");
    t.add("Simbolo");
    t.add("Tipos");
    t.endOfRow();
    if (!r.at(5).getPosiciones().empty())
    {
        t.add("Cantidad de simbolos");
        t.add("Posicion de cada simbolo");
        for (int i = 0; i < r.size(); i++)
        {
            t.add(r.at(i).getNombre());
            t.add(r.at(i).getSimbolo());
            string tipo = "";
            for (int j = 0; j < r.at(i).getTipo().size(); j++)
            {
                tipo += r.at(i).getTipo().at(j) + ", ";
            }
            t.add(tipo);
            string cantidad = r.at(i).getCantidadSimbolos()+"";
            t.add(cantidad);
            string posiciones = "";
            for (int j = 0; j < r.at(i).getPosiciones().size(); j++)
            {
                posiciones += r.at(i).getPosiciones().at(j).getFila() + ", " + r.at(i).getPosiciones().at(j).getColumna();
                posiciones += "; ";
            }
            t.add(posiciones);
            t.endOfRow();
        }
    }
    else
    {
        for (int i = 0; i < r.size(); i++)
        {
            t.add(r.at(i).getNombre());
            t.add(r.at(i).getSimbolo());
            string tipo = "";
            for (int j = 0; j < r.at(i).getTipo().size(); j++)
            {
                tipo += r.at(i).getTipo().at(j) + ", ";
            }
            t.add(tipo);
            t.endOfRow();
        }
    }
    t.setAlignment(2, TextTable::Alignment::LEFT);
    std::cout << t << endl;
}
#endif

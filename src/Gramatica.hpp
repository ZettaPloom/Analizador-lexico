
#include <string>
#include <iostream>
using namespace std;

class Gramatica
{
private:
    string cadenaEntrada;
    char tokenEntrada;
    int posicion;

public:
    string getCadenaEntrada()
    {
        return this->cadenaEntrada;
    }

    Gramatica(string cadenaEntrada)
    {
        this->cadenaEntrada = cadenaEntrada;
        posicion = 0;
        tokenEntrada = PrimerToken();
        Expresion();
    }

    void HacerMatch(char t)
    {
        if (t == tokenEntrada)
        {
            tokenEntrada = SiguienteToken();
        }
        else
        {
            PresentarError();
        }
    }

    char SiguienteToken()
    {
        if (posicion < cadenaEntrada.size())
        {
            posicion++;
            return cadenaEntrada.at(posicion - 1);
        }
        else
        {
            exit(0);
        }
    }

    char PrimerToken()
    {
        posicion++;
        return cadenaEntrada.at(posicion - 1);
    }

    void Letra()
    {
        if (isalpha(tokenEntrada))
        {
            cout << "Analizando: " << tokenEntrada << endl;
            HacerMatch(tokenEntrada);
        }
    }

    void Digit()
    {
        if (isdigit(tokenEntrada))
        {
            cout << "Analizando: " << tokenEntrada << endl;
            HacerMatch(tokenEntrada);
        }
    }

    void Identificador()
    {
        Letra();
        IdentificadorPrima();
    }

    void IdentificadorPrima()
    {
        if (isalpha(tokenEntrada))
        {
            Letra();
            IdentificadorPrima();
        }
    }

    void Numeros()
    {
        Digit();
        NumerosPrima();
    }

    void NumerosPrima()
    {
        if (isdigit(tokenEntrada))
        {
            Digit();
            NumerosPrima();
        }
    }

    void Factor()
    {
        if (isdigit(tokenEntrada))
        {
            Numeros();
        }
        else if (isalpha(tokenEntrada))
        {
            Identificador();
        }
        else if (tokenEntrada == '(')
        {
            cout << "Analizando: " << tokenEntrada << endl;
            HacerMatch('(');
            Expresion();
            cout << "Analizando: " << tokenEntrada << endl;
            HacerMatch(')');
        }
    }

    void Termino()
    {
        Factor();
        TerminoPrima();
    }

    void TerminoPrima()
    {
        if (tokenEntrada == '*')
        {
            cout << "Analizando: " << tokenEntrada << endl;
            HacerMatch('*');
            Factor();
            TerminoPrima();
        }
        else if (tokenEntrada == '/')
        {
            cout << "Analizando: " << tokenEntrada << endl;
            HacerMatch('/');
            Factor();
            TerminoPrima();
        }
        else if (tokenEntrada == '%')
        {
            cout << "Analizando: " << tokenEntrada << endl;
            HacerMatch('%');
            Factor();
            TerminoPrima();
        }
    }

    void Expresion()
    {
        Termino();
        ExpresionPrima();
    }

    void ExpresionPrima()
    {
        if (tokenEntrada == '+')
        {
            cout << "Analizando: " << tokenEntrada << endl;
            HacerMatch('+');
            Termino();
            ExpresionPrima();
        }
        else if (tokenEntrada == '-')
        {
            cout << "Analizando: " << tokenEntrada << endl;
            HacerMatch('-');
            Termino();
            ExpresionPrima();
        }        
    }

    void PresentarError()
    {
        cout << "Error en token: "+ tokenEntrada << endl;
    }
};

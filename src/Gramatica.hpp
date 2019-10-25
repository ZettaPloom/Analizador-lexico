
#include <string>
#include <iostream>
using namespace std;

class Gramatica
{
private:
    string cadenaEntrada;
    char tokenEntrada;
    int posicion;
    bool aceptada = true;
    string preOrden;
    string posOrden;

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
        if (aceptada)
                cout << "La cadena: " << cadenaEntrada << " es aceptada por la gramática" << endl;
    }

    string getPreOrden()
    {
        return this->preOrden;
    }

    string getPosOrden()
    {
        return this->posOrden;
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
            //cout << "Analizando: " << tokenEntrada << endl;
            preOrden+=tokenEntrada;
            posOrden+=tokenEntrada;
            HacerMatch(tokenEntrada);
        }
    }

    void Digit()
    {
        if (isdigit(tokenEntrada))
        {
            //cout << "Analizando: " << tokenEntrada << endl;
            preOrden+=tokenEntrada;
            posOrden+=tokenEntrada;
            HacerMatch(tokenEntrada);
        }
        else
        {
            //PresentarError();
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
            // preOrden+=tokenEntrada;
            Numeros();
            // posOrden+=tokenEntrada;
        }
        else if (isalpha(tokenEntrada))
        {
            // preOrden+=tokenEntrada;
            Identificador();
            // posOrden+=tokenEntrada;
        }
        else if (tokenEntrada == '(')
        {
            //cout << "Analizando: " << tokenEntrada << endl;
            HacerMatch('(');
            preOrden+='(';
            posOrden+='(';
            Expresion();
            //cout << "Analizando: " << tokenEntrada << endl;
            HacerMatch(')');
            preOrden+=')';
            posOrden+=')';
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
            //cout << "Analizando: " << tokenEntrada << endl;
            
            HacerMatch('*');
            Factor();
            preOrden+='*';
            TerminoPrima();
            posOrden+='*';
        }
        else if (tokenEntrada == '/')
        {
            //cout << "Analizando: " << tokenEntrada << endl;
            HacerMatch('/');
            Factor();
            preOrden+='/';
            TerminoPrima();
            posOrden+='/';
        }
        else if (tokenEntrada == '%')
        {
            //cout << "Analizando: " << tokenEntrada << endl;
            HacerMatch('%');
            Factor();
            preOrden+='%';
            TerminoPrima();
            posOrden+='%';
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
            //cout << "Analizando: " << tokenEntrada << endl;
            HacerMatch('+');
            Termino();
            preOrden+='+';
            ExpresionPrima();
            posOrden+='+';
        }
        else if (tokenEntrada == '-')
        {
            //cout << "Analizando: " << tokenEntrada << endl;
            HacerMatch('-');
            Termino();
            preOrden+='-';
            ExpresionPrima();
            posOrden+='-';
        }
        else
        {
            //PresentarError();
        }
    }

    void PresentarError()
    {
        aceptada = false;
        cout << "La cadena: " << cadenaEntrada << " NO es aceptada por la gramática" << endl;
    }
};

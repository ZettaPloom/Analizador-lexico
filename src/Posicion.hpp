class Posicion
{
private:
    int fila;
    int columna;

public:
    Posicion(int fila, int columna)
    {
        this->fila = fila;
        this->columna = columna;
    }
    int getFila()
    {
        return this->fila;
    }
    int getColumna()
    {
        return this->columna;
    }
};
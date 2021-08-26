#ifndef USUARIO_H
#define USUARIO_H
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

class usuario
{
public:
    void leer_archivo(char *contenido,string nombre_de_entrada);
    void convertircadena(int *entero,char *contenido);
    void siste_binario(char *binario,int *entero);
    void metodo2(char *binario,int semilla,string nombre_de_salida);
    void deco_metodo2(int semilla,string nombre_de_entrada);
    string recogerunalinea(int linea, string a);
    bool ingresarcomousuario(string a);
    void versaldo(string usuario);
    void retirardinero(string usuario);
    usuario();
};

#endif // USUARIO_H

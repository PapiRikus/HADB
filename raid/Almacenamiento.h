//
// Created by richard on 11/06/17.
//

#ifndef PROYECTO3_ALMACENAMIENTO_H
#define PROYECTO3_ALMACENAMIENTO_H

#include <fstream>
#include <iostream>
using namespace std;
class Datos :public fstream {
public:
    Datos() : fstream("alea.txt", ios::in | ios::out | ios::binary) {
        if(!good()) {
            open("alea.txt", ios::in | ios::out | ios::trunc | ios::binary);
            cout << "fichero creado" << endl;
            cin.get();
        }
    }
    ~Datos() {}
    string cortarString(string string1);
    void Guardar(bool &x);
    bool Recupera(long n, bool &x);
    void editar(long n, bool &x);
    void escribirString(string std, long posicion);
    bool validarExistencia(long posicion);
    void crearTabla(int indice);
    void agregarColumna(int indice);
    bool recuperarAux(long posicion);
    string pasarIntBinario(int numero);
    string recuperarEntero(long posicion);

private:
    int tamanoTabla = 20816;
};


#endif //PROYECTO3_ALMACENAMIENTO_H

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
    void escribirEntero(string std, long posicion);
    string recuperarCaracteres(long posicion);
    bool validarExistencia(long posicion);
    void crearTabla(int indice);
    void agregarFila(int tabla, int indicecolumna, string valor);
    void agregarDatoColumna(int indice,int posicion,int locacion, string dato);
    void escribirCaracteres(string std, long posicion);
    bool EliminarFila(int tabla, int id);
    bool recuperarAux(long posicion);
    string pasarIntBinario(int numero);
    string recuperarEntero(long posicion);

private:
    void eliminarEntero(long posicion);
    void eliminarCaracter(long posicion);
    int bloqueEntero = 32;
    int bloqueString = 2048;
    long cantidadGeneral = 0;
    int tamanoTabla = 20544;
};


#endif //PROYECTO3_ALMACENAMIENTO_H

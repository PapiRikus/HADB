/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ArbolBmas.h
 * Author: aaronsolera
 *
 * Created on 15 de junio de 2017, 07:30 AM
 */

#ifndef ARBOLBMAS_H
#define ARBOLBMAS_H

#include <fstream>
#include <iostream>
#include "NodoBmas.h"
using namespace std;

class ArbolBmas:public fstream{
public:
    NodoBmas *raiz, *Xr, *P, *N, *vsam;
    int k, cuentas, MAX, MIN, nivel;
    NodoProducto mediana;
    bool esta, ea;
    double contT, contTot;
    int eli;
    int arreglo[50];
    //bandera es del archivo maestro, y bandera2
    int bandera, bandera2;
    //Prototipos
    ArbolBmas();

    void refrescar ();
    void insertar (NodoProducto);
    void empujar(NodoProducto, NodoBmas *);
    void meterHoja();
    bool arbolVacio(NodoBmas *);
    void dividir ();
    void doblar (NodoBmas *);
    //imprime el arbol en orden por la referencia de la raiz
    void print_rec ();
    void print_rec_aux (NodoBmas *nodo);//auxiliar
    bool buscarNodo (NodoProducto clave, NodoBmas *nodo);
    bool buscar (NodoProducto clave, NodoBmas *nodo);
    //busca si una clace existe o no en el arbol
    bool buscar (NodoProducto clave);
    //da la altura
    int  Altura ();
    //imprime en anchura
    void Anchura();
    void Anchura_aux (NodoBmas *, int , int);
    //imprime por niveles auxiliar de anchura aux
    void ImprimeNivel(NodoBmas *, int);
    //imprime por la referencia de orden
    void Imprimir ();
    //carga el archivo de productos
    void Cargar();

    /***********  Recorridos **************************/

    void postOrdenRecursivo(NodoBmas *r);
    void postOrdenIterativo(NodoBmas *r);
    void preOrdenRecursivo(NodoBmas *r);
    void preOrdenIterativo(NodoBmas *r);

    void postOrdenRecursivoAux(NodoBmas *r);
    void postOrdenIterativoAux(NodoBmas *r);
    void preOrdenRecursivoAux(NodoBmas *r);
    void preOrdenIterativoAux(NodoBmas *r);

    //bool buscarNodo (int clave, NodoBmas *pagina);
    bool Buscar (int clave);
    //elimina al archivo
    void Eliminar(int);
    //ve si c esta en el archivo
    int Esta(int c);
    NodoProducto* Encontrar(int c);

    bool EstaArreglo(int num);
    void ImprimirArreglo();
};

#endif /* ARBOLBMAS_H */


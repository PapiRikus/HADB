/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   HuffmanCompresor.h
 * Author: cp
 *
 * Created on 12 de junio de 2017, 09:51 PM
 */

#ifndef HADB_HUFFMANCOMPRESOR_H
#define HADB_HUFFMANCOMPRESOR_H

#include <iostream>
using namespace std;
/* Tipo nodo para árbol o Lista de árboles*/
/* El propósito es dual, sirve como elemento de una lista enlazada */
/* Cuando se usa el puntero sig, y como elemento de un árbol cuando */
/* se usan los punteros cero y uno */
typedef struct _nodo
{
    char letra;      /* Letra a la que hace referencia el nodo */
    int frecuencia;  /* veces que aparece la letra en el texto o las letras */
    /* de los nodos de las ramas cero y uno */
    _nodo *sig;      /* Puntero a siguiente nodo de una lista enlazada */
    _nodo *cero;     /* Puntero a la rama cero de un árbol */
    _nodo *uno;      /* Puntero a la rama uno de un árbol */
} tipoNodo;         /* Nombre de tipo */

/* Tipo nodo para árbol */
typedef struct _tnodo
{
    char letra;             /* Letra a la que hace referencia el nodo */
    unsigned long int bits; /* Valor de la codificación de la letra */
    char nbits;             /* Número de bits de la codificación */
    _tnodo *cero;            /* Puntero a la rama cero de un árbol */
    _tnodo *uno;             /* Puntero a la rama uno de un árbol */
} tipoTNodo;                /* Nombre del tipo */

/* Nodo para construir una lista para la tabla de codigos */
typedef struct _tabla
{
    char letra;      /* Letra a la que hace referencia el nodo */
    unsigned long int bits; /* Valor de la codificación de la letra */
    char nbits;      /* Número de bits de la codificación */
    _tabla *sig;     /* Siguiente elemento de la tabla */
} tipoTabla;        /* Nombre del tipo */


class HuffmanCompresor {
private:
    /* Variables globales */
    tipoTabla *Tabla;
    void Cuenta(tipoNodo* &Lista, char c);
    void Ordenar(tipoNodo* &Lista);
    void InsertarOrden(tipoNodo* &Cabeza, tipoNodo *e);
    void BorrarArbol(tipoNodo *n);
    void BorrarArbol(tipoTNodo *n);
    void CrearTabla(tipoNodo *n, int l, int v);
    void InsertarTabla(char c, int l, int v);
    tipoTabla *BuscaCaracter(tipoTabla *Tabla, char c);
public:
    void compress(char* in_file, char* out_file);
    void decompress(char* in_file, char* out_file);
    string compress(string to_compress);
    string decompress(string to_decompress);
};

#endif //HADB_HUFFMANCOMPRESOR_H#endif /* HUFFMANCOMPRESOR_H */


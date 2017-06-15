/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodoBmas.h
 * Author: aaronsolera
 *
 * Created on 15 de junio de 2017, 07:24 AM
 */

#ifndef NODOBMAS_H
#define NODOBMAS_H

#include "NodoProducto.h"

class NodoBmas{
public:
    NodoProducto claves [5];
    NodoBmas     *ramas [5];
    NodoBmas     *shojas;
    int cuentas;

    // Prototipos
    NodoBmas ();
};


#endif /* NODOBMAS_H */


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NodoProducto.h
 * Author: aaronsolera
 *
 * Created on 15 de junio de 2017, 07:26 AM
 */

#ifndef NODOPRODUCTO_H
#define NODOPRODUCTO_H

#include <iostream>
class NodoProducto{
public:
    int    Codigo;
    int    Precio;
    std::string Descripcion;

    // Prototipos
    NodoProducto ();
    NodoProducto(int cod, int pres, std::string des);
};

#endif /* NODOPRODUCTO_H */

